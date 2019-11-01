#ifndef Player_hpp
#define Player_hpp

#include "hwlib.hpp"

///@file
///\brief
///Weapon struct that contains information about a weapon.
///\details
///This Weapon struct contains the name, damage, rateOfFire,
///magazine and reloadTime of a weapon.
struct Weapon {
	hwlib::string name;
	size_t damage;
	size_t rateOfFire;
	size_t magazine;
	size_t reloadTime;
};

///\brief
///A templated Weapons struct able to contain N Weapon objects.
///\details
///The Weapons struct can accept a template int N to adjust the size of the array.
///The default value of N is set to 9. The struct also has a getMin() function
///to retrieve the weapon with the least amount of damage.
template<int N = 9>
struct Weapons {
	Weapon allWeapons[N];

	size_t getMin();
};

///\brief
///A templated Player class with get and set functions.
///\details
///The Player class can accept a template int N1 to adust the score.
///The default value of N1 is set to 5000. The class also accepts a template
///N2 to calculate the maximum number of assailants, N2 should equal the weapon
///with the least amount of damage. This class has the following members:
///a Weapons struct, playerID, weaponIndex of te chosen weapon, the score and
///a array with the maximum amount of hits a player can take before dying.
template<int N1 = 5000, int N2 = 6>
class Player {
private:
	Weapons weapons;
	size_t playerID = 1;
	size_t weaponIndex = 1;
	size_t score = 5000;
	int assailants[N1/N2] = {0};
public:
	///\brief
	///The constructor of the Player class
	///\details
	///The Player class constructor only expects a Weapons struct.
	Player(
		Weapons WeaponsInput
	):
		weapons(WeaponsInput)
	{};

	///\brief
	///The setPlayerID sets the playerID with the chosen ID.
	void setPlayerID(size_t _playerID);

	///\brief
	///The setWeapon sets the weaponIndex with the chosen weapon.
	void setWeapon(size_t _weaponIndex);

	///\brief
	///The reportHit function adjusts the score and assailants array.
	///\details
	///The reportHit function expects 2 parameters to calculate the score
	///with which the player is left after getting hit. And also to save
	///the playerID of the attacker using a static counter to remember the index.
	void reportHit(size_t _playerID, size_t _weaponIndex);

	///\brief
	///The getWeaponIndex function returns the player's chosen weapon index.
	size_t getWeaponIndex();

	///\brief
	///The getPlayerID fucntion returns the player's chosen player ID.
	size_t getPlayerID();

	///\brief
	///The getWeaponFireRate function returns the fire rate of a weapon.
	size_t getWeaponFireRate();

	///\brief
	///The getScore function returns the score of the player.
	size_t getScore();

	///\brief
	///The getAssailants function returns the array of assailants of the player.
	int[] getAssailants();

	///\brief
	///The getAssailantsAmount function returns how many people have hit the player.
	size_t getAssalantsAmount();
};

#endif