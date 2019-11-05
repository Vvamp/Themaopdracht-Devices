#include "IrDiode.hpp"

void IrDiode::setHigh(){
    diodePin.set(1);
    diodePin.flush();
}

void IrDiode::setLow(){
    diodePin.set(0);
    diodePin.flush();
};