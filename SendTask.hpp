#ifndef SENDTASK_HPP
#define SENDTASK_HPP

#include "IrDiode.hpp"

#include "hwlib.hpp"
#include "rtos.hpp"

///@file
///\brief
/// Send task class
///\details
/// Class that inherits from rtos task. It waits for the comflag to be set, it will then read the command pool and send the command through its IR sender.
/// the command needs to be 16 bits.
class SendTask : public rtos::task<>{
private:
	IrDiode irDiode; 								//< object from the IR diode class.

    rtos::flag comFlag;								//< flag that need to be set when something is written in the pool
    rtos::pool<uint16_t> comPool; 					//< pool in which commands can be written
    rtos::timer timer;

    uint16_t shortWait = 795; 						//< the wait short wait time between turning on and off the IR sender
    uint16_t longWait = 1595; 						//< the long wait time between turning on and off the IR sender
    uint16_t message = 0; 							//< variable in which the message is set when the pool is read
    uint8_t counter = 0;							//< counter that is used to count

    enum class states{IDLE,SET_BIT,SEND_0,SEND_1};	//<enumerator that holds the names on which the task switches
    states state = states::IDLE;					//< member variable on which the task switches

public:

    ///\brief
    /// constructor
    ///\details
    /// the constructor only needs a hwlib pin out to be able to function.
    SendTask(
		hwlib::target::d2_36kHz& p
	):
		task(3,"Send task"),
		irDiode(p),
		comFlag(this,"send command flag"),
		comPool("command pool"),
		timer(this,"send timer")
    {};

    ///\brief
    /// this function sets the command flag
    void setComFlag();

    ///\brief
    /// this function sets the command pool
    void writeComPool(uint16_t command);

    ///\brief
    /// function to fill in the last 5 bits of the command with the XOR of other bits
    ///\details
    /// this function fills in the XOR of bit 2 and 7 of the command, and places it in the 12th bit, it than takes the XOR of bit 3 and 8 and places
    /// it in bit 13, and so on. only after this is done, the command is valid to be sent.
    void checkSum(uint16_t & _message);

    void main() override{
		static uint16_t tmpMsg = 0x00;
        while(true){
            switch (state){
                case states::IDLE:{
                    auto ev = wait(comFlag);
                    if (ev == comFlag){
                        wait(comFlag);
                        message = comPool.read();
                        checkSum(message);
                        counter = 0;
						tmpMsg = message;
                        state = states::SET_BIT;
						hwlib::wait_us(100);
                        break;
                    }
                    break;
                }

                case states::SET_BIT:{
                    uint8_t bit = message >> 15;
                    message <<= 1;
                    counter++;
                    if (counter == 34){
                        state = states::IDLE;
                        break;
					} else if (counter == 17){
						hwlib::wait_us(3'000);
						message = tmpMsg;
                    } else {
						irDiode.setLow();
                        if (bit == 0){
                            state = states::SEND_0;
                            break;
                        }
                        else{
                            state = states::SEND_1;
                            break;
                        }
                    }
                    break;
                }

                case states::SEND_0:{
                    irDiode.setHigh();
					hwlib::wait_us(shortWait);
                    irDiode.setLow();
					hwlib::wait_us(longWait);
                    state = states::SET_BIT;
                    break;
                }

                case states::SEND_1:{
                    irDiode.setHigh();
					hwlib::wait_us(longWait);
                    irDiode.setLow();
					hwlib::wait_us(shortWait);
                    state = states::SET_BIT;
                    break;
                }
            }
        }
    }
};
#endif //SENDTASK_HPP