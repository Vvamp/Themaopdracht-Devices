#ifndef RunGameControl_hpp
#define RunGameControl_hpp

#include "hwlib.hpp"
#include "Player.hpp"
#include "SendTask.hpp"
// #include "KeyboardListener.hpp"

class RunGameControl {
private:
	Player<> & player;
	SendTask & sendTask;
	size_t gameTime = 0x00;
public:
	RunGameControl(
		Player<> & playerInput,
		SendTask & sendTaskInput
	):
		player(playerInput),
		sendTask(sendTaskInput)
	{}

	void setGameTime(size_t time);
	void toDisplay(hwlib::string<200> & msg);
	bool reduceTime();
	size_t getTime();
};

#endif
