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
    hwlib::target::pin_out& buzzerPin;//<pin on which the buzzer is connected
public:

    ///\brief
    /// constructor for the buzzer class
    ///\details
    /// this constructor needs a reference to a hwlib::pin_out
    Buzzer():
    buzzerPin(hwlib::target::pin_out& buzzerPin) :
    buzzerPin(buzzerPin)
    {};

    ///\brief
    /// set the buzzer pin on
    void soundOn();
    ///\brief
    /// set the buzzer pin low
    void soundOff();
};

#endif //BUZZER_HPP