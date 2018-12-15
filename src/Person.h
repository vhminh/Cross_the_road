#ifndef _PERSON_H_
#define _PERSON_H_
#include "Buffer.h"
#include "Obstacle.h"
#include <fstream>

class Person {
public:
	Person();
	void setPosition(double x, int y);
	const double& getPositionX() const;
	const int& getPositionY() const;
	void moveUp();
	void moveDown();
	void moveLeft();
	void moveRight();
	void draw(Buffer &b) const;
	void writeFile(std::ofstream &out) const;
	void readFile(std::ifstream &in);
	bool collide(const Car& c) const;
	bool collide(const Truck& t) const;
	bool collide(const Dinosaur& d) const;
	bool collide(const Bird& b) const;
	bool collide(const Ambulance& a) const;
	bool collide(const Obstacle& ob, int size) const; // check if the person and the obstacle collide, size is the width of the ob
	void setVel(double vel = 0.0);
	void update(double deltaTime);
	bool isDead;
private:
	double x;
	int y;
	double vel = 0;
};

#endif