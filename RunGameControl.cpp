#include "RunGameControl.hpp"

void RunGameControl::setGameTime(size_t time){
	gameTime = time;
};

void RunGameControl::toDisplay(hwlib::string<200> & msg){
	/*
		Gametime gaan bitshfiten, de bit(s) naar een tijdchar casten
		Dit in een string pleuren en dat in een strnig zetten
		
	*/
	size_t asciiOffset = 48;
	uint8_t smallNumber = (gameTime < 10) ? gameTime : gameTime%10;
	uint8_t bigNumber = (gameTime > 9) ? (gameTime-smallNumber)/10 : 0; 
	char[2] valChars;
	valChars[0] = bigNumber;
	valChars[1] = smallNumber;
	hwlib::string<10> timeMsg = "Tijd : ";
	hwlib::string<2> valueMsg = valChars[0] + valChars[1];
	hwlib::string<32> playerMsg = "\nPlayer ID : " + player.getPlayerID();
	hwlib::string<32> scoreMsg = "\nScore : " + player.getScore();
	msg += timeMsg;
	msg += valueMsg;
	msg += playerMsg;
	msg += scoreMsg;
};

bool RunGameControl::reduceTime(){
	gameTime--;
	return bool(gameTime);
};

size_t RunGameControl::getTime(){
	return gameTime;
};