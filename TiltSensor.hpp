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
    /// The TiltSensor constuctor needs no parameters.
    TiltSensor():
        tiltSensor( hwlib::target::pins:d13 )
    {};

    /// \brief
    /// Get the position of the tiltsensoro
    size_t getTilt();

}

#endif //TILTSENSOR_HPP