#ifndef RECEIVETASK_HPP
#define RECEIVETASK_HPP

#include "RecIRMsgControl.hpp"
#include "IrDetector.hpp"
#include "GameTask.hpp"

#include "hwlib.hpp"
#include "rtos.hpp"

///@file
///\brief
///The IR receiver task
///\details
///This rtos::task checks the incoming IR signals and translates it to IR messages.
class ReceiveTask : public rtos::task<>{
private:
	GameTask & gameTask;			//<The GameTask 'uber' object, to write the received message to
	RecIRMsgControl recIRMsgControl;//<The IR Receiver control object, to check and compose the messages
	IrDetector irDetector;			//<The IR detector boundary object
	rtos::timer messageTimer;		//<The timer object that lets the system know that it's taken too long for a new bit and the next bit received should be for a new message
	rtos::timer interruptTimer;		//<The timer that interrupts the wait for messageTimer
	uint16_t message;				//<The correct, composed message to be sent to gameTask
	enum states{IS_LOW, IS_HIGH};	//<The 2 states this task can be in, used to calculate pauses which get translated to bits
	states state = IS_LOW;			//<System starts at the isLow state
public:

	///\brief
	///The ReceiveTask constructor takes no parameters and initializes all of its objects itself.
	ReceiveTask(
		hwlib::target::pin_in irReceiverPin,
		GameTask & gameTaskInput
	):
		task(10"Receive Task"),
		gameTask(gameTaskInput),
		recIRMsgControl(),
		irDetector(irReceiverPin),
		messageTimer(this, "Message Timer"),
		interruptTimer(this, "Interrupt Timer")
	{};

	///\brief
	///The ReceiveTask body.
	///\details
	///It checks incoming IR signals, translates it to bits.
	///Bits gets translated to a message and if the message is composed, it's checked with the lastMessage received.
	///These messages get written to the message channel.
	void main() override{
		int beginPause = -1;
		int eindPause = -1;
		int pause = -1;
		int bit = -1;
		for(;;){
			switch(state){
				case IS_LOW:{
					interruptTimer.set(25);

					auto event = wait(messageTimer + interruptTimer);
					if(event == messageTimer){
						recIRMsgControl.recBit(false, true);
						break;
					}

					if(irDetector.get() == 1){
						state = IS_HIGH;
						eindPause = hwlib::now_us();
					}
					break;
				}

				case IS_HIGH:{
					interruptTimer.set(25);

					if(beginPause >= 0 && eindPause >= 0){
						pause = eindPause - beginPause;
						beginPause = -1;
						eindPause = -1;
					}

					if(pause >= 0){
						if(pause >= 700 && pause <= 900){bit=0;}else
						if(pause >= 1500 && pause <= 1700){bit=1;}
						pause=-1;
					}

					if(bit>=0){
						// A bit was received, start timer
						messageTimer.set(4'000);
						if(recIRMsgControl.recBit(bit)){
							if(recIRMsgControl.checkMessage(message) == true){
								gameTask.writeReceiveChannel(message);
							}
						}
						bit=-1;
					}

					auto event = wait(messageTimer + interruptTimer);
					if(event == messageTimer){
						recIRMsgControl.recBit(false, true);
						break;
					}

					if(irDetector.get() == 0){
						state = IS_LOW;
						beginPause = hwlib::now_us();
					}
					break;
				}
			}
		}
	}
};

#endif // Receive_Task.hpp