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
template<unsigned int N = 1 >
class Keyboard{
private:
	hwlib::matrix_of_switches matrix;		///<The matrix of output and input pins for the keyboard.

	hwlib::keypad<16> keypadIn;				///<The keyboard object made up of 16 characters.

	unsigned int pointer = 0;					///<The current object to be placed in the KeyboardListener array. Max of 3.
	KeyboardListener * listeners[N];		///<An array of keyboardListeners. All listeners in this array get their update() function called every x ms.

public:
	///\brief
	///The default constructor for the keyboard class.
	///\details
	///The constructor initializes a keyboard object with the Arduino Due pins a0-a7.
	///These are put into their corresponding objects(a0 - a3 become pin_oc's, a4-a7 become pin_ins).
	///The pin_oc's get put into the out_port and the pin_in's get put into the in_port.
	///Finally, the matrix made from the out_port and in_port it used to initialize the keypad, along with the keyset '123A456B789C*0#D'
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
		KeyboardListener::Buttons buttonPressed;

		// Store the corresponding Buttons enum value in buttonPressed.
		switch(keyPressed){
			case KeyboardListener::btn0:
				buttonPressed=KeyboardListener::btn0;
			break;
			case KeyboardListener::btn1:
				buttonPressed=KeyboardListener::btn1;
			break;
			case KeyboardListener::btn2:
				buttonPressed=KeyboardListener::btn2;
			break;
			case KeyboardListener::btn3:
				buttonPressed=KeyboardListener::btn3;
			break;
			case KeyboardListener::btn4:
				buttonPressed=KeyboardListener::btn4;
			break;
			case KeyboardListener::btn5:
				buttonPressed=KeyboardListener::btn5;
			break;
			case KeyboardListener::btn6:
				buttonPressed=KeyboardListener::btn6;
			break;
			case KeyboardListener::btn7:
				buttonPressed=KeyboardListener::btn7;
			break;
			case KeyboardListener::btn8:
				buttonPressed=KeyboardListener::btn8;
			break;
			case KeyboardListener::btn9:
				buttonPressed=KeyboardListener::btn9;
			break;

			case KeyboardListener::btnA:
				buttonPressed=KeyboardListener::btnA;
			break;
			case KeyboardListener::btnB:
				buttonPressed=KeyboardListener::btnB;
			break;
			case KeyboardListener::btnC:
				buttonPressed=KeyboardListener::btnC;
			break;
			case KeyboardListener::btnD:
				buttonPressed=KeyboardListener::btnD;
			break;

			case KeyboardListener::btnStar:
				buttonPressed=KeyboardListener::btnStar;
			break;
			case KeyboardListener::btnHashtag:
				buttonPressed=KeyboardListener::btnHashtag;
			break;
		}

		// Call each buttonPressed function in the array of listeners.
		for(KeyboardListener* iListener : listeners){
			iListener->buttonPressed(buttonPressed);
		}
	};

	///\brief
	///Add a KeyboardListener to the KeyboardListener array. Max of 3.
	///\details
	///When added, the listener gets their buttonPressed function called.
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