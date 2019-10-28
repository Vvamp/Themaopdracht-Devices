#ifndef BUZZERTASK_HPP
#define BUZZERTASK_HPP
#include "../rtos/rtos.hpp"
#include "Buzzer.hpp"

class BuzzerTask : public rtos::task<>{
public:
    enum class sounds{startEndSound,hitSound};

    ///\brief
    /// constructor for the BuzzerTask
    ///\details
    /// this constructor does not need any paramaters
    BuzzerTask() :
    task("buzzer task"),
    buzzerFlag(this,"buzzer flag"),
    buzzerPool(this,"buzzer pool"),
    buzzer()
    {};

    void makeSound(sounds sound);

    void main() override{
        while(1){
            switch(state){
                case states::idle:{
                    auto ev = wait(buzzerFlag);
                    if (ev == buzzerFlag){
                        auto sound = buzzerPool.read();
                        state = states::makeSound;
                        break;
                    }
                }
                case states::makeSound:{
                    if (sound == sounds::startEndSound)
                    {
                        //long first beep
                        buzzer.soundOn();
                        hwlib::wait_ms(1000);
                        buzzer.soundOff();
                        hwlib::wait_ms(333);

                        //short beep 1
                        buzzer.soundOn();
                        hwlib::wait_ms(333);
                        buzzer.soundOff();
                        hwlib::wait_ms(333);

                        //short beep 2
                        buzzer.soundOn();
                        hwlib::wait_ms(333);
                        buzzer.soundOff();
                        hwlib::wait_ms(333);

                        //short beep 3
                        buzzer.soundOn();
                        hwlib::wait_ms(333);
                        buzzer.soundOff();
                        hwlib::wait_ms(333);
                    }
                    else if (sound == sounds::hitSound)
                    {
                        buzzer.soundOn();
                        hwlib::wait_ms(100);
                        buzzer.soundOff();
                        hwlib::wait_ms(100);

                        buzzer.soundOn();
                        hwlib::wait_ms(100);
                        buzzer.soundOff();
                        hwlib::wait_ms(100);

                        buzzer.soundOn();
                        hwlib::wait_ms(100);
                        buzzer.soundOff();
                        hwlib::wait_ms(100);
                    }
                    state = states::idle;
                    break;
                }
            }
        }
    }

private:
    rtos::flag buzzerFlag;
    rtos::pool<sounds> buzzerPool; 
    Buzzer buzzer;
    enum class states{idle, makeSound};
    states state = states::idle;
}
#ifndef //BUZZERTASK_HPP