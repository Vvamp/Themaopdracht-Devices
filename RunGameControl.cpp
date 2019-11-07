#include "RunGameControl.hpp"

void RunGameControl::setGameTime(size_t time){
	gameTime = time;
};

bool RunGameControl::reduceTime(){
	gameTime--;
	return bool(gameTime);
};

size_t RunGameControl::getTime(){
	return gameTime;
};

