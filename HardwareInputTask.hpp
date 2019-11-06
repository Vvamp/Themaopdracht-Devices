#ifndef HardwareInputTask_hpp
#define HardwareInputTask_hpp

#include "hwlib.hpp"
#include "rtos.hpp"

#include "Keyboard.hpp"

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
		task(50,"Hardware Input Task"),
		keyboard(keyboardInput),
		period(this, "Period Timer")
	{};

	///\brief
	///The task main, calls the keyboard update function every 100ms.
	void main() override{
		for(;;){
			// Start the timer at 100ms, or 100.000us
			period.set(150'000);
			
			// Call the update function
			keyboard.update();

			// Wait until the timer ends
			wait(period);
		}
	}
};


#endif // HardwareInputTask_hpp