#include "RunGameControl.hpp"

void RunGameControl::setGameTime(size_t time){
	gameTime = time;
};

void RunGameControl::toDisplay(hwlib::string<200> & msg){
	msg = "Tijd : " + gameTime + "\nPlayer ID : " +player.getPlayerID() + "\nScore : " + player.getScore();
};

hwlib::string

bool RunGameControl::reduceTime(){
	gameTime--;
	return bool(gameTime);
};

size_t RunGameControl::getTime(){
	return gameTime;
};