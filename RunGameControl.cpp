#include "RunGameControl.hpp"

void RunGameControl::setGameTime(size_t time){
	gameTime = time;
};

hwlib::string RunGameControl::toDisplay(){
	hwlib::string msg = "Tijd : " + gameTime + "\n";
	msg += "Player ID : " + player.getPlayerID() + "\n";
	msg += "Score : " + player.getScore();
	return msg;
};

bool RunGameControl::reduceTime(){
	gameTime--;
};

size_t RunGameControl::getTime(){
	return gameTime;
};