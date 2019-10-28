#include "Display.hpp"

void Display::showMessage(hwlib::string message){
    terminal << message;
    oled.flush();
}

void Display::clear(){
    oled.clear();
    oled.flush();
}