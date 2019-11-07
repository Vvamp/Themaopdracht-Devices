#ifndef DISPLAYTASK_HPP
#define DISPLAYTASK_HPP

#include "Display.hpp"

#include "rtos.hpp"
#include "hwlib.hpp"

struct gameDisplay{
	size_t time;
	size_t playerID;
	size_t score;
};

struct textDisplay{
	char message[32];
};

/// @file
/// \brief
/// Display task
/// \details
/// This class is the RTOS task which uses a display, flag and pool to write to an oled screen.
class DisplayTask : public rtos::task<>{
private:
	Display display; 							//< its own display class object
    rtos::flag displayFlag; 					//< flag to let the display know there is new information available in the pool
	rtos::flag displayFlagStruct;
	rtos::flag displayFlagNumber;
    rtos::pool<textDisplay> displayPool; //< pool which holds strings
	rtos::pool<size_t> displayPoolNumber;
	rtos::pool<gameDisplay> displayPoolStruct;
    enum class states{IDLE,write1,write2,write3};				//< enumerator that holds the states in which the rtos task can be in
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
		task(500,"Display task"),
		display(sda,scl),
		displayFlag(this,"display flag"),
		displayFlagStruct(this, "display flag struct"),
		displayFlagNumber(this, "display flag uint16_t"),
		displayPool("display pool"),
		displayPoolNumber("display pool uint16_t"),
		displayPoolStruct("display pool struct")
    {
        display.showMessage("\f");
	};

    /// \brief
    ///function to set the display flag
    void setDisplayFlag(){
		displayFlag.set();
	};

	void setDisplayFlagNumber(){
		displayFlagNumber.set();
	}

	void setDisplayFlagStruct(){
		displayFlagStruct.set();
	}

    /// \brief
    ///function to write in the display pool, it writes its paramater in the pool
    void writeDisplayPool(const textDisplay & message){
        displayPool.write(message);
        setDisplayFlag();
    };

	void writeDisplayPool(const uint16_t & message){
		displayPoolNumber.write(message);
		setDisplayFlagNumber();
	}

	void writeDisplayPool(const gameDisplay & message){
		displayPoolStruct.write(message);
		setDisplayFlagStruct();
	}

    /// \brief
    ///function to cout the message
    template<typename T>
    void showMessage(T message){
        display.showMessage(message);
		display.flush();
    };

	void showMessage(const gameDisplay & message){
		display.showMessage("\fTijd : ");
		display.showMessage(message.time);
		display.showMessage("\nPlayer ID : ");
		display.showMessage(message.playerID);
		display.showMessage("\nScore : ");
		display.showMessage(message.score);
		display.flush();
	}


    void main() override{
        while(true){
            switch(state){
                case states::IDLE:{
                    auto ev = wait(displayFlag + displayFlagNumber + displayFlagStruct);
                    if (ev == displayFlag){
                        state = states::write1;
                    } else if (ev == displayFlagNumber){
						state = states::write2;
					} else if (ev == displayFlagStruct){
						state = states::write3;
					}
                    break;
                }

				case states::write1:{
					auto message = displayPool.read();
					showMessage(message.message);
					state = states::IDLE;
					break;
				}

                case states::write2:{
                    auto message = displayPoolNumber.read();
                    showMessage(message);
                    state = states::IDLE;
                    break;
                }

				case states::write3:{
					auto message = displayPoolStruct.read();
					showMessage(message);
					state = states::IDLE;
					break;
				}
            }
        }
    }
};
#endif //DISPLAYTASK_HPP