#include "GameTask.hpp"

void override GameTask::buttonPressed(buttons btnID){
	writeButtonChannel(btnID);
};

void GameTask::writeButtonChannel(buttons btnID){
	buttonChannel.write(btnID);
};

void GameTask::writeReceiveChannel(size_t message){
	receiveChannel.write(message);
};

void GameTask::setGameOverFlag(){
	gameOverFlag.set();
};