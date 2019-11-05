#include "SendTask.hpp"

void SendTask::setComFlag(){
    comFlag.set();
}

void SendTask::writeComPool(uint16_t command){
    comPool.write(command);
}

void SendTask::checkSum(uint16_t & _message){
    uint16_t temp = 0;
    uint8_t bit1 = 0;
    uint8_t bit2 = 0;
    for (uint8_t i = 0; i < 5; i ++){
        temp = _message << (i+1);
        bit1 = temp >> 15;
        temp = _message << (i+6);
        bit2 = temp >> 15;
        temp = bit1 ^ bit2;
        temp <<= (4-i);
        _message |= temp;
    }
}