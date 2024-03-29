#ifndef GAMETASK_HPP
#define GAMETASK_HPP

#include "Player.hpp"
#include "RunGameControl.hpp"
#include "TransferHitsControl.hpp"
#include "DisplayTask.hpp"
#include "SendTask.hpp"
#include "BuzzerTask.hpp"
#include "Keyboard.hpp"
#include "KeyboardListener.hpp"

#include "hwlib.hpp"
#include "rtos.hpp"

///@file
///\brief
///The Game Task class dictates the entire laser tag game.
///\details
///The class inherits from the rtos::task and KeyboardListener classes.
///It expects the Player, RunGameControl, and TransferHitsControl by value.
///Furthermore it expects the DisplayTask and SendTask by reference.
class GameTask : public rtos::task<>, KeyboardListener {
private:
	Player<> player;
	DisplayTask & displayTask;
	SendTask & sendTask;
	BuzzerTask & buzzerTask;
	RunGameControl runGameControl;
	TransferHitsControl transferHitsControl;
	rtos::clock clock1S;
	rtos::timer invincibilityTimer;
	rtos::timer rateOfFireTimer;
	rtos::timer startTimer;
	rtos::channel<int, 128> buttonChannel;
	rtos::channel<uint16_t, 128> receiveChannel;
	rtos::flag gameOverFlag;
	const uint16_t commandStart = 0b1000000000000000;
	uint16_t commandTime = 0x00;
	char commandString[16];
	//size_t second = 1'000'000;
	size_t startBit = 0b1000'0000'0000'0000;
	size_t lowestPlayerBit = 0b0000'0010'0000'0000;
public:
	GameTask(
		Player<> playerInput,
		DisplayTask & displayTaskInput,
		SendTask & sendTaskInput,
		BuzzerTask & buzzerTaskInput,
		Keyboard<> & keyboardInput
	):
		task(300,"GameTask"),
		player(playerInput),
		displayTask(displayTaskInput),
		sendTask(sendTaskInput),
		buzzerTask(buzzerTaskInput),
		runGameControl(RunGameControl(player,sendTask)),
		transferHitsControl(TransferHitsControl(player)),
		clock1S(this, 1'000'000, "1 second clock"),
		invincibilityTimer(this, "Invicibility Timer"),
		rateOfFireTimer(this, "Rate of Fire Timer"),
		startTimer(this,"Countdown on startup"),
		buttonChannel(this, "Channel for Buttons"),
		receiveChannel(this,"Channel for messages"),
		gameOverFlag(this,"Signals Game Over")

	{
		keyboardInput.addKeyboardListener(this);
	}

	///\brief
	///The buttonPressed function calls the writeButtonChannel.
	void buttonPressed(int btnID) override;

	///\brief
	///The writeButtonChannel fills the buttonChannel with btnID's.
	void writeButtonChannel(int btnID);

	///\brief
	///The writeReceiveChannel fills the receiveChannel with a message.
	void writeReceiveChannel(size_t message);

	///\brief
	///The setGameOverFlag sets the gameOverFlag.
	void setGameOverFlag();

	enum class mainStates {REG_GAME_PARAM, INIT_GAME, RUN_GAME};
	enum class regGameParamStates {IDLE,PLAYER_INPUT,WAIT_ON_B, WEAPON_INPUT, WAIT_ON_COMMAND};
	enum class initGameStates {IDLE,GET_TIME,SEND_TIME,SEND_START};
	enum class runGameStates {STARTUP, PLAYING, SHOOT, GET_SHOT, GAME_OVER, EXPORTING};


	///\brief
	///The main rtos::task from the GameTask class.
	///\details
	///This function will move through all of the states the game can be in.
	///It uses the various enum classes to achieve this.
	void main() override{
		static mainStates mainState = mainStates::REG_GAME_PARAM;
		static regGameParamStates regSubState = regGameParamStates::IDLE;
		static initGameStates initSubState = initGameStates::IDLE;
		static runGameStates runSubState = runGameStates::STARTUP;
		while(true){
			switch (mainState){
				//In this state the user can configure his player ID and
				//choose his weapon. Once the user has chosen these settings
				//the program will wait for the time and start signal send
				//by the game leader.
				case mainStates::REG_GAME_PARAM:{
					switch (regSubState){
						//In this state the user will start configuring his settings
						//once he has pressed the A button.
						//If the settings are set the user will have to wait for
						//the time and start commands from the leader.
						case regGameParamStates::IDLE:{
							textDisplay output = {"\fA: choose player\n"};
							displayTask.writeDisplayPool(output);
							wait(buttonChannel);
							int btnID = buttonChannel.read();
							if(btnID == Buttons::btnA){
								regSubState = regGameParamStates::PLAYER_INPUT;
							}
							break;
						}
						//In this state the user chooses his player ID.
						//If the player decides to choose player ID 0 he will me
						//send to the INIT_GAME state where he will be treated as
						//the game leader. Otherwise he will be send to WAIT_ON_B
						//to start the process of choosing a weapon.
						case regGameParamStates::PLAYER_INPUT:{
							textDisplay output = {"\fnumber 1/9\n"};
							displayTask.writeDisplayPool(output);
							hwlib::wait_ms(10);
							wait(buttonChannel);
							int btnID = buttonChannel.read();
							if(btnID == Buttons::btn0){
								regSubState = regGameParamStates::IDLE;
								mainState = mainStates::INIT_GAME;
							}else if(btnID <= 9){
								player.setPlayerID(btnID);
								regSubState = regGameParamStates::WAIT_ON_B;
							}
							break;
						}
						//In this state the user has to press the B button to
						//move to the WEAPON_INPUT state.
						case regGameParamStates::WAIT_ON_B:{
							textDisplay output = {"\fB: choose weapon\n"};
							displayTask.writeDisplayPool(output);
							hwlib::wait_ms(10);
							wait(buttonChannel);
							auto btnID = buttonChannel.read();
							if( btnID == Buttons::btnB){
								regSubState = regGameParamStates::WEAPON_INPUT;
							}
							break;
						}
						//In this state the user has to choose a weapon and will be moved
						//to the IDLE state to wait for the game leader's commands.
						case regGameParamStates::WEAPON_INPUT:{
							textDisplay output = {"\fweapon 1/9\n"};
							displayTask.writeDisplayPool(output);
							hwlib::wait_ms(10);
							wait(buttonChannel);
							auto btnID = buttonChannel.read();
							if(btnID <= 9){
								player.setWeapon( btnID );
								regSubState = regGameParamStates::WAIT_ON_COMMAND;
							}
							break;
						}
						case regGameParamStates::WAIT_ON_COMMAND:{
							textDisplay output1 = {"\fWait for commands\n"};
							displayTask.writeDisplayPool(output1);
							hwlib::wait_ms(10);
							auto event = wait(receiveChannel);
							if (event == receiveChannel){
								auto incomingMsg = receiveChannel.read();
								if (incomingMsg < (startBit | lowestPlayerBit) && !runGameControl.getTime()){
									textDisplay output2 = {"\fTime received\n"};
									displayTask.writeDisplayPool(output2);
									hwlib::wait_ms(10);
									uint16_t clearData = incomingMsg << 7;
									uint8_t readData = clearData >> 12;
									size_t resultTimesSixty = readData*60;
									runGameControl.setGameTime(resultTimesSixty);
								} else if (incomingMsg == startBit && runGameControl.getTime()){
									textDisplay output2 = {"\fStart received\n"};
									displayTask.writeDisplayPool(output2);
									hwlib::wait_ms(10);
									regSubState = regGameParamStates::IDLE;
									mainState = mainStates::RUN_GAME;
								}
							}
							break;
						}
					}
					break;
				}
				//In this state the user has choosen the player ID 0 and is now the
				//game leader. First the leader has to set time of the game and then
				//start sending the time to the players. After that the leader has
				//to start sending the start signal to the players.
				case mainStates::INIT_GAME:{

					switch (initSubState){
						//In this state the user has to press the C button to start
						//settings the time. Once the C button is pressed the user
						//moves to the GET_TIME state.
						case initGameStates::IDLE:{
							textDisplay output = {"\fPress C to set\ntime"};
							displayTask.writeDisplayPool(output);
							hwlib::wait_ms(10);
							wait(buttonChannel);
							auto btnID = buttonChannel.read();
							if(btnID == Buttons::btnC){
								initSubState = initGameStates::GET_TIME;
							}
							break;
						}
						//In this state the user can set the time.
						//We restricted the playtime between 10 and 99 minutes.
						//We also gave the leader the option to press the * button
						//to set the time to one minute for demo purposes.
						case initGameStates::GET_TIME:{
							textDisplay output = {"\fTijd:"};
							displayTask.writeDisplayPool(output);
							hwlib::wait_us(25);
							displayTask.writeDisplayPool(commandTime);
							displayTask.setDisplayFlagNumber();
							hwlib::wait_ms(10);
							static size_t itterator = 1;
							wait(buttonChannel);
							auto btnID = buttonChannel.read();
							if(btnID <= 9 && itterator == 1){
								commandTime += btnID * 10;
								itterator++;
							} else if (btnID <= 9 && itterator == 2){
								commandTime += btnID;
								itterator++;
							} else if (btnID == Buttons::btnStar){
								commandTime = 1;
							} else if (btnID == Buttons::btnHashtag || itterator == 3){
								itterator = 1;
								//commandTime *= 60;
								commandTime <<= 5;
								initSubState = initGameStates::SEND_TIME;
							}
							break;
						}
						//In this state the user will send the time to the players.
						//When the user presses the * button he will move to SEND_START
						case initGameStates::SEND_TIME:{
							textDisplay output1 = {"\f#: send time\n*: send start"};
							displayTask.writeDisplayPool(output1);
							hwlib::wait_ms(10);
							wait(buttonChannel);
							auto btnID = buttonChannel.read();
							if(btnID == Buttons::btnStar){
								initSubState = initGameStates::SEND_START;
								textDisplay output2 = {"\f*: start signal"};
								displayTask.writeDisplayPool(output2);
								break;
							} else if(btnID == Buttons::btnHashtag){
								commandTime |= startBit;
								sendTask.writeComPool(commandTime);
								sendTask.setComFlag();
							}
							break;
						}
						//In this state the user will send the start command to the players.
						//When the user presses anything else than  the * button he will
						//move to the IDLE state.
						case initGameStates::SEND_START:{
							wait(buttonChannel);
							auto btnID = buttonChannel.read();
							if(btnID == btnStar){
								sendTask.writeComPool(commandStart);
								sendTask.setComFlag();
								break;
							}else{
								commandTime = 0;
								initSubState = initGameStates::IDLE;
								break;
							}
						}
						default:{
							break;
						}
					}
					break;
				}
				//The user will end up in this state after the start command has
				//been received. It will start with a countdown after which the
				//the game has started. Then we will move through several states
				//to shoot and get shot.
				case mainStates::RUN_GAME:{
					static uint16_t hitMessage;
					switch (runSubState){
						//In this state the game is going to start.
						//There will be a sound during the countdown and after
						//3 seconds the user will move to the PLAYING state.
						case runGameStates::STARTUP:{
							textDisplay output = {"\fstarting...\n"};
							displayTask.writeDisplayPool(output);
							buzzerTask.makeSound(BuzzerTask::sounds::START_END_SOUND);
							startTimer.set(3'000'000);
							wait(startTimer);
							runSubState = runGameStates::PLAYING;
							break;
						}
						//In this state the user is playing the game.
						//By pressing the * button the user will shoot and move to
						//the SHOOT state. By receiving a message in the receiveChannel
						//the user will move to the GET_SHOT state.
						//We will also change the time every second and listen to the
						//gameOverFlag to end the game.
						case runGameStates::PLAYING:{
							auto event = wait(clock1S + buttonChannel + receiveChannel + gameOverFlag);
							if(event == clock1S){
								if(!runGameControl.reduceTime()){
									setGameOverFlag();
								}
								gameDisplay message = gameDisplay({
									runGameControl.getTime(),
									player.getPlayerID(),
									player.getScore()});
								displayTask.writeDisplayPool(message);
							} else if (event == buttonChannel){
								auto btnID = buttonChannel.read();
								if(btnID == Buttons::btnStar){
									runSubState = runGameStates::SHOOT;
								}
							} else if(event == receiveChannel){
								auto msg = receiveChannel.read();
								if(msg > startBit){
									hitMessage = msg;
									runSubState = runGameStates::GET_SHOT;
								}
							} else if (event == gameOverFlag){
								runSubState = runGameStates::GAME_OVER;
							}
							break;
						}
						//In this state the user is shooting.
						//After shooting we wait for the rateOfFireTimer to have finished.
						//Here too we listen to the clock1S and gameOverFlag events.
						case runGameStates::SHOOT:{
							runSubState = runGameStates::PLAYING;
							uint16_t message = 0x01 << 15;
							uint16_t playerBits = player.getPlayerID() << 10;
							uint16_t weaponBits = player.getWeaponIndex() << 5;
							message |= playerBits;
							message |= weaponBits;
							sendTask.writeComPool( message );
							sendTask.setComFlag();
							rateOfFireTimer.set( player.getWeaponFireRate());
							auto event = wait(clock1S + rateOfFireTimer + gameOverFlag);
							if(event == clock1S){
								if(!runGameControl.reduceTime()){
									setGameOverFlag();
									runSubState = runGameStates::GAME_OVER;
								}
								gameDisplay message = gameDisplay({
									runGameControl.getTime(),
									player.getPlayerID(),
									player.getScore()});
								displayTask.writeDisplayPool(message);
							} else if (event == rateOfFireTimer){
								runSubState = runGameStates::PLAYING;
							} else if (event == gameOverFlag){
								runSubState = runGameStates::GAME_OVER;
							}
							break;
						}
						//In this state you have been shot and we will change the score of
						//the user.
						case runGameStates::GET_SHOT:{
							runSubState = runGameStates::PLAYING;
							uint16_t playerBits = hitMessage << 1;
							playerBits >>= 11;
							uint16_t weaponBits = hitMessage << 6;
							weaponBits >>= 11;
							player.reportHit(playerBits,weaponBits);
							invincibilityTimer.set(200);
							auto event = wait(clock1S + invincibilityTimer + gameOverFlag);
							if(event == clock1S){
								if(!runGameControl.reduceTime()){
									setGameOverFlag();
									runSubState = runGameStates::GAME_OVER;
								}
								gameDisplay message = gameDisplay({
									runGameControl.getTime(),
									player.getPlayerID(),
									player.getScore()});
								displayTask.writeDisplayPool(message);
							} else if (event == invincibilityTimer){
								if(!player.getScore()){
									setGameOverFlag();
									runSubState = runGameStates::GAME_OVER;
								}
							} else if (event == gameOverFlag){
								runSubState = runGameStates::GAME_OVER;
							}
							break;

						}
						//In this state the game is over. We will wait until
						//the user has pressed the D button to start exporting
						//the stats of the user.
						case runGameStates::GAME_OVER:{
							wait(buttonChannel);
							auto btnID = buttonChannel.read();
							if(btnID == Buttons::btnD){
								runSubState = runGameStates::EXPORTING;
							}
							break;
						}
						//In this state the user has started the exporting process.
						//When this is done we set the sub state back to START_UP
						//and the main state to REG_GAME_PARAM to start all over again.
						case runGameStates::EXPORTING:{
							transferHitsControl.exportPlayer();
							runSubState = runGameStates::STARTUP;
							break;
						}
						default:{
							break;
						}							
					}
					break;
				}
			}
		}
	}
};
#endif