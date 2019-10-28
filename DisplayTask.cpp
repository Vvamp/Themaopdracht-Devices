#include "DisplayTask.hpp"

DisplayTask::setDisplayFlag(){
    displayFlag.set();
}

DisplayTask::writeDisplayPool(hwlib::string message){
    displayPool.write(message);
    setDisplayFlag();
}

DisplayTask::showMessage(){
    auto message = displayPool.read();
    display.showMessage(message);
}