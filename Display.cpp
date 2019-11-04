#include "Display.hpp"

void Display::showMessage(const hwlib::string_base& message){
    terminal.clear();
    terminal.cursor_set(hwlib::xy(0,0));
    terminal << message;
    terminal.flush();
    //oled.flush();
}