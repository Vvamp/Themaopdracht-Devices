#ifndef WILDWESTCONTROL_HPP
#define WILDWESTCONTROL_HPP
#include "hwlib.hpp"
#include "TiltSensor.hpp"

/// @file
/// \brief
/// WildWestControl class
/// \details
/// This class functions as the Wild West game mode.
class WildWestControl{
private:
    player & Player
    TiltSensor tiltSensor;
    size_t matchTimer;
    size_t drawTimer = 0;
    hwlib::string gameMessage;

public:
    
    /// \brief
    /// WildWestControl constructor
    /// \details
    /// The WildWestControl constructor needs a player.
    WildWestControl(
        Player & player
    ):
        player( player )
    {};

    /// \brief
    /// Set the match time
    /// \details
    /// Set the match time
    void setMatchTime( size_t time );

    /// \brief
    /// Reduce the match time
    /// \details
    /// Reduce the match time.
    /// When the match time is lower then or equal to 0,
    /// start the draw and start shooting
    bool reduceMatchTime();

    /// \brief
    /// Add draw time
    /// \details
    /// Add to the draw time.
    /// When the draw time is greater or equal to 60 sec,
    /// stop the draw and end the game
    bool addDrawTime();

    /// \brief
    /// Get the match time
    /// \details
    /// Return the match time
    size_t getMatchTime();

    /// \brief
    /// Get the draw time
    /// \details
    /// Return the draw time
    size_t getDrawTime();

    /// \brief
    /// Change the game message
    /// \details
    /// Change the current game message
    void changeMessage( hwlib::string message );

    /// \brief
    /// Create a message for the display
    /// \details
    /// Create a hwlib::string message for the display
    hwlib::string toDisplay();

    /// \brief
    /// Set the match results
    /// \details
    /// Set the match results at the end of the game.
    // void setMatchResults();

};


#endif //WILDWESTCONTROL_HPP