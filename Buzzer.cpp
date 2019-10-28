#include "Buzzer.hpp"

void Buzzer::soundOn(){
    buzzerPin.write(1);
    buzzerPin.flush();
}

void Buzzer::soundOff(){
    buzzerPin.write(0);
    buzzerPin.flush();
}