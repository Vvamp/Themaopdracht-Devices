#include "player.hpp"

size_t Weapons::getMin(){
	size_t min = 99;
	for (auto weapon : allWeapons){
		if (weapon.damage < min) {
			min = weapon.damage;
		}
	}
	return min;
};

void Player::setPlayerID(size_t _playerID){
	playerID = _playerID;
};

void Player::setWeapon(size_t _weaponIndex){
	weaponIndex = _weaponIndex;
};

void Player::reportHit(size_t _playerID, size_t _weaponIndex){
	static counter = 0;
	score -= weapons[_weaponIndex].damage;
	assailants[counter] = _playerID;
	counter++;
};

size_t Player::getWeaponIndex(){
	return weaponIndex;
};

size_t Player::getPlayerID(){
	return playerID;
};

size_t Player::getWeaponFireRate(){
	return weapons[weaponIndex].rateOfFire;
};

size_t Player::getScore(){
	return score;
};

int[] Player::getAssailants(){
	return assailants;
};

size_t Player::getAssalantsAmount(){
	size_t amount=0;
	for (auto assailant : assailants){
		(assailant == 0) ? break : amount++;
	}
	return amount;
};