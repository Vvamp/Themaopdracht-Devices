#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "hwlib.hpp"

///@file
///\brief
///Weapon struct that contains information about a weapon.
///\details
///This Weapon struct contains the name, damage, rateOfFire,
///magazine and reloadTime of a weapon.
struct Weapon {
	hwlib::string<32> name;
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

	///\brief
	///getMin returns the damage value of the weapin with the least amount of damage.
	size_t getMin(){
		size_t min = 99;
		for (auto weapon : allWeapons){
			if (weapon.damage < min) {
				min = weapon.damage;
			}
		}
		return min;
	};
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
	Weapons<> weapons;
	size_t playerID = -1;
	size_t weaponIndex = -1;
	size_t score = N1;
	int assailants[N1/N2] = {0};
public:

	///\brief
	///The constructor of the Player class
	///\details
	///The Player class constructor only expects a Weapons struct.
	Player(
		Weapons<> weaponsInput
	):
		weapons(weaponsInput)
	{};

	///\brief
	///The setPlayerID sets the playerID with the chosen ID.
	void setPlayerID(size_t _playerID){
		playerID = _playerID;
	};

	///\brief
	///The setWeapon sets the weaponIndex with the chosen weapon.
	void setWeapon(size_t _weaponIndex){
		weaponIndex = _weaponIndex;
	};

	///\brief
	///The reportHit function adjusts the score and assailants array.
	///\details
	///The reportHit function expects 2 parameters to calculate the score
	///with which the player is left after getting hit. And also to save
	///the playerID of the attacker using a static counter to remember the index.
	void reportHit(size_t _playerID, size_t _weaponIndex){
		hwlib::cout << "PLAYER_ID:" << hwlib::dec << _playerID << "\t WEAPON_INDEX" << hwlib::dec << _weaponIndex << "\n"; 
		static size_t counter = 0;
		score -= weapons.allWeapons[_weaponIndex].damage;
		assailants[counter] = _playerID;
		counter++;
	};

	///\brief
	///The getWeaponIndex function returns the player's chosen weapon index.
	size_t getWeaponIndex(){
		return weaponIndex;
	};

	///\brief
	///The getPlayerID fucntion returns the player's chosen player ID.
	size_t getPlayerID(){
		return playerID;
	};

	///\brief
	///The getWeaponFireRate function returns the fire rate of a weapon.
	size_t getWeaponFireRate(){
		return weapons.allWeapons[weaponIndex].rateOfFire;
	};

	///\brief
	///The getScore function returns the score of the player.
	size_t getScore(){
		return score;
	};

	///\brief
	///The getAssailants function returns the array of assailants of the player.
	int* getAssailants(){
		return assailants;
	};

	///\brief
	///The getAssailantsAmount function returns how many people have hit the player.
	size_t getAssailantsAmount(){
		size_t amount=0;
		for (auto assailant : assailants){
			if (assailant == 0){
				break;
			} else {
				amount++;
			}
		}
		return amount;
	};
};

#endif