#ifndef BUZZERTASK_HPP
#define BUZZERTASK_HPP
// #include "../rtos/rtos.hpp"
#include "rtos.hpp"
#include "Buzzer.hpp"

///@file
///\brief
/// Buzzer task class
///\details
/// This task uses Rtos to switch tasks. It can use its own Buzzer to make different sounds calling the makeSound member function.
class BuzzerTask : public rtos::task<>{
public:
    ///\brief
    /// public class with sounds. When the memberfunction makeSound is called, you need to give an entry from this enumerator as its paramater.
    enum class sounds{startEndSound,hitSound};

    ///\brief
    /// constructor for the BuzzerTask
    ///\details
    /// this constructor needs a reference to a hwlib pin_out
    BuzzerTask(hwlib::target::pin_out& buzzerPin) :
    task("buzzer task"),
    buzzerFlag(this,"buzzer flag"),
    buzzerPool("buzzer pool"),
    buzzer(buzzerPin)
    {};

    ///\brief
    /// Member function that set a flag and writes a pool. The parameter needs to be of the enumerator sounds. When this function is called, this task
    /// will start to make the specified sound while still being able to switch between tasks
    void makeSound(sounds sound);

    void main() override{
        while(1){
            switch(state){
                case states::idle:{
                    auto ev = wait(buzzerFlag);
                    if (ev == buzzerFlag){
                        sound = buzzerPool.read();
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
                    }
                    state = states::idle;
                    break;
                }
            }
        }
    }

private:
    sounds sound = sounds::startEndSound;
    rtos::flag buzzerFlag; //< flag that is to be set when someone writes in the pool
    rtos::pool<sounds> buzzerPool; //< pool that holds which sound has to be played
    Buzzer buzzer; //< the boundary buzzer object
    enum class states{idle, makeSound}; //< enumerator that holds the sounds, one of these sounds need to be given as a paraamater to the makeSound function
    states state = states::idle; //< this is the state on which the task switches
};
#endif //BUZZERTASK_HPP