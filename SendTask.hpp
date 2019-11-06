#ifndef SENDTASK_HPP
#define SENDTASK_HPP
// #include "../hwlib/library/hwlib.hpp"
#include "hwlib.hpp"
// #include "../rtos/rtos.hpp"
#include "rtos.hpp"
#include "IrDiode.hpp"
///@file
///\brief
/// Send task class
///\details
/// Class that inherits from rtos task. It waits for the comflag to be set, it will then read the command pool and send the command through its IR sender.
/// the command needs to be 16 bits.
class SendTask : public rtos::task<>{
private:
    rtos::flag comFlag;//< flag that need to be set when something is written in the pool
    rtos::pool<uint16_t> comPool; //< pool in which commands can be written
    rtos::timer timer;

    IrDiode irDiode; //< object from the IR diode class.

    uint16_t shortWait = 795; //< the wait short wait time between turning on and off the IR sender
    uint16_t longWait = 1595; //< the long wait time between turning on and off the IR sender
    uint16_t message = 0; //< variable in which the message is set when the pool is read
    uint8_t counter = 0; //< counter that is used to count

    enum class states{idle,setBit,send0,send1};//<enumerator that holds the names on which the task switches
    states state = states::idle;//< member variable on which the task switches

public:
    ///\brief
    /// constructor
    ///\details
    /// the constructor only needs a hwlib pin out to be able to function.
    SendTask(
		hwlib::target::d2_36kHz& p
	):
		task(5,"Send task"),
		comFlag(this,"send command flag"),
		comPool("command pool"),
		timer(this,"send timer"),
		irDiode(p)
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
        while(1){
            switch (state){
                case states::idle:{
                    auto ev = wait(comFlag);
                    if (ev == comFlag){
                        message = comPool.read();
                        checkSum(message);
                        counter = 0;
                        state = states::setBit;
                        break;
                    }
                    break;
                }

                case states::setBit:{
                    uint8_t bit = message >> 15;
                    message <<= 1;
                    counter++;
                    if (counter == 17){
                        state = states::idle;
                        break;
                    } else {
						irDiode.setLow();
                        if (bit == 0){
                            state = states::send0;
                            break;
                        }
                        else{
                            state = states::send1;
                            break;
                        }
                    }
                    break;
                }

                case states::send0:{
                    irDiode.setHigh();
					hwlib::wait_us(800);
                    irDiode.setLow();
					hwlib::wait_us(1600);
                    state = states::setBit;
                    break;
                }

                case states::send1:{
                    irDiode.setHigh();
					hwlib::wait_us(1600);
                    irDiode.setLow();
					hwlib::wait_us(800);
                    state = states::setBit;
                    break;
                }
            }
        }
    }
};
#endif //SENDTASK_HPP