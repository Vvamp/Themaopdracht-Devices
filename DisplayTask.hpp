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
    rtos::flag displayFlag2;                    //< flag to let the display know there is new integer information available in the pool
    rtos::pool<const char *> displayPool; //< pool which holds strings
    rtos::pool<size_t> displayPool2;            //< pool that holds numbers
    enum class states{IDLE,write1,write2};				//< enumerator that holds the states in which the rtos task can be in
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
        displayFlag2(this,"display flag2"),
		displayPool("display pool"),
        displayPool2("display pool 2")
    {
		hwlib::string<2> x = "\f";
		// x.clear() << "\f";
        display.showMessage(x);
	};

    /// \brief
    ///function to set the display flag
    void setDisplayFlag();

     /// \brief
    ///function to set the display flag
    void setDisplayFlag2();

    /// \brief
    ///function to write in the display pool, it writes its paramater in the pool
    void writeDisplayPool(char * message){
        displayPool.write(message);
        setDisplayFlag();
    };

    void writeDisplayPool(size_t message){
        displayPool2.write(message);
        setDisplayFlag2();
    };

    /// \brief
    ///function to cout the message
    template<typename T>
    void showMessage(T message){
        display.showMessage(message);
    };


    void main() override{
        while(true){
            switch(state){
                case states::IDLE:{
                    auto ev = wait(displayFlag + displayFlag2);
                    if (ev == displayFlag){
                        state = states::write1;
                    } else if (ev == displayFlag2){
                        state = states::write2;
                    }
                    break;
                }

                case states::write1:{
                    auto message = displayPool.read();
                    showMessage(message);
                    state = states::IDLE;
                    break;
                }

                case states::write2:{
                    auto message = displayPool2.read();
                    showMessage(message);
                    state = states::IDLE;
                    break;
                }
            }
        }
    }
};
#endif //DISPLAYTASK_HPP