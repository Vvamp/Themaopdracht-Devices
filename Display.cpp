#include "Display.hpp"

void Display::showMessage(hwlib::string message){
    terminal.clear();
    terminal.cursor_set(hwlib::xy(0,0));
    terminal << message;
    terminal.flush();
}