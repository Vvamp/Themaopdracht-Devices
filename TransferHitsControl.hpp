#ifndef TRANSFERHITSCONTROL_HPP
#define TRANSFERHITSCONTROL_HPP
#include "hwlib.hpp"

#include "Player.hpp"
/// @file
/// \brief
/// TransferHitsControl class
/// \details
/// This class is Transfers the player stats to a connected terminal
class TransferHitsControl {
private:
    Player<> & player;

public:

    /// \brief
    /// TransferHitsControl constructor
    TransferHitsControl( Player<> & player ):
        player( player )
    {};

    /// \brief
    /// Export player stats to connected pc terminal
    /// \details
    /// Export the Player entity to an connected pc terminal,
    /// this is done by calculating the amount of hits by every indivitual player
    void exportPlayer();

};

#endif //TRANSFERHITSCONTROL_HPP