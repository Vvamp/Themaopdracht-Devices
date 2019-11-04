#ifndef KeyboardListener_hpp
#define KeyboardListener_hpp

/// @file
///\brief
///The abstract keyboardlistener class.
///\details
///Contains an enum of buttons, with their corresponding keycode values that the hwlib::keyboard object sends.
class KeyboardListener{
public:
	///\brief
	///The Buttons enum. '0' is btn0, 'A' is btnA, etc.
	///\details
	///Please note: the '*' is called 'btnStar' and '#' is called btnHashtag.
	enum Buttons{
		btn0 = '0',
		btn1 = '1',
		btn2 = '2',
		btn3 = '3',
		btn4 = '4',
		btn5 = '5',
		btn6 = '6',
		btn7 = '7',
		btn8 = '8',
		btn9 = '9',

		btnA = 'A',
		btnB = 'B',
		btnC = 'C',
		btnD = 'D',

		btnStar = '*',
		btnHashtag = '#'
	};


	///\brief
	///This virtual function gets called with the button called 'knopID'/
	virtual void buttonPressed(Buttons knopID) = 0;
};

#endif // KeyboardListener_hpp