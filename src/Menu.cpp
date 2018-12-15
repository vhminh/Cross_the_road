#include "Menu.h"
#include "Constants.h"

Menu::Menu() : buffer(120, 35 + 1) {}

void Menu::soundMenu(Game& g) {
	int pointer = 0;
	clrscr();
	while (true) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		menuDraw();
		for (int i = 0; i<3; i++) {
			gotoXY_(70, i + 22);
			if (i == pointer)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xFC);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			std::cout << sounds[i] << std::endl;
		}
		int c;
		bool isArrowKey;
		while (true) {
			isArrowKey = false;
			c = _getch();
			if (c == 27 /* ESC */)
				return;
			if (c == 0xE0 || c == 0) {
				c = _getch();
				isArrowKey = true;
			}
			if (isArrowKey && c == 72 /* up arrow */) {
				Sleep(150);
				pointer--;
				if (pointer == -1) {
					pointer = 2;
				}
				break;
			}
			else if (isArrowKey && c == 80 /* down arrow */ ) {
				Sleep(150);
				pointer++;
				if (pointer == 3) {
					pointer = 0;
				}
				break;
			}
			else if (c == '\r') {
				Sleep(150);
				gotoXY_(71, 22 + 3);
				switch (pointer) {
				case 0: {
					if (!sound)
						PlaySound("Resource\\the-legend-of-zelda-overworld.wav", NULL, SND_LOOP | SND_ASYNC);
					sound = true;
					std::cout << "Sound: ON" << std::endl;
					Sleep(300);
					clrscr();
					return;
				} break;
				case 1: {
					sound = false;
					std::cout << "Sound: OFF" << std::endl;
					PlaySound(NULL, NULL, NULL);
					Sleep(300);
					clrscr();
					return;
				} break;
				case 2: {
					clrscr();
					return;
				} break;
				}
				break;
			}
		}
	}
}

void Menu::difficultyMenu(Game& g) {
	int pointer = 0;
	clrscr();
	while (true) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		menuDraw();
		for (int i = 0; i<4; i++) {
			gotoXY_(70, i + 22);
			if (i == pointer)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xFC);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			std::cout << difficulties[i] << std::endl;
		}
		int c;
		bool isArrowKey;
		while (true) {
			isArrowKey = false;
			c = _getch();
			if (c == 27 /* ESC */)
				return;
			if (c == 0xE0 || c == 0) {
				c = _getch();
				isArrowKey = true;
			}
			if (isArrowKey && c == 72 /* up arrow */) {
				Sleep(150);
				pointer--;
				if (pointer == -1) {
					pointer = 3;
				}
				break;
			}
			else if (isArrowKey && c == 80 /* down arrow */) {
				Sleep(150);
				pointer++;
				if (pointer == 4) {
					pointer = 0;
				}
				break;
			}
			else if (c == '\r') {
				Sleep(150);
				gotoXY_(71, 22 + 4);
				switch (pointer) {
				case 0: {
					difficulty = 0;
					std::cout << "Setting difficulty: Easy" << std::endl;
					Sleep(300);
					clrscr();
					return;
				} break;
				case 1: {
					difficulty = 1;
					std::cout << "Setting difficulty: Normal" << std::endl;
					Sleep(300);
					clrscr();
					return;
				} break;
				case 2: {
					difficulty = 2;
					std::cout << "Setting difficulty: Hard" << std::endl;
					Sleep(300);
					clrscr();
					return;
				} break;
				case 3: {
					clrscr();
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
					return;
				} break;
				}
				break;
			}
		}
	}
}

void Menu::settingsMenu(Game& g) {
	int pointer = 0;
	clrscr();
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	while (true) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		menuDraw();
		for (int i = 0; i<3; i++) {
			gotoXY_(70, i + 22);
			if (i == pointer)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xFC);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			std::cout << settings[i] << std::endl;
		}
		int c;
		bool isArrowKey;
		while (true) {
			isArrowKey = false;
			c = _getch();
			if (c == 27 /* ESC */)
				return;
			if (c == 0xE0 || c == 0) {
				c = _getch();
				isArrowKey = true;
			}
			if (isArrowKey && c == 72 /* up arrow */) {
				Sleep(150);
				pointer -= 1;
				if (pointer == -1) {
					pointer = 2;
				}
				break;
			}
			else if (isArrowKey && c == 80 /* down arrow */) {
				Sleep(150);
				pointer += 1;
				if (pointer == 3) {
					pointer = 0;
				}
				break;
			}
			else if (c == '\r') {
				Sleep(150);
				gotoXY_(71, 22 + 3);
				switch (pointer) {
				case 0: {
					clrscr();
					difficultyMenu(g);
				} break;
				case 1: {
					clrscr();
					soundMenu(g);
				} break;
				case 2: {
					clrscr();
					mainMenu(g);
				} break;
				}
				break;
			}
		}
	}
}

void Menu::mainMenu(Game& g) {
	int pointer = 0;
	clrscr();
	while (true) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		menuDraw();
		for (int i = 0; i<4; i++) {
			gotoXY_(70, i + 22);
			if (i == pointer)
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0xFC);
			else
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			std::cout << main[i] << std::endl;
		}
		int c;
		bool isArrowKey;
		while (true) {
			isArrowKey = false;
			c = _getch();
			if (c == 27 /* ESC */)
				return;
			if (c == 0xE0 || c == 0) {
				c = _getch();
				isArrowKey = true;
			}
			if (isArrowKey && c == 72 /* up arrow */) {
				Sleep(150);
				pointer -= 1;
				if (pointer == -1) {
					pointer = 3;
				}
				break;
			}
			else if (isArrowKey && c == 80 /* down arrow */) {
				Sleep(150);
				pointer += 1;
				if (pointer == 4) {
					pointer = 0;
				}
				break;
			}
			else if (c == '\r') {
				Sleep(150);
				gotoXY_(71, 22 + 4);
				switch (pointer) {
				case 0: {
					std::cout << "Starting new game..." << std::endl;
					Sleep(500);
					clrscr();
					splashScreen();
					clrscr();
					g.run();
				} break;
				case 1: {
					std::string path;
					std::cout << "Input path: ";
					gotoXY_(83, 22 + 4);
					getline(std::cin, path);

					gotoXY_(71, 22 + 5);
					std::cout << "Loading path: " << path << std::endl;
					try {
						g.loadGame(path);
					}
					catch (std::string &message) {
						gotoXY_(71, 22 + 6);
						std::cout << message;
					}
					Sleep(1000);
					clrscr();
				} break;
				case 2: {
					clrscr();
					settingsMenu(g);
				} break;
				case 3:
					exit(0);
					break;
				}
				break;
			}
		}
	}
}

void Menu::splashScreen() {
	clrscr();
	system("cls");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	gotoXY_(51, 15);
	std::cout << "INITIALIZING..." << std::endl;

	for (int i = 0; i<30; i++) {
		gotoXY_(44 + i, 18);
		Sleep(140);
		std::cout << "\b" << char(250);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		if (i % 2 == 0)
			std::cout << char(220) << char(223) << char(223) << char(220) << std::flush;
		else if (i % 2 != 0)
			std::cout << char(223) << char(220) << char(220) << char(223) << std::flush;
		gotoXY_(43 + i, 19);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		std::cout << char(220) << std::flush;
	}
}

void Menu::menuDraw() {
	int i, j;
	i = j = 3;
	gotoXY_(27, ++i);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	std::cout << "_.|._" << std::endl;
	gotoXY_(28, ++i);
	std::cout << "'|'" << std::endl;
	gotoXY_(27, ++i);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
	std::cout << "/   \\" << std::endl;
	gotoXY_(26, ++i);
	std::cout << "/     \\" << std::endl;
	gotoXY_(25, ++i);
	std::cout << "/    Щ.~\\" << std::endl;
	gotoXY_(24, ++i);
	std::cout << "!_.~о    _!" << std::endl;
	gotoXY_(24, ++i);
	std::cout << "/м.      o\\" << std::endl;
	gotoXY_(23, ++i);
	std::cout << "/ J о~~.    \\" << std::endl;
	gotoXY_(22, ++i);
	std::cout << "!_       мм~._!" << std::endl;
	gotoXY_(22, ++i);
	std::cout << "/   Щ       ~о\\" << std::endl;
	gotoXY_(21, ++i);
	std::cout << "/  J    .~~оо   \\" << std::endl;
	gotoXY_(20, ++i);
	std::cout << "!_...~~оо      o _!" << std::endl;
	gotoXY_(20, ++i);
	std::cout << "/  м..     J      \\" << std::endl;
	gotoXY_(19, ++i);
	std::cout << "/      мо~~..       \\" << std::endl;
	gotoXY_(18, ++i);
	std::cout << "!_     Щ      мм~~~.._!" << std::endl;
	gotoXY_(18, ++i);
	std::cout << "/   o           ..~~оо\\" << std::endl;
	gotoXY_(17, ++i);
	std::cout << "/        ..~~~ооо       \\" << std::endl;
	gotoXY_(16, ++i);
	std::cout << "!_...~~~оо          J    _!" << std::endl;
	gotoXY_(16, ++i);
	std::cout << "/  мо~~~..                \\" << std::endl;
	gotoXY_(15, ++i);
	std::cout << "/     Щ     моо~~...      o \\" << std::endl;
	gotoXY_(14, ++i);
	std::cout << "!_  o               моо~~..._!" << std::endl;
	gotoXY_(14, ++i);
	std::cout << "/             o      ...~~~ооо\\" << std::endl;
	gotoXY_(13, ++i);
	std::cout << "/     J      ...~~~ооо    J     \\" << std::endl;
	gotoXY_(12, ++i);
	std::cout << "/:....~~~~оооо::::::::::::::::::::\\" << std::endl;
	gotoXY_(21, ++i);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "[________________]" << std::endl;
	gotoXY_(22, ++i);
	std::cout << "\\    Group 3   /" << std::endl;
	gotoXY_(23, ++i);
	std::cout << "\\____________/" << std::endl;

	++i;
	gotoXY_(10, ++i);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
	std::cout << "_____  " << char(219) << "     ____  " << char(219) << "     _______    _______ " << std::endl;
	gotoXY_(10, ++i);
	std::cout << "|" << char(219) << "     " << char(219) << "    |" << char(219) << "     " << char(219) << "    |" << char(219) << "         |" << char(219) << std::endl;
	gotoXY_(10, ++i);
	std::cout << "_____  " << char(219) << "     _______    |" << char(219) << "        _______ " << char(219) << std::endl;
	gotoXY_(10, ++i);
	std::cout << "|" << char(219) << "     " << char(219) << "    |" << char(219) << "          |" << char(219) << "                " << char(219) << std::endl;
	gotoXY_(8, ++i);
	std::cout << "__|" << char(219) << "   __" << char(219) << "  __|" << char(219) << "        __________  _________ " << std::endl;

	j = 5;
	gotoXY_(34, j);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	std::cout << "_______     ______      _______     ______    " << std::endl;
	gotoXY_(33, ++j);
	std::cout << "|   __  \\   /      \\    /       \\   |      \\   " << std::endl;
	gotoXY_(33, ++j);
	std::cout << "|  |__|  | /   __   \\  /   __   |   |   __  |  " << std::endl;
	gotoXY_(33, ++j);
	std::cout << "|   _   /  |  |__|  |  |  |__|  |   |  |__| |  " << std::endl;
	gotoXY_(33, ++j);
	std::cout << "|  | \\  \\  \\        /  \\        |   |       |  " << std::endl;
	gotoXY_(33, ++j);
	std::cout << "|__|  \\__\\  \\______/    \\_____/\\_\\  |______/   " << std::endl;

	j = j - 3;
	gotoXY_(80, j++);
	std::cout << "_________  " << std::endl;
	gotoXY_(80, j++);
	std::cout << "|_______|  " << std::endl;

	j = j + 2;
	gotoXY_(46, j);
	std::cout << "________   _______     ______      ________   ________  " << std::endl;
	gotoXY_(45, ++j);
	std::cout << "/  _____/  |   __  \\   /      \\    /  _____/  /  _____/  " << std::endl;
	gotoXY_(44, ++j);
	std::cout << "/  /        |  |__|  | /   __   \\  /  /____   /  /____    " << std::endl;
	gotoXY_(44, ++j);
	std::cout << "|  |        |   _   /  |  |__|  |  \\____   \\  \\____   \\   " << std::endl;
	gotoXY_(44, ++j);
	std::cout << "\\  \\______  |  | \\  \\  \\        /  _____/  /  _____/  /   " << std::endl;
	gotoXY_(45, ++j);
	std::cout << "\\_______/  |__|  \\__\\  \\______/  /______ /  /______ /    " << std::endl;
}

void Menu::menuCall(Game& g) {
	clrscr();
	while (true) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		mainMenu(g);
		clrscr();
	}
}
