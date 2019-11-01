#ifndef Keyboard_hpp
#define Keyboard_hpp

#include "KeyboardListener.hpp"
#include "hwlib.hpp"

/// @file
/// \brief
/// A keyboard object 
/// \details
/// It calls the update() function in its private KeyboardListeners array.
/// 3 of these keyboardlisteners can be added by the public addKeyboardListener() function.
class Keyboard{
private:
	hwlib::target::pin_oc out0;				///<An output pin for the keypad matrix.
	hwlib::target::pin_oc out1;				///<An output pin for the keypad matrix.
	hwlib::target::pin_oc out2;				///<An output pin for the keypad matrix.
	hwlib::target::pin_oc out3;				///<An output pin for the keypad matrix.
	
	hwlib::target::pin_in in0;				///<An input pin for the keypad matrix.
	hwlib::target::pin_in in1;				///<An input pin for the keypad matrix.
	hwlib::target::pin_in in2;				///<An input pin for the keypad matrix.
	hwlib::target::pin_in in3;				///<An input pin for the keypad matrix.

	hwlib::port_oc_from out_port;			///<An output port for the keypad matrix.
	hwlib::port_in_from in_port;			///<An input port for the keypad matrix.

	hwlib::matrix_of_switches matrix;		///<The matrix of output and input pins for the keyboard.

	hwlib::keypad<16> keypadIn;				///<The keyboard object made up of 16 characters.

	int arrayPointer = 0;					///<The current object to be placed in the KeyboardListener array. Max of 3.
	KeyboardListener & listeners[3];		///<An array of keyboardListeners. All listeners in this array get their update() function called every x ms.

public:
	///\brief 
	///The default constructor for the keyboard class. 
	///\details
	///The constructor initializes a keyboard object with the Arduino Due pins a0-a7. 
	///These are put into their corresponding objects(a0 - a3 become pin_oc's, a4-a7 become pin_ins).
	///The pin_oc's get put into the out_port and the pin_in's get put into the in_port. 
	///Finally, the matrix made from the out_port and in_port it used to initialize the keypad, along with the keyset '123A456B789C*0#D' 
	Keyboard(hwlib::port_oc_from out_port, hwlib::port_in_from in_port) :
		matrix(out_port, in_port),
		keypadIn(matrix, "123A456B789C*0#D")
	{};

	///\brief
	///This function calls the 'buttonPressed' function of each KeyboardListener in the listeners array with the corresponding button enum.
	void update();

	///\brief
	///Add a KeyboardListener to the KeyboardListener array. Max of 3.
	///\details
	///When added, the listener gets their buttonPressed function called.
	void addKeyboardListener(KeyboardListener * listener);

};
#endif // Keyboard_hpp