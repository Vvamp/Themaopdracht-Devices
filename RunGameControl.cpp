#include "RunGameControl.hpp"

void RunGameControl::setGameTime(size_t time){
	gameTime = time;
};

void RunGameControl::toDisplay(hwlib::string<128> & msg){
	msg.clear();
	/*
		Gametime gaan bitshfiten, de bit(s) naar een tijdchar casten
		Dit in een string pleuren en dat in een strnig zetten
		
	*/
	hwlib::string<10> timeMsg = "Tijd : ";
	
	hwlib::string<20> playerMsg = "\nPlayer ID : " + (char)player.getPlayerID();
	hwlib::string<10> scoreMsg = "\nScore : ";

	msg += timeMsg;
	msg += 
};

bool RunGameControl::reduceTime(){
	gameTime--;
	return bool(gameTime);
};

size_t RunGameControl::getTime(){
	return gameTime;
};