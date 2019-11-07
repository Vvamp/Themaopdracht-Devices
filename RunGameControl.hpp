#ifndef RUNGAMECONTROL_HPP
#define RUNGAMECONTROL_HPP

#include "Player.hpp"
#include "SendTask.hpp"

#include "hwlib.hpp"

///\brief
///RungameControl tracks information for the player for the game.
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

	///\brief
	///setGameTime sets the gameTime.
	void setGameTime(size_t time);

	///\brief
	///reduceTime reduces the gameTime varaible by 1 and return false when it has reached 0.
	bool reduceTime();

	///\brief
	///getTime returns the gameTime parameter.
	size_t getTime();
};

#endif
