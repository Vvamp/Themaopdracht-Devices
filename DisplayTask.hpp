#ifndef DISPLAYTASK_HPP
#define DISPLAYTASK_HPP
// #include "../rtos/rtos.hpp"
#include "rtos.hpp"
// #include "../hwlib/library/hwlib.hpp"
#include "hwlib.hpp"
#include "Display.hpp"
/// @file
/// \brief
/// Display task
/// \details
/// This class is the RTOS task which uses a display, flag and pool to write to an oled screen.
class DisplayTask : public rtos::task<>{
private:
    rtos::flag displayFlag; //< flag to let the display know there is new information available in the pool
    rtos::pool<hwlib::string> displayPool; //< pool which holds strings
    Display display; //< its own display class object
    enum class states{idle,write};//< enumerator that holds the states in which the rtos task can be in
    states state = states::idle;//< the state on which the task switches
public:
    /// \details
    /// constructor
    /// \brief
    ///constructor for the display task
    DisplayTask():
    task("Display task"),
    displayFlag(this,"display flag"),
    displayPool(this,"display pool"),
    display()
    {};
    /// \brief
    ///function to set the display flag
    void setDisplayFlag();
    /// \brief
    ///function to write in the display pool, it writes its paramater in the pool
    void writeDisplayPool(hwlib::string message);
    /// \brief
    ///function to cout the message
    void showMessage();

    void main() override{
        while(1){
            switch(state){

                case states::idle:{
                    auto ev = wait(displayFlag);
                    if (ev == displayFlag){
                        state = states::write;
                        break;
                    }
                    break;
                }

                case states::write:{
                    showMessage();
                    state = states::idle;
                    break;
                }
            }

        }
    }

};
#endif //DISPLAYTASK_HPP