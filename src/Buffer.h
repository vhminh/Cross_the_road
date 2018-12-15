#ifndef _BUFFER_H_
#define _BUFFER_H_
#include <string>

class Buffer {
public:
	Buffer(int width, int height);
	void draw(char c, int x, int y);
	void draw(std::string wstr, int x, int y);
	void display();
private:
	int width;
	int height;
	std::string content;
	void resetContent();
};

#endif