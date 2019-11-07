#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "hwlib.hpp"

/// @file
/// \brief
/// display class
/// \details
/// this is the boundary object which implements the functions to actually write to the display.
class Display{
private:
    hwlib::target::pin_oc& scl; //< scl pin for the i2c bus
    hwlib::target::pin_oc& sda; //< sda pin for the i2c bus
    hwlib::font_default_8x8 font;//< the font that is written on the display
    hwlib::i2c_bus_bit_banged_scl_sda mainBus;//< i2c bus that needs both the pins
    hwlib::glcd_oled oled; //< the oled screen on which information is displayed
    hwlib::terminal_from terminal;//< the terminal that holds both the font and the oled
public:
    ///\brief
    /// constructor
    ///\details
    /// It constructs its own font, oled and terminal you can call it using Display(), two paramaters needed, the SDA en SCL pin.
    Display(
		hwlib::target::pin_oc& sda,
		hwlib::target::pin_oc& scl
	):
		scl(scl),
		sda(sda),
		font(),
		mainBus(scl,sda),
		oled(mainBus),
		terminal(oled,font)
    {};
	
    ///\brief
    /// function to show the message. It writes its paramater on the screen.
    template<typename T>
    void showMessage(T text){
		terminal << text;
    	terminal.flush();
	};

	// template<typename T=size_t>
	// void showMessage(T text){
	// 	terminal << hwlib::dec << text;
	// 	terminal.flush();
	// }
};
#endif // DISPLAY_HPP