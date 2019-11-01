#include "SendTask.hpp"

void SendTask::setComFlag(){
    comFlag.set()
}

void SendTask::writeComPool(size_t command){
    comPool.write(command);
}

void SendTask::checkSum(){
    uint8_t temp = 0;
    uint8_t bit1 = 0;
    uint8_t bit2 = 0;
    for (uint8_t i = 0; i < 5; i ++){
        temp = message << i+1;
        bit1 = temp >> 15;
        temp = message << i+6;
        bit2 = temp >> 15;
        temp = bit1 ^ bit2;
        temp <<= 4-i;
        message |= temp;
    }
}