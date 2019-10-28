#include "DisplayTask.hpp"

DisplayTask::setDisplayFlag(){
    displayFlag.set();
}

DisplayTask::writeDisplayPool(hwlib::string message){
    displayPool.write(message);
    setDisplayFlag();
}