#include "GameTask.hpp"

void GameTask::buttonPressed(Buttons btnID){
	writeButtonChannel(btnID);
};

void GameTask::writeButtonChannel(Buttons btnID){
	buttonChannel.write(btnID);
};

void GameTask::writeReceiveChannel(size_t message){
	receiveChannel.write(message);
};

void GameTask::setGameOverFlag(){
	gameOverFlag.set();
};