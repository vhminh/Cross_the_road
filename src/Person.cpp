#include "Person.h"
#include "Constants.h"

Person::Person() : isDead(false) {}

void Person::setPosition(double x, int y) {
	this->x = x;
	this->y = y;
}

const double& Person::getPositionX() const {
	return x;
}

const int& Person::getPositionY() const {
	return y;
}

void Person::moveUp() {
	if (isDead) return;
	if (y - LANE_SIZE >= 0) {
		y -= LANE_SIZE;
	}
}

void Person::moveDown() {
	if (isDead) return;
	if (y + LANE_SIZE < LANE_SIZE * 6) {
		y += LANE_SIZE;
	}
}

void Person::moveRight() {
	if (isDead) return;
	if (x + LANE_SIZE < WIDTH) {
		x += LANE_SIZE;
	}
}

void Person::moveLeft() {
	if (isDead) return;
	if (x - LANE_SIZE >= 0) {
		x -= LANE_SIZE;
	}
}

void Person::draw(Buffer& b) const {
	if (!isDead) {
		b.draw(" c ", (int)x, y + 1);
		b.draw("<|>", (int)x, y + 2);
		b.draw("/ \\", (int)x, y + 3);
		return;
	}
	b.draw("___", (int)x + 2, y);
	b.draw("(X.X)", (int)x + 1, y + 1);
	b.draw("=.|m|.=", (int)x, y + 2);
	b.draw("='   '=", (int)x, y + 3);
}

void Person::writeFile(std::ofstream &out) const {
	out.write((char*)&x, sizeof(x));
	out.write((char*)&y, sizeof(y));
}

void Person::readFile(std::ifstream &in) {
	in.read((char*)&x, sizeof(x));
	in.read((char*)&y, sizeof(y));
}

bool Person::collide(const Car &car) const {
	return collide(car, 14);
}

bool Person::collide(const Truck &truck) const {
	return collide(truck, 21);
}

bool Person::collide(const Dinosaur &dino) const {
	return collide(dino, 15);
}

bool Person::collide(const Bird &bird) const {
	return collide(bird, 3);
}

bool Person::collide(const Ambulance &am) const {
	// reimplement because the sprite when the person is dead has different size
	int size = 23;
	bool sameLane = (y == am.getPositionY());
	bool collideToTheRight = (x <= int(am.getPositionX()) && x + 6 > int(am.getPositionX()));
	bool collideToTheLeft = (x >= int(am.getPositionX()) && x < int(am.getPositionX() + size));
	return sameLane && (collideToTheLeft || collideToTheRight);
}

bool Person::collide(const Obstacle &ob, int size) const {
	bool sameLane = (y == ob.getPositionY());
	bool collideToTheRight = (x <= int(ob.getPositionX()) && x + 2 > int(ob.getPositionX()));
	bool collideToTheLeft = (x >= int(ob.getPositionX()) && x < int(ob.getPositionX() + size));
	return sameLane && (collideToTheLeft || collideToTheRight);
}

void Person::setVel(double vel) {
	this->vel = vel;
}

void Person::update(double deltaTime) {
	double newX = x + vel*deltaTime;
	if (newX >= 0 && newX < WIDTH - 3)
		x = newX;
}