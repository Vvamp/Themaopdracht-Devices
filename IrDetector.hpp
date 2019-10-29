#ifndef IrDetector_hpp
#define IrDetector_hpp

#include "hwlib.hpp"

class IrDetector{
private:
	hwlib::target::pin_in detectorPin;

public:
	IrDetector() :
		detectorPin(hwlib::target::pins::d12)
	{};

	bool get();
};

#endif // IrDetector.hpp