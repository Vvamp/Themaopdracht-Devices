#ifndef GameTask_hpp
#define GameTask_hpp

#include "hwlib.hpp"
#include "rtos.hpp"

class GameTask : public rtos::task, Keyboardlistener {
private:
	Player player;
	RunGameControl runGameControl;
	InitGameControl initGameControl;
	RegGameParamControl regGameParamControl;
	TransferHitsControl transferHitsControl;
	DisplayTask & displayTask;
	SendTask & sendTask;
	rtos::clock clock1S;
	rtos::timer startTimer;
	rtos::timer invincibleTimer; // set to 200ms
	rtos::timer rateOfFireTimer;
	rtos::channel<buttons, 128> buttonChannel;
	rtos::channel<uint16_t, 128> receiveChannel;
	rtos::flag gameOverFlag;
	const uint16_t commandStart = 0x00;
	uint16_t commandTime = 0x00;
	size_t second = 1'000'000;
	size_t startBit = 0b1000'0000'0000'0000;
public:
	GameTask(
		Player playerInput,
		RunGameControl runGameControlInput,
		InitGameControl initGameControlInput,
		RegGameParamControl regGameParamControlInput,
		TransferHitsControl transferHitsControlInput,
		DisplayTask & displayTaskInput,
		SendTask & sendTaskInput
	):
		player(playerInput),
		runGameControl(runGameControlInput),
		initGameControl(initGameControlInput),
		regGameParamControl(regGameParamControlInput),
		transferHitsControl(transferHitsControlInput),
		displayTask(displayTaskInput),
		sendTask(sendTaskInput),
		clock1S(this, second, "1 second clock"),
		invincibleTimer(this, "Invicibility Timer"),
		rateOfFireTimer(this, "Rate of Fire Timer")
	{}

	void override buttonPressed(buttons btnID);
	void writeButtonChannel(buttons btnID);
	void writeReceiveChannel(size_t message);
	void setGameOverFlag();

	enum class mainStates {REG_GAME_PARAM, INIT_GAME, RUN_GAME, TRANSFER_HITS};
	enum class regGameParamStates {IDLE,PLAYER_INPUT,WAIT_ON_B, WEAPON_INPUT};
	enum class initGameStates {IDLE,GET_TIME,SEND_TIME,SEND_START};
	enum class runGameStates {STARTUP, PLAYING, SHOOT, GET_SHOT, GAME_OVER, EXPORTING};

	void override main(){
		static mainStates mainState = mainStates::REG_GAME_PARAM;
		static regGameParamStates regSubState = regGameParamStates::IDLE;
		static initGameStates initSubState = initGameStates::IDLE;
		static runGameStates runSubState = runGameStates::STARTUP;

		while(true){

			switch (mainState){
			case mainStates::REG_GAME_PARAM:

				switch (regSubState){
				case regGameParamStates::IDLE:
					auto event = wait(buttonChannel + receiveChannel);
					if (event == buttonChannel){
						auto btnID = buttonChannel.read();
						(btn == buttons::btnA) ? regSubState = regGameParamStates::PLAYER_INPUT : break;
					} else if (receiveChannel){
						if(player.getPlayerID()){
							auto msg = receiveChannel.read();
						}
					}
				case regGameParamStates::PLAYER_INPUT:
					wait(buttonChannel);
					auto btnID = buttonChannel.read();
					if(btnID == 0){
						regSubState = regGameParamStates::IDLE;
						mainState = mainStates::INIT_GAME;
					}else if(btnID <= 9){
						player.setPlayerID(btnID);
						regSubState = regGameParamStates::WAIT_ON_B;
					}
					break;
				case regGameParamStates::WAIT_ON_B:
					wait(buttonChannel);
					auto btnID = buttonChannel.read();
					if( btnID == buttons::btnB){
						regSubState = regGameParamStates::WEAPON_INPUT;
					}
					break;
				case regGameParamStates::WEAPON_INPUT:
					wait(buttonChannel);
					auto btnID = buttonChannel.read();
					if(btnID <= 9){
						player.setWeapon( btnID );
						regSubState = regGameParamStates::IDLE;
					}
					break;
				}
				break;

			case mainStates::INIT_GAME:

				switch (initSubState){
				case initGameStates::IDLE:
					displayTask.writeDisplayPool("");
					displayTask.setDisplayFlag();
					wait(buttonChannel);
					auto btnID = buttonChannel.read();
					if(btnID == buttons::btnC){
						initSubState = initGameStates::GET_TIME;
					}
					break;
				case initGameStates::GET_TIME:
					displayTask.writeDisplayPool("Tijd : " + commandTime);
					displayTask.setDisplayFlag();
					static itterator = 1;
					wait(buttonChannel);
					auto btnID = buttonChannel.read();
					if(btnID <= 9 && itterator == 1){
						commandTime += btnID * 10;
						itterator++;
					} else if (btnID <= 9 && itterator == 2){
						commandTime += btnID;
						itterator++;
					} else if (btnID == buttons::btnHashtag || itterator == 3){
						itterator = 1;
						initSubState = initGameStates::SEND_TIME;
					}
					break;
				case initGameStates::SEND_TIME:
					wait(buttonChannel);
					auto btnID = buttonChannel.read();
					if(btnID == btnStar){
						initSubState = initGameStates::SEND_START;
					} else if(btnID == btnHashtag){
						sendTask.writeComPool(commandTime);
						sendTask.setComFlag();
					}
					break;
				case initGameStates::SEND_START:
					wait(buttonChannel);
					auto btnID = buttonChannel.read();
					if(btnID == btnStar){
						sendTask.writeComPool(commandStart);
						sendTask.setComFlag();
						break;
					}
					initSubState = initGameStates::IDLE;
				default:
					break;
				}
				break;

			case mainStates::RUN_GAME:
				static hitMessage;
				switch (runSubState){
				case runGameStates::STARTUP:
					buzzerTask.makeSound(buzzerTask::sounds::startSound);
					startTimer.set(3'000'000);
					wait(startTimer);
					runSubState = runGameStates::PLAYING;
					break;
				case runGameStates::PLAYING:
					auto event wait(buttonChannel + receiveChannel + gameOverFlag);
					if (event == buttonChannel){
						auto btnID = buttonChannel.read();
						if(btnID == buttons::btnStar){
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
				case runGameStates::SHOOT:
					uint16_t message = 0x01 << 16;
					uint16_t playerBits = player.getPlayerID() << 10;
					uint16_t weaponBits = player.getWeaponIndex() << 5;
					message |= playerBits;
					message |= weaponBits;
					sendTask.writeComPool( message );
					rateOfFireTimer.set( player.getWeaponRateOfFire());
					auto event wait(clock1S + rateOfFireTimer + gameOverFlag);
					if(event == clock1S){
						runGameControl.reduceTime();
						displayTask.writeDisplayPool.write(runGameControl.toDisplay());
						if(!runGameControl.getTime()){
							setGameOverFlag();
						}
					} else if (event == rateOfFireTimer){
						runSubState = runGameStates::PLAYING;
					} else if (event == gameOverFlag){
						runSubState = runGameStates::GAME_OVER;
					}
					break;
				case runGameStates::GET_SHOT:
					uint16_t playerBits = hitMessage << 1;
					playerBits >>= 11;
					uint16_t weaponBits = hitMessage << 6;
					weaponBits >>= 11;
					player.reportHit(playerBits,weaponBits);
					break;
				case runGameStates::GAME_OVER:
					wait(buttonChannel);
					auto btnID = buttonChannel.read();
					if(btnID == buttons::btnD){
						runSubState = runGameStates::EXPORTING;
					}
					break;
				case runGameStates::EXPORTING:
					transferHitsControl.exportPlayer();
					runSubState = runGameStates::STARTUP;
					mainState = mainStates::REG_GAME_PARAM;
					break;
				default:
					break;
				}
				break;
			}
		}
	};
};

#ifndef