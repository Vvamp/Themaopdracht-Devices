#include "BuzzerTask.hpp"
#include "DisplayTask.hpp"
#include "ReceiveTask.hpp"
#include "SendTask.hpp"
#include "GameTask.hpp"

#include "hwlib.hpp"
#include "rtos.hpp"

int main(){

	Weapon subGroot = Weapon("Sub Groot", 6, 200'000, 40, 6'000'000);
	Weapon subKlein = Weapon("Sub Klein", 7, 250'000, 20, 4'000'000);
	Weapon volAuto = Weapon("Vol Auto", 8, 330'000, 30, 5'000'000);
	Weapon semi = Weapon("Semi", 9, 500'000, 25, 5'000'000);
	Weapon pistol = Weapon("Pistool", 10, 1'000'000, 17, 3'000'000);
	Weapon lmg = Weapon("Light Machine gun", 13, 1'500'000, 150, 30'000'000);
	Weapon sniper = Weapon("Sniper", 15, 2'000'000, 10, 8'000'000);
	Weapon grenadeLauncher = Weapon("Grenade Launcher",20, 4'000'000, 5, 8'000'000);
	Weapon rpg = Weapon("RPG", 5000, 8'000'000, 1, 8'000'000);
	Weapons allWeapons({subGroot,subKlein,volAuto,semi,pistol,lmg,sniper,grenadeLauncher,rpg});

	auto iRPin = hwlib::target:pin_out(hwlib::target::pins::d11);

	BuzzerTask buzzerTask = BuzzerTask();
	DisplayTask displayTask =DisplayTask();
	SendTask sendTask = SendTask(iRPin);
	ReceiveTask receiveTask = ReceiveTask();

	HardwareInputTask hardwareInputTask = HardwareInputTask();

	GameTask gameTask = GameTask();

	return 0;
}
