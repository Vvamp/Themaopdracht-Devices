#include "TransferHitsControl.hpp"

void TransferHitsControl::exportPlayer(){
    int* assailantsArr = player.getAssailants();
    int i = 0;
    int hitBy[9] = {0};
    while(true){
        if(assailantsArr[i] == 0) break;
        hitBy[assailantsArr[i-1]]++;
        i++;
    }

    // Send player stats to the connected pc terminal
    hwlib::cout << "====== GAME RESULTS =====" << hwlib::endl;
    hwlib::cout << "Player_ID: " << player.getPlayerID() << hwlib::endl;
    hwlib::cout << "Score: " << player.getScore() << hwlib::endl;
    hwlib::cout << "Hits: " << hwlib::endl;

    for( int i = 0; i < 9; i++ ){
        hwlib::cout << " \t" << i+1 << " : " << hitBy[i] << hwlib::endl;

    };
    hwlib::cout << "=========================" << hwlib::endl;
};