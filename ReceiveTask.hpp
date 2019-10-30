#ifndef ReceiveTask_hpp
#define ReceiveTask_hpp

#include "hwlib.hpp"
#include "rtos.hpp"

#include "GameTask.hpp"
#include "RecIRMsgControl.hpp"
#include "IrDetector.hpp"

///@file
///\brief
///The IR receiver task
///\details
///This rtos::task checks the incoming IR signals and translates it to IR messages.
class ReceiveTask : public rtos::task<>{
private:
	GameTask gameTask;
	RecIRMsgControl recIRMsgControl;
	IrDetector irDetector;
	rtos::timer timerMsg;
	rtos::timer interruptTimer;
	uint16_t message;
	enum states = {isLow, isHigh};
	states state = isLow;
public:
	///\brief
	///The ReceiveTask constructor takes no parameters and initializes all of its objects itself.
	ReceiveTask():
		task("Receive Task"),
		gameTask(),
		recIRMsgControl(),
		irDetector(),
		timerMsg(this, "Message Timer"),
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
				case isLow:
				{
					timerMsg.set(4'000);
					interruptTimer.set(150);

					if(beginPause >= 0 && eindPause >= 0){
						pause = eindPause - beginPause;
						beginPause = -1; 
						eindPause = -1;
						hwlib::wait_us(20);

					}

					if(pause >= 0){
						if(pause >= 700 && pause <= 900){bit=1}else
						if(pause >= 1500 && pause <= 1700){bit=0}
						pause=-1;
						hwlib::wait_us(20);
					}

					if(bit>=0){
						if(recIRMsgControl.recbit(bit)){
							if(recIRMsgControl.checkmessage(message) == true){
								gameTask.writeReceiveChannel(message);
							}
						}
						bit=-1;
						hwlib::wait_us(20);
					}

					auto event = wait(timerMsg + interruptTimer);
					if(event == timerMsg){
						recIRMsgControl.recBit(false, true);
						break;
					}
				
					if(irDetector.get() == 1){
						state = isHigh;
						eindPause = hwlib::now_us();
					}
					break;
				}

				case isHigh:
				{
					timerMsg.set(4'000);
					interruptTimer.set(150);

					auto event = wait(timerMsg + interruptTimer);
					if(event == timerMsg){
						recIRMsgControl.recBit(false, true);
						break;
					}
				
					if(irDetector.get() == 0){
						state = isLow;
						eindPause = hwlib::now_us();
					}
					break;
				}

			}
		}
	}

};

#endif // Receive_Task.hpp