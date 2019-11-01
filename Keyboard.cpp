#include "Keyboard.hpp"
#include "KeyboardListener.hpp"

void Keyboard::addKeyboardListener(KeyboardListener * listener){
	// Return if the pointer points out-of-bounds of the array.
	if(pointer > 3){
		return;
	}
	// Add the listener to the array at index where the pointer points.
	listeners[pointer] = listener;

	// Increment the pointer by 1.
	pointer++;
}

void Keyboard::update(){
	// Get the character pressed on the keyboard, or '\0' if nothing is pressed.
	char keyPressed = keypadIn.pressed();

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
	for(KeyboardListener* listener : listeners){
		listener.buttonPressed(buttonPressed);
	}
}