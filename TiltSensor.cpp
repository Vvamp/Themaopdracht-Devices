#include "TiltSensor.hpp"

size_t TiltSensor::getTilt(){

    tiltSensor.refresh();
    size_t tiltPosition = tiltSensor.read();

    return tiltPosition;

};