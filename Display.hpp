#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include "../hwlib/library/hwlib.hpp"
/// @file
/// \brief
/// display class
/// \details
/// this is the boundary object which implements the functions to actually write to the display. 

class Display{
private:
    hwlib::target::pin_oc scl;
    hwlib::target::pin_oc sda;
    hwlib::font_default_16x16 font;
    hwlib::i2c_bus_bit_banged_scl_sda mainBus;
    hwlib::glcd_oled oled;
    hwlib::terminal_from terminal;
public:
    ///\brief
    /// constructor 
    ///\details
    /// It constructs its own arduino pins, font,
    /// oled and terminal you can call it using Display(), no parameters needed.
    Display() : 
    scl(hwlib::target::pins::scl),
    sda(hwlib::target::pins::sda),
    font(),
    mainBus(scl,sda),
    oled(mainBus),
    terminal(oled,font) 
    {};
    ///\brief
    /// function to show the message. It writes its paramater on the screen.
    void showMessage(hwlib::string message);
};
#endif // DISPLAY_HPP