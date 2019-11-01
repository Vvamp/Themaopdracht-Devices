#ifndef RecIRMsgControl_hpp
#define RecIRMsgControl_hpp

#include "hwlib.hpp"
///@file
///\brief
///The control object for the IR receiver
///\details
///This control objects composes the IR message and checks if it's valid.
class RecIRMsgControl{
private:
	static uint16_t message = 0;	//<The current message being composed
	static uint16_t lastMsg = 0;	//<The previously composed message
	
	///\brief
	///Returns true if the current message's control bits are the way they should be
	bool XOR();

	///\brief
	///Returns true if the lastMessage and the current message are the same
	bool CMP();

public:
	///\brief 
	///Default constructor for the RecIRMsgcontrol class. It takes no parameters.
	RecIRMsgControl() :
	{};

	///\brief 
	///Receive a bit and add it to the IR message that's currently being composed
	///\details
	///The bit parameter represents a bit: true is 1, false is 0.
	///The resetMessage parameter is false by default, and if set to true it resets the message and lastMessage.
	bool recBit(bool bit, bool resetMessage = false);

	///\brief
	///
	bool checkMessage(uint16_t & _message);

};

#endif // RecIRMsgControl_hpp