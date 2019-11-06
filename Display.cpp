#include "Display.hpp"

void Display::showMessage(const char* message){
    terminal.clear();
    terminal.cursor_set(hwlib::xy(0,0));
    terminal << message;
    terminal.flush();
}