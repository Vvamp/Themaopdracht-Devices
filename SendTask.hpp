#ifndef SENDTASK_HPP
#define SENDTASK_HPP
#include "../hwlib/library/hwlib.hpp"
#include "../rtos/rtos.hpp"
#include "IrDiode.hpp"

class SendTask : public rtos::task<>{
private:
    rtos::flag comFlag;
    rtos::pool<uint16_t> comPool;

    IrDiode irDiode;

    uint16_t shortWait = 800;
    uint16_t = 1600;
    uint16_t message = 0;
    uint8_t counter = 0;

    enum class states{idle,checkSum,setBit,send0,send1};
    states state = states::idle;

public:
    SendTask(hwlib::target::pin_out& p):
    comFlag(this,"send command flag"),
    comPool(this,"command pool"),
    irDiode(p)
    {};

    void setComFlag();
    void writeComPool(uint16_t command);
    void checkSum();

    void main() override{
        while(1){
            switch (state){
                case states::idle:{
                    auto ev = wait(comFlag);
                    if (ev == comFlag){
                        message = comPool.read();
                        state = states::checkSum;
                        break;
                    }
                    break;
                }

                case states::checkSum:{
                    checkSum();
                    state = states::setBit;
                    counter = 0;
                    break;
                }

                case states::setBit:{
                    uint8_t bit = message >> 15;
                    message <<= 1;
                    counter++;
                    if (counter == 16){
                        state = states::idle;
                        break;
                    }
                    else{
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