#include "RunGameControl.hpp"

void RunGameControl::setGameTime(size_t time){
	gameTime = time;
};

void RunGameControl::toDisplay(hwlib::string<200> & msg){
	/*
		Gametime gaan bitshfiten, de bit(s) naar een tijdchar casten
		Dit in een string pleuren en dat in een strnig zetten
		
	*/
	size_t asciiOffset = 48;
	uint8_t smallNumber = (gameTime < 10) ? gameTime : gameTime%10;
	uint8_t bigNumber = (gameTime > 9) ? (gameTime-smallNumber)/10 : 0; 
	char[2] valChars;
	valChars[0] = bigNumber;
	valChars[1] = smallNumber;
	hwlib::string<10> timeMsg = "Tijd : ";
	hwlib::string<2> valueMsg = valChars[0] + valChars[1];
	hwlib::string<32> playerMsg = "\nPlayer ID : " + player.getPlayerID();
	hwlib::string<32> scoreMsg = "\nScore : " + player.getScore();
	msg += timeMsg;
	msg += valueMsg;
	msg += playerMsg;
	msg += scoreMsg;
};

bool RunGameControl::reduceTime(){
	gameTime--;
	return bool(gameTime);
};

size_t RunGameControl::getTime(){
	return gameTime;
};

hwlib::string<4> RunGameControl::numberToString(const size_t n){
	hwlib::string<4> returnString;
	const uint16_t originalNumber = n;
	uint16_t thousandsNumber = 0;
	uint16_t hundredsNumber = 0;
	uint16_t tensNumber = 0;
	uint16_t lowerNumber = 0;
	uint16_t counter = 0;
    uint8_t caseSwitcher = 0;
    if (n>=1000){
        caseSwitcher = 0;
    }
    else if (n >= 100){
        caseSwitcher = 1;
    }
    else if (n >= 10){
        caseSwitcher = 2;
    }
    else if (n < 10){
        caseSwitcher = 3;
    }
    
	switch (caseSwitcher){
		case 0:
			//fish out the thousands
			counter+=1000;
			auto temp = originalNumber % 1000;
			if (temp == 0){
				thousandsNumber = originalNumber;
				break;
			}
			thousandsNumber = originalNumber - temp;
		case 1:
			//fish out the hundreds
			counter+=100;
			hundredsNumber = originalNumber - thousandsNumber;
			auto temp = hundredsNumber%100;
			if (temp == 0){
				hundredsNumber = originalNumber - thousandsNumber;
				break;
			}
			hundredsNumber -= temp;
		case 2:
			//fish out the tens
			counter+=10;
			tensNumber = originalNumber - thousandsNumber - hundredsNumber;
			auto temp = tensNumber%10;
			if (temp == 0){
				tensNumber = originalNumber - thousandsNumber - hundredsNumber;
				break;
			}
			tensNumber -= temp;
		case 3:
			//fish out the lower number
			counter+=1;
			lowerNumber = originalNumber - thousandsNumber - hundredsNumber - tensNumber;
			break;
	}
	switch (caseSwitcher){
		case 0:
			thousandsNumber /= 1000;
			hundredsNumber /= 100;
			tensNumber /= 10;
			thousandsNumber += 48;
			hundredsNumber += 48;
			tensNumber += 48;
			lowerNumber += 48;
			returnString << (char)thousandsNumber << (char)hundredsNumber << (char)tensNumber << (char)lowerNumber;
			break;
		case 1:
			hundredsNumber /= 100;
			tensNumber /= 10;
			hundredsNumber += 48;
			tensNumber += 48;
			lowerNumber += 48;
			returnString << (char)hundredsNumber << (char)tensNumber << (char)lowerNumber;
			break;
		case 2:
			tensNumber /= 10;
			hundredsNumber += 48;
			tensNumber += 48;
			lowerNumber += 48;
			returnString << (char)tensNumber << (char)lowerNumber;
			break;
		case 3:
			lowerNumber += 48;
			returnString << (char)lowerNumber;
			break;
	}
	return returnString;

}