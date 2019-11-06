#include "RunGameControl.hpp"

void RunGameControl::setGameTime(size_t time){
	gameTime = time;
};

void RunGameControl::toDisplay(hwlib::string<200> & msg){
	/*
		Gametime gaan bitshfiten, de bit(s) naar een tijdchar casten
		Dit in een string pleuren en dat in een strnig zetten
		
	*/
	hwlib::string<32> timeMsg = "Tijd : " + gameTime;
	hwlib::string<32> playerMsg = "\nPlayer ID : " + player.getPlayerID();
	hwlib::string<32> scoreMsg = "\nScore : " + player.getScore();
	msg += timeMsg;
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