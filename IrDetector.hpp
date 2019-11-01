#ifndef IrDetector_hpp
#define IrDetector_hpp

#include "hwlib.hpp"
///@file
///\brief
///The IR receiver object
///\details
///The pin is set for pin D12 on the Arduino Due.
///The state can be retrieved via the public get() member, which returns it through a bool.
class IrDetector{
private:
	hwlib::target::pin_in detectorPin;			//<The pin_in for the IR receiver

public:
	///\brief
	///The IrDetector constructor, it takes no parameters and initializes the necessary members itself.
	IrDetector() :
		detectorPin(hwlib::target::pins::d12)
	{};

	///\brief
	///Returns true if the IR receiver pin is HIGH and false if the IR receiver pin is LOW.
	///\details
	///It refreshes the hwlib::pin_in, before returning the value.
	bool get();
};

#endif // IrDetector.hpp