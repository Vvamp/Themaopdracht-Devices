#ifndef RunGameControl_hpp
#define RunGameControl_hpp

#include "hwlib.hpp"
#include "Player.hpp"
#include "SendTask.hpp"

class RunGameControl : public KeyboardListener {
private:
	Player & player;
	SendTask & sendTask;
	size_t gameTime = 0x00;
public:
	RunGameControl(
		Player & playerInput,
		SendTask & sendTaskInput
	):
		player(playerInput),
		sendTask(sendTaskInput)
	{}

	void setGameTime(size_t time);
	hwlib::string toDisplay();
	bool reduceTime();
	size_t getTime();
};

#endif
