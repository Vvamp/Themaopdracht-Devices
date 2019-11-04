#include "DisplayTask.hpp"

void DisplayTask::setDisplayFlag(){
    displayFlag.set();
}

void DisplayTask::showMessage(){
    auto message = displayPool.read();
    display.showMessage(message);
}