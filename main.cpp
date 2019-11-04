#include "BuzzerTask.hpp"
#include "DisplayTask.hpp"
#include "ReceiveTask.hpp"
#include "SendTask.hpp"
#include "GameTask.hpp"
#include "HardwareInputTask.hpp"

#include "hwlib.hpp"
#include "rtos.hpp"

int main(){

	hwlib::wait_ms(500);

	const unsigned int amountOfListeners = 1;

	Weapon subGroot = 			Weapon({"Sub Groot", 6, 200'000, 40, 6'000'000});
	Weapon subKlein = 			Weapon({"Sub Klein", 7, 250'000, 20, 4'000'000});
	Weapon volAuto = 			Weapon({"Vol Auto", 8, 330'000, 30, 5'000'000});
	Weapon semi = 				Weapon({"Semi", 9, 500'000, 25, 5'000'000});
	Weapon pistol = 			Weapon({"Pistool", 10, 1'000'000, 17, 3'000'000});
	Weapon lmg = 				Weapon({"Light Machine gun", 13, 1'500'000, 150, 30'000'000});
	Weapon sniper = 			Weapon({"Sniper", 15, 2'000'000, 10, 8'000'000});
	Weapon grenadeLauncher = 	Weapon({"Grenade Launcher",20, 4'000'000, 5, 8'000'000});
	Weapon rpg = 				Weapon({"RPG", 5000, 8'000'000, 1, 8'000'000});
	Weapons allWeapons({subGroot,subKlein,volAuto,semi,pistol,lmg,sniper,grenadeLauncher,rpg});

	auto buzzerPin = hwlib::target::pin_out(hwlib::target::pins::d10);

	auto iRDPin = hwlib::target::d2_36kHz();
	auto iRRPin = hwlib::target::pin_in(hwlib::target::pins::d12);

	auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
	auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);

	auto out0 = hwlib::target::pin_oc(hwlib::target::pins::a0);
	auto out1 = hwlib::target::pin_oc(hwlib::target::pins::a1);
	auto out2 = hwlib::target::pin_oc(hwlib::target::pins::a2);
	auto out3 = hwlib::target::pin_oc(hwlib::target::pins::a3);

	auto in0 = hwlib::target::pin_in(hwlib::target::pins::a4);
	auto in1 = hwlib::target::pin_in(hwlib::target::pins::a5);
	auto in2 = hwlib::target::pin_in(hwlib::target::pins::a6);
	auto in3 = hwlib::target::pin_in(hwlib::target::pins::a7);

	auto out_port = hwlib::port_oc_from(out0, out1, out2, out3);
	auto in_port = hwlib::port_in_from(in0, in1, in2, in3);

	// KeyboardListener henk = KeyboardListener();
	BuzzerTask buzzerTask = BuzzerTask(buzzerPin);
	DisplayTask displayTask =DisplayTask(sda,scl);
	SendTask sendTask = SendTask(iRDPin);
	Keyboard<amountOfListeners> keyboard = Keyboard(out_port, in_port);
	HardwareInputTask<amountOfListeners> hardwareInputTask = HardwareInputTask(keyboard);

	GameTask gameTask = GameTask(
		Player(allWeapons),
		displayTask,
		sendTask,
		buzzerTask,
		keyboard
	);

	ReceiveTask receiveTask = ReceiveTask(iRRPin,gameTask);

	hwlib::cout << sendTask;
	hwlib::cout << receiveTask;
	hwlib::cout << displayTask;
	hwlib::cout << buzzerTask;
	hwlib::cout << hardwareInputTask;
	rtos::run();
	return 0;
}
