#ifndef IRDIODE_HPP
#define IRDIODE_HPP
// #include "../hwlib/library/hwlib.hpp"
#include "hwlib.hpp"

///\brief
///IrDiode class for setting the IR sender pin high or low.
class IrDiode{
private:
    hwlib::pin_out& diodePin;//< member variable that holds the sender pin
public:
    ///\brief
    /// constructor
    ///\details
    ///this constructor only needs a reference to a hwlib::pin_out in his parameters to compile. The constructor also sets the pin low during start up
    IrDiode(hwlib::target::pin_out& diodePin):
    diodePin(diodePin){
        diodePin.write(0);
        diodePin.flush();
    };

    ///\brief
    /// function to set the IR pin high.
    void setHigh();
    ///\brief
    /// function to set the IR pin low.
    void setLow();
};
#endif //IRDIODE_HPP