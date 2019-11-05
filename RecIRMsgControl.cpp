#include "RecIRMsgControl.hpp"

bool RecIRMsgControl::recBit(bool bit, bool resetMessage){
	// If the resetMessage bit is set, reset the messages and return false
	if(resetMessage){
		message = 0;
		lastMsg = 0;
		return false;
	}



	// Shift a new bit into message and if the bit is supposed to be 1, set the bit to 1
	message <<= 1;
	if(bit){
		message |= 1;
	}

	// If the startbit was set, return true, else false.
	if(message >> 15 & 0x1){
		return true;
	}else{
		return false;
	}
}

bool RecIRMsgControl::checkMessage(uint16_t & _message){
	// Check if the messages are the same, if they aren't: set lastMsg to message and reset message.
	// Since the messages weren't valid, return false
	if(!CMP()){
		lastMsg = message;
		message = 0;
		return false;
	}

	// Check if the control bits for the current message are correct,
	// if it isn't set the lastMsg to message and reset message.
	// Since the messages weren't valid, return false
	if(!XOR()){
		lastMsg = message;
		message = 0;
		return false;
	}

	// If they are the same and the control bits were right, set the ReceiveTask '_message' to message and set lastMsg to message.
	// After that reset message and return true, as the message is correct.
	_message = message;
	lastMsg = message;
	message = 0;
	hwlib::cout << "CORRECT MESSAGE!!!! Message: " << hwlib::bin << _message << "\n";
	return true;
}

bool RecIRMsgControl::XOR(){
	// Check if bit 11 is the xor of bit 1 & bit 6,
	// Then check if bit 12 is the xor of bit 2 & bit 7... etc
	// If one of those is incorrect, return false
	// If they were all correct, return true
	for(int i = 0; i < 5; i++){
		uint8_t firstBit = message << (11+i); // clear bits left of the 12+i bit
				firstBit = message >> 15;

		uint8_t bitToCheck1 = message << (1+i); // clear bits left of the 2+i bit
				bitToCheck1 = bitToCheck1 >> 15; // shift it right

		uint8_t bitToCheck2 = message << (6+i); // clear bits left of the 7+i bit
				bitToCheck2 = bitToCheck2 >> 15; // shift it right

		if( !(firstBit ^ (bitToCheck1 & bitToCheck2)) ){
			return false;
		}
	}
	return true;
}

bool RecIRMsgControl::CMP(){
	return (lastMsg==message);
}
