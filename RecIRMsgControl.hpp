#ifndef RecIRMsgControl_hpp
#define RecIRMsgControl_hpp

#include "hwlib.hpp"

class RecIRMsgControl{
private:
	static uint16_t message = 0;
	static uint16_t lastMsg = 0;
	
	bool XOR();
	bool CMP();

public:
	RecIRMsgControl() :
	{};

	bool recBit(bool bit, bool resetMessage = false);

	bool checkMessage(uint16_t & _message);

};

#endif // RecIRMsgControl_hpp