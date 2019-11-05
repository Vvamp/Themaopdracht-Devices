#include "IrDiode.hpp"

void IrDiode::setHigh(){
    diodePin.write(1);
    diodePin.flush();
}

void IrDiode::setLow(){
    diodePin.write(0);
    diodePin.flush();
};