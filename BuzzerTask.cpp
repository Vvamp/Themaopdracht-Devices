#include "BuzzerTask.hpp"

void BuzzerTask::makeSound(sounds sound){
    buzzerPool.write(sound);
    buzzerFlag.set();
}