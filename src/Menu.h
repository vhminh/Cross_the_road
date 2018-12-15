#ifndef _MENU_H_
#define _MENU_H_
#include "Game.h"
#include "console.h"
#include <windows.h>
#include <iostream>
#include <conio.h>

class Menu {
public:
    Menu();
    void menuCall(Game& g);
    void splashScreen();
    void menuDraw();
    void mainMenu(Game& g);
    void settingsMenu(Game& g);
    void soundMenu(Game& g);
    void difficultyMenu(Game& g);
private:
    Buffer buffer;
    std::string sounds[3] = {
        " ON         ",
        " OFF        ",
        " Return     "};
    std::string difficulties[4] = {
        " Easy       ",
        " Normal     ",
        " Hard       ",
        " Return     "};
    std::string main[4] = {
        " Start Game ",
        " Load Game  ",
        " Settings   ",
        " Exit       "};
    std::string settings[3] = {
        " Difficulty ",
        " Sound      ",
        " Return     "};
};

#endif /* Menu_hpp */
