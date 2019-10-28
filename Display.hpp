#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include "../hwlib/library/hwlib.hpp"

class Display{
private:
    hwlib::target::pin_oc scl;
    hwlib::target::pin_oc sda;
    hwlib::font_default_16x16 font;
    hwlib::i2c_bus_bit_banged_scl_sda mainBus;
    hwlib::glcd_oled oled;
    hwlib::terminal_from terminal;
public:
    //constructor
    Display() : 
    scl(hwlib::target::pins::scl),
    sda(hwlib::target::pins::sda),
    font(),
    mainBus(scl,sda),
    oled(mainBus),
    terminal(oled,font) 
    {};

    void showMessage(hwlib::string message);
    void clear();
};
#endif // DISPLAY_HPP