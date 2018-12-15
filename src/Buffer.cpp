#include "Buffer.h"
#include "Function.h"
#include <iostream> 
#include <Windows.h>
#include <string>

Buffer::Buffer(int width, int height) : content((width + 1)*height, ' '), width(width), height(height) {
	resetContent();
}

void Buffer::draw(char c, int x, int y) {
	if (x >= 0 && x < width && y >= 0 && y < height)
		content[x + y * (width + 1)] = c;
}

void Buffer::draw(std::string s, int x, int y) {
	for (int i = 0; i < s.size(); ++i)
		draw(s[i], x + i, y);
}

void Buffer::resetContent() {
	for (size_t i = 0; i < content.size(); ++i)
		content[i] = ' ';
	for (int i = 0; i < height; ++i)
		content[width + i * (width + 1)] = '\n';
}

void Buffer::display() {
	gotoXY(0, 0);
	printf(content.c_str());
	resetContent();
}