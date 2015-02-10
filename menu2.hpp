#ifndef MENU2_H
#define MENU2_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class TextMenu {

private:
    sf::Text t; 
    sf::Font f;
    sf::Color c;
//    sf::Button b;
    bool open;
    
public:
    TextMenu();
    ~TextMenu();

    void        displayText         (sf::RenderWindow* window, std::string s = "~ Click to skip ~", sf::Color c = (sf::Color::Black));
    std::string display_recieve_text(sf::RenderWindow* window, std::string s = "~ Click to skip ~", sf::Color c = (sf::Color::Black));
    
};

#endif // MENU2_H