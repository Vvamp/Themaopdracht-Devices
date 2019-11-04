#include "GameTask.hpp"

void GameTask::buttonPressed(int btnID){
	writeButtonChannel(btnID);
};

void GameTask::writeButtonChannel(int btnID){
	buttonChannel.write(btnID);
};

void GameTask::writeReceiveChannel(size_t message){
	receiveChannel.write(message);
};

void GameTask::setGameOverFlag(){
	gameOverFlag.set();
};