#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main(){

    const float g = 1;
    
    sf::Vector2f v = sf::Vector2f(0,0);
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Gravity");
    
    sf::RectangleShape r(sf::Vector2f(window.getSize().x/10, window.getSize().y/10));
    
    r.setPosition(0,0);
    r.setFillColor(sf::Color::Red);
    
    float ground = window.getSize().y*6/7;

    //GAME LOOP
    while(window.isOpen()){
        
        sf::Event event;
        while(window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close(); 
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  v.y = -10;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) v.x = -1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  v.x = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) v.x = 1;
        
        r.move(v);
        
        if( (r.getPosition().y + r.getSize().y) < ground || v.y < 0){
            v.y += g;
        }
        else {
            r.setPosition(r.getPosition().x, ground - r.getSize().y);
            v.y = 0;
        }
        
        window.clear();
        window.draw(r);
        window.display();
    }
}

/*
g++ -c gravity.cpp
g++ -o gravity gravity.o -lsfml-graphics -lsfml-window -lsfml-system
./gravity
 */