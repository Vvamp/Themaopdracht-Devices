#ifndef TILTSENSOR_HPP
#define TILTSENSOR_HPP
#include "hwlib.hpp"

/// @file
/// \brief
/// TiltSensor
/// \details
/// This class implements the the functionallity of the tiltsensor.
class TiltSensor{
private:
    hwlib::target::pin_in tiltSensor;

public:

    ///\brief
    /// TiltSensor constructor
    /// \details
    /// The TiltSensor constuctor needs a hwlib::pin_in.
    /// this pin is used for the tilt sensor
    TiltSensor( hwlib::pin_in & tiltSensor ):
        tiltSensor( tiltSensor )
    {};

    /// \brief
    /// Get the position of the tiltsensoro
    size_t getTilt();

}

#endif //TILTSENSOR_HPP