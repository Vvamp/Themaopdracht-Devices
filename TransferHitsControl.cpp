#include "TransferHitsControl.hpp"

void TransferHitsControl::exportPlayer(){

    // Create a struct to collect 
    struct playerHit {
        size_t playerID = 0;
        size_t amount   = 0;
    };

    // Create a list of all players the player has been hit by 
    // and the amount of times the player has been hit by that player
	playerHit hitBy[ 9 ];
	
    int playerCount = 0;

    for( auto hit : player.getAssailants() ){
		// Check if a player is already in the playerHit list
		// If true: increment the amount of hits a player has done
		// If false: add the player to the playerHit list
		bool found = false;
		
		for( int i = 0; i < playerCount; i++ ){

			if( hitBy[i].playerID == hit ){
				hitBy[i].amount++;
				found = true;
				break;
			}
		}

		if( !found ){
			hitBy[playerCount].playerID = hit;
			hitBy[playerCount].amount++;
			playerCount++;
		}
    }

    // Send player stats to the connected pc terminal
    hwlib::cout << "====== GAME RESULTS =====" << hwlib::endl;
    hwlib::cout << "Player_ID: " << player.getPlayerID() << hwlib::endl;
    hwlib::cout << "Score: " << player.getScore() << hwlib::endl;
    hwlib::cout << "Hits: " << hwlib::endl;

    for( int i = 0; i < playerCount; i++ ){
        hwlib::cout << " \t" << hitBy[i].playerID << " : " << hitBy[i].amount << hwlib::endl;

    };

    hwlib::cout << "=========================" << hwlib::endl;
    
};