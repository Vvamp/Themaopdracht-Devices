#ifndef Keyboard_hpp
#define Keyboard_hpp

#include "KeyboardListener.hpp"
#include "hwlib.hpp"

/// @file
/// \brief
/// A keyboard class, representing a physical 16-key keypad.
/// \details
/// It calls the update() function in its private KeyboardListeners array.
/// The class is templated, it takes 1 template argument of the integer.
/// This argument represents the amount of keyboard listeners in the array.
/// If no argument is given, it is 1.
template<unsigned int N = 1 >
class Keyboard{
private:
	hwlib::matrix_of_switches matrix;		///<The matrix of output and input pins for the keyboard.

	hwlib::keypad<16> keypadIn;				///<The keyboard object made up of 16 characters.

	unsigned int pointer = 0;				///<The current object to be placed in the KeyboardListener array. Max of 3.
	KeyboardListener * listeners[N];		///<An array of 'N' keyboardListeners(N being the template argument, default 1). All listeners in this array get their update() function called every x ms.

public:
	///\brief
	///The default constructor for the keyboard class.
	///\details
	///The constructor initializes a keyboard object with a port_oc output port(4 port oc's) and a port_in input port(4 port_in's).
	///These ports get put into a matrix, after which the keypadIn object gets initialized with 'D#0*C987B654A321'.
	Keyboard(
		hwlib::port_oc & out_port,
		hwlib::port_in & in_port
	):
		matrix(out_port, in_port),
		keypadIn(matrix, "D#0*C987B654A321")
	{};

	///\brief
	///This function calls the 'buttonPressed' function of each KeyboardListener in the listeners array with the corresponding button enum.
	void update(){
		// Get the character pressed on the keyboard, or '\0' if nothing is pressed.
		char keyPressed = keypadIn.pressed();
		// hwlib::cout << keyPressed <<"\n";

		// If nothing was pressed, do nothing.
		if(keyPressed == '\0'){
			return;
		}
		int buttonPressed;

		// Store the corresponding Buttons enum value in buttonPressed.
		switch(keyPressed){
			case '0':
				buttonPressed=0;
			break;
			case '1':
				buttonPressed=1;
			break;
			case '2':
				buttonPressed=2;
			break;
			case '3':
				buttonPressed=3;
			break;
			case '4':
				buttonPressed=4;
			break;
			case '5':
				buttonPressed=5;
			break;
			case '6':
				buttonPressed=6;
			break;
			case '7':
				buttonPressed=7;
			break;
			case '8':
				buttonPressed=8;
			break;
			case '9':
				buttonPressed=9;
			break;

			case 'A':
				buttonPressed=10;
			break;
			case 'B':
				buttonPressed=11;
			break;
			case 'C':
				buttonPressed=12;
			break;
			case 'D':
				buttonPressed=13;
			break;

			case '*':
				buttonPressed=14;
			break;
			case '#':
				buttonPressed=15;
			break;
		}

		// Call each buttonPressed function in the array of listeners.
		for(KeyboardListener* iListener : listeners){
			iListener->buttonPressed(buttonPressed);
		}
		hwlib::wait_ms(150);
	};

	///\brief
	///Add a KeyboardListener to the KeyboardListener array. Max of 'N'. 
	///\details
	///When added, the listener gets their buttonPressed function called.
	///N is the template argument, defaults to 1.
	///If the array is already full, the listener given to the function gets thrown away.
	void addKeyboardListener(KeyboardListener * listener){
	// Return if the pointer points out-of-bounds of the array.
	if(pointer > N){
		return;
	}
	// Add the listener to the array at index where the pointer points.
	listeners[pointer] = listener;

	// Increment the pointer by 1.
	pointer++;
	}
};
#endif // Keyboard_hpp