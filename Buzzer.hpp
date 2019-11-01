#ifndef BUZZER_HPP
#define BUZZER_HPP
// #include "../hwlib/library/hwlib.hpp"
#include "hwlib.hpp"
/// @file
///\brief
/// Buzzer boundary class
///\details
/// this class implements the functionality that is needed to make sounds with a buzzer.
class Buzzer{
private:
    hwlib::target::pin_out buzzerPin;//<pin on which the buzzer is connected
public:

    ///\brief
    /// constructor for the buzzer class
    ///\details
    /// this constructor needs no paramaters, it constructs its own pin (d10)
    Buzzer():
    buzzerPin(hwlib::target::pins::d10)
    {};

    ///\brief
    /// set the buzzer pin on
    void soundOn();
    ///\brief
    /// set the buzzer pin low
    void soundOff();
};

#endif //BUZZER_HPP