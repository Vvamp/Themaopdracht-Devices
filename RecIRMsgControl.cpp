#include "RecIRMsgControl.hpp"

bool RecIRMsgControl::recBit(bool bit, bool resetMessage){
	if(resetMessage){
		message = 0;
		lastMsg = 0; 
		return true;
	}

	message <<= 1;
	if(bit){
		message |= 1;
	}

	if(message >> 15 & 0x1){
		return true;
	}else{
		return false;
	}
}

bool RecIRMsgControl::checkMessage(uint16_t & _message){
	if(!CMP()){
		lastMsg = message; // I don't remember if we have to store the lastMsg here or someplace else
		return false;
	}

	if(!XOR()){
		lastMsg = message; // I don't remember if we have to store the lastMsg here or someplace else
		return false;
	}

	_message = message;
	return true;
}

bool RecIRMsgControl::XOR(){
	bool xorCorrect = true;

	for(int i = 0; i < 5; i++){
		uint8_t firstBit = message << 11+i; // clear bits left of the 12+i bit
				firstBit = message >> 15;

		uint8_t bitToCheck1 = message << 1+i; // clear bits left of the 2+i bit
				bitToCheck1 = bitToCheck1 >> 15; // shift it right

		uint8_t bitToCheck2 = message << 6+i; // clear bits left of the 7+i bit
				bitToCheck2 = bitToCheck2 >> 15; // shift it right

		if( !(firstBit ^ bitToCheck1 & bitToCheck2) ){
			xorCorrect=false;
		}
	}
	return xorCorrect;
}

bool RecIRMsgControl::CMP(){
	(lastMsg == message) ? return true : return false;
}