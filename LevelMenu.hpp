#ifndef LEVELMENU_H
#define LEVELMENU_H

#include "button.h"
#include "menu2.hpp"
#include <sstream> 
#include <string>   
#include <fstream>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class LevelMenu {

private:
    bool open;
    int actualLvl;
    Button forward;
    Button backward;
    Button centralImage;
    TextMenu text;
    std::string maxScore;
    std::string bestTime;
    
public:
    LevelMenu();
    ~LevelMenu();
    int display(sf::RenderWindow* window);
    
};

#endif // LEVELMENU_H