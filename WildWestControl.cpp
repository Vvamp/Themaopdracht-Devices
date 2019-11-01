#include "WildWestControl.hpp"

void WildWestControl::setMatchTime( size_t time ){
    matchTimer = time;
};

bool WildWestControl::reduceMatchTime(){
    
    // Decrease matchTime
    matchTime--;

    // If matchTime is equal or lower then 0 seconds,
    // Start the draw and shooting
    matchTime <= 0 ? return false : return true;

    if( matchTime <= 0 ){
        hwlib::string currentMessage = "SHOOT!";
        WildWestControl.changeMessage( currentMessage );
        return false;

    } else {
        hwlib::string currentMessage = "READY?";
        WildWestControl.changeMessage( currentMessage );
        return true;
    }

};

bool WildWestControl::addDrawTime(){

    // Increase drawTime
    drawTime++;
    
    // If drawTime is equal or past 60 seconds,
    // End game
    if( drawTime >= 60 ){
        hwlib::string currentMessage = "YOU WON!";
        WildWestControl.changeMessage( currentMessage );
        return true;

    } else {
        hwlib::string currentMessage = "SHOOT!";
        WildWestControl.changeMessage( currentMessage );
        return false;
    }

};

size_t WildWestControl::getMatchTime(){
    return matchTime;
};

size_t WildWestControl::getDrawTime(){
    return drawTime;
};

void WildWestControl::changeMessage( hwlib::string message ){
    gameMessage = message;
}

hwlib::string WildWestControl::toDisplay(){
    hwlib::string = gameMessage;
};

// void WildWestControl::setMatchResults(){

// };