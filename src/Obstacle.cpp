#include "Obstacle.h"
#include "Constants.h"
#include "Function.h"
#include <fstream>

Obstacle::Obstacle(double x, int y) : x(x), y(y), vel(0) {}

const double& Obstacle::getPositionX() const {
	return x;
}

const int& Obstacle::getPositionY() const {
	return y;
}

void Obstacle::setVel(double vel) {
	this->vel = vel;
}

const double& Obstacle::getVel() const {
	return vel;
}

void Obstacle::setPosition(double x, int y) {
	this->x = x;
	this->y = y;
}

void Obstacle::setPositionX(double x) {
	this->x = x;
}

void Obstacle::setPositionY(int y) {
	this->y = y;
}

void Obstacle::writeFile(std::ofstream &out) const {
	out.write((char*)&x, sizeof(x));
	out.write((char*)&y, sizeof(y));
}

void Obstacle::readFile(std::ifstream &in) {
	in.read((char*)&x, sizeof(x));
	in.read((char*)&y, sizeof(y));
}

Car::Car(double x) : Obstacle(x, LANE_SIZE * 4) {}

void Car::draw(Buffer &b) const {
	/*
	b.draw(L"   ______", (int)x, y);
	b.draw(L"  /|_||_\`.__", (int)x, y + 1);
	b.draw(L" (   _    _ _\\", (int)x, y + 2);
	b.draw(L"= `-(_)--(_)-'", (int)x, y + 3);
	*/
	b.draw("______", (int)x + 3, y);
	b.draw("/|_||_\\`.__", (int)x + 2, y + 1);
	b.draw("(   _    _ _\\", (int)x + 1, y + 2);
	b.draw("= `-(_)--(_)-'", (int)x, y + 3);
}

void Car::update(double deltaTime) {
	x += vel*deltaTime;
	if (GAME_IS_OVER)
		return;
	if (x < 0 - 14) {
		x += WIDTH + 14;
	}
	else if (x > WIDTH) {
		x -= WIDTH + 14;
	}
}

Truck::Truck(double x) : Obstacle(x, LANE_SIZE * 3) {}

void Truck::draw(Buffer &b) const {
	/*
	b.draw(L"        ____________________", x, y);
	b.draw(L"  ___  |                    | ", x, y + 1);
	b.draw(L" /_| | |                    |", x, y + 2);
	b.draw(L"|    |_| __________________ |", x, y + 3);
	b.draw(L"\"-O----O-O' `         `O`O'-'", x, y + 4);
	*/
	b.draw("  ___   ____________ ", (int)x, y);
	b.draw(" /_| | |            |", (int)x, y + 1);
	b.draw("|    |_| ___________|", (int)x, y + 2);
	b.draw("\"-O----O-O' ` `O`O'-'", (int)x, y + 3);
}

void Truck::update(double deltaTime) {
	x += vel*deltaTime;
	if (GAME_IS_OVER)
		return;
	if (x < 0 - 21) {
		x += WIDTH + 21;
	}
	else if (x > WIDTH) {
		x -= WIDTH + 21;
	}
}

Dinosaur::Dinosaur(double x) : Obstacle(x, LANE_SIZE * 2) {}

void Dinosaur::draw(Buffer &b) const {
	/*
	b.draw(L"            __", (int)x, y);
	b.draw(L"           / _)", (int)x, y + 1);
	b.draw(L"    .-^^^-/ /", (int)x, y + 2);
	b.draw(L" __/       /", (int)x, y + 3);
	b.draw(L"<__.|_|-|_|", (int)x, y + 4);
	*/
	b.draw("__", (int)x + 12, y);
	b.draw("/ _)", (int)x + 11, y + 1);
	b.draw(".-^^^-/ /", (int)x + 4, y + 2);
	b.draw("__/       /", (int)x + 1, y + 3);
	b.draw("<__.|_|-|_|", (int)x, y + 4);
}

void Dinosaur::update(double deltaTime) {
	x += vel*deltaTime;
	if (GAME_IS_OVER)
		return;
	if (x < 0 - 15) {
		x += WIDTH + 15;
	}
	else if (x > WIDTH) {
		x -= WIDTH + 15;
	}
}

Bird::Bird(double x) : Obstacle(x, LANE_SIZE * 1) {}

void Bird::draw(Buffer &b) const {
	b.draw(" _", (int)x, y);
	b.draw("<o)", (int)x, y + 1);
	b.draw("(_>", (int)x, y + 2);
}

void Bird::update(double deltaTime) {
	x += vel*deltaTime;
	if (GAME_IS_OVER)
		return;
	if (x < 0 - 3) {
		x += WIDTH + 3;
	}
	else if (x > WIDTH) {
		x -= WIDTH + 3;
	}
}

Ambulance::Ambulance() : Obstacle(-100.0, -100) {}

void Ambulance::draw(Buffer &b) const {
	if (vel > 0) {
		b.draw(" .________________.", (int)x, y);
		b.draw(" | _______________]___", (int)x, y + 1);
		b.draw(" |  _  AMBULANCE   _  )", (int)x, y + 2);
		b.draw("='-(_)----------=-(_)-", (int)x, y + 3);
		return;
	}
	b.draw("    .________________.", (int)x, y);
	b.draw(" ___[_______________ |", (int)x, y + 1);
	b.draw("(  _   AMBULANCE  _  |", (int)x, y + 2);
	b.draw(" -(_)-=----------(_)-'=", (int)x, y + 3);
}

void Ambulance::update(double deltaTime) {
	x += vel*deltaTime;
}

/*
RandomBird::RandomBird() {
	setPosition(-100, 0);
}

void RandomBird::draw(Buffer &b) const {
	b.draw('v', x, (int)y);
}
void RandomBird::update(double deltaTime) {
	y += RANDOM_BIRD_SPEED*deltaTime;
	if (y > 2 * HEIGHT) {
		setPosition(random(0, WIDTH), 0);
	}
}
void RandomBird::setPosition(int x, double y) {
	this->x = x;
	this->y = y;
}
const int& RandomBird::getPositionX() const {
	return x;
}
const double& RandomBird::getPositionY() const {
	return y;
}
void RandomBird::writeFile(std::ofstream &out) const {
	out.write((char*)&x, sizeof(x));
	out.write((char*)&y, sizeof(y));
}
void RandomBird::readFile(std::ifstream &in) {
	in.read((char*)&x, sizeof(x));
	in.read((char*)&y, sizeof(y));
}
*/