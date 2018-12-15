#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_
#include "Buffer.h"

class Obstacle {
public:
	Obstacle(double x = 0, int y = 0);
	virtual void draw(Buffer &b) const = 0;
	virtual void update(double deltaTime) = 0;
	void setPosition(double x, int y);
	void setPositionX(double x);
	void setPositionY(int y);
	const double& getPositionX() const;
	const int& getPositionY() const;
	void setVel(double vel = 0);
	const double& getVel() const;
	void writeFile(std::ofstream &out) const;
	void readFile(std::ifstream &in);
protected:
	double vel;
	double x;
	int y;
};

class Car : public Obstacle {
public:
	Car(double x = 0);
	void draw(Buffer &b) const;
	void update(double deltaTime);
};

class Truck : public Obstacle {
public:
	Truck(double x = 0);
	void draw(Buffer &b) const;
	void update(double deltaTime);
};

class Dinosaur : public Obstacle {
public:
	Dinosaur(double x = 0);
	void draw(Buffer &b) const;
	void update(double deltaTime);
};

class Bird : public Obstacle {
public:
	Bird(double x = 0);
	void draw(Buffer &b) const;
	void update(double deltaTime);
};

class Ambulance : public Obstacle {
public:
	Ambulance();
	void draw(Buffer &b) const;
	void update(double deltaTime);
};

/*
class RandomBird {
public:
	RandomBird();
	void draw(Buffer &b) const;
	void update(double deltaTime);
	void setPosition(int x, double y);
	const int& getPositionX() const;
	const double& getPositionY() const;
	void writeFile(std::ofstream &out) const;
	void readFile(std::ifstream &in);
private:
	int x;
	double y;
};
*/

#endif