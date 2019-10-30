#include "TransferHitsControl.hpp"

void TransferHitsControl::exportPlayer(){

    // Create a struct to collect 
    struct playerHit {
        int playerID = 0;
        int amount   = 0;
    };

    // Create a list of all players the player has been hit by 
    // and the amount of times the player has been hit by that player
    playerHit hitBy[ player.score / player.weapons.getMin() ];

    int hits[]      = player.asailents;
    int playerCount = 0;

    for( int hit : hits ){
        
        // Add the first player hit to the playerHit list
        if( playerCount == 0 ){
            hitBy[0].playerID = hit;
            hitBy[0].amount = 1;
            playerCount++;

        } else {

            // Check if a player is already in the playerHit list
            // If true: increment the amount of hits a player has done
            // If false: add the player to the playerHit list
            bool found = false;
            
            for( int i = 0; i < playerCount; i++ ){

                if( hitBy[i].playerID == hit ){
                    hitBy[i].amount = hitBy[i].amount + 1;
                    found = true;
                    break;
                }

            }

            if( !found ){
                hitBy[playerCount].playerID = hit;
                hitBy[playerCount].amount += 1;
                playerCount++;
            }

        }

    }

    // Send player stats to the connected pc terminal
    hwlib::cout << "====== GAME RESULTS =====" << hwlib::endl;
    hwlib::cout << "Player_ID: " << player.playerID << hwlib::endl;
    hwlib::cout << "Score: " << player.score << hwlib::endl;
    hwlib::cout << "Hits: " << hwlib::endl;

    for( int i = 0; i < playerCount; i++ ){
        hwlib::cout << " \t" << hitBy[i].playerID << " : " << hitBy[i].amount << hwlib::endl;

    };

    hwlib::cout << "=========================" << hwlib::endl;
    
};