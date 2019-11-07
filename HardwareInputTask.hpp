#ifndef HARDWAREINPUTTASK_HPP
#define HARDWAREINPUTTASK_HPP

#include "Keyboard.hpp"

#include "hwlib.hpp"
#include "rtos.hpp"

/// @file
///\brief
///This tasks polls the keyboard every x milliseconds and calls the keyboard update() function.
template<unsigned int N = 1>
class HardwareInputTask : public rtos::task<>{
private:
	Keyboard<N> & keyboard;			///<The keyboard object whose update function gets called
	rtos::timer period;			///<The timer that checks if the keyboard update gets called
public:
	///\brief
	///The default constructor. Initializes the timer, rtos task and the keyboard.
	HardwareInputTask(
		Keyboard<> & keyboardInput
	):
		task(4,"Hardware Input Task"),
		keyboard(keyboardInput),
		period(this, "Period Timer")
	{};

	///\brief
	///The task main, calls the keyboard update function every 100ms.
	void main() override{
		while(true){
			// Start the timer at 100ms, or 100.000us
			period.set(100'000);
			
			// Call the update function
			keyboard.update();

			// Wait until the timer ends
			wait(period);
		}
	}
};

#endif // HardwareInputTask_hpp