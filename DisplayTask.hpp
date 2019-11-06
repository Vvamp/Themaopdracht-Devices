#ifndef DISPLAYTASK_HPP
#define DISPLAYTASK_HPP

#include "Display.hpp"

#include "rtos.hpp"
#include "hwlib.hpp"

/// @file
/// \brief
/// Display task
/// \details
/// This class is the RTOS task which uses a display, flag and pool to write to an oled screen.
class DisplayTask : public rtos::task<>{
private:
	Display display; 							//< its own display class object
    rtos::flag displayFlag; 					//< flag to let the display know there is new information available in the pool
    rtos::pool<hwlib::string<130>> displayPool; //< pool which holds strings
    enum class states{IDLE,write};				//< enumerator that holds the states in which the rtos task can be in
    states state = states::IDLE;				//< the state on which the task switches
public:
    /// \details
    /// constructor
    /// \brief
    ///constructor for the display task, it needs a hwlib pin_oc sda and scl pin to construct
    DisplayTask(
		hwlib::target::pin_oc & sda,
		hwlib::target::pin_oc & scl
	):
		task(100,"Display task"),
		display(sda,scl),
		displayFlag(this,"display flag"),
		displayPool("display pool")
    {
		hwlib::string<2> x = "\f";
		// x.clear() << "\f";
        display.showMessage(x);
	};

    /// \brief
    ///function to set the display flag
    void setDisplayFlag();

    /// \brief
    ///function to write in the display pool, it writes its paramater in the pool
    template<unsigned int N>
    void writeDisplayPool(hwlib::string<N>&message){
        displayPool.write(message);
        setDisplayFlag();
    };

    /// \brief
    ///function to cout the message
    void showMessage();

    void main() override{
        while(true){
            switch(state){
                case states::IDLE:{
                    auto ev = wait(displayFlag);
                    if (ev == displayFlag){
                        state = states::write;
                        break;
                    }
                    break;
                }

                case states::write:{
                    showMessage();
                    state = states::IDLE;
                    break;
                }
            }
        }
    }
};
#endif //DISPLAYTASK_HPP