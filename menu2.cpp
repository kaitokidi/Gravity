#include "menu2.hpp"


    TextMenu::TextMenu() {
        open = true;
        f.loadFromFile("res/font.ttf");
        t.setFont(f);
    }
    
    TextMenu::~TextMenu(){}

    std::string TextMenu::display_recieve_text(sf::RenderWindow* window, std::string s, sf::Color c ){
        open = true;
        std::string recieved = "";
        t.setString(recieved);
        t.setPosition(window->getSize().x/2 - ((s.size()/2)*t.getCharacterSize()), window->getSize().y/2 - t.getCharacterSize()/2);
        window->clear(c);
        float oldSize;
        
        while(open){
            
            sf::Event event;
            while (window->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    exit(0);
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        window->close();
                        exit(0);
                    }
                    break;
                case sf::Event::TextEntered:
                    oldSize = t.getGlobalBounds().width;
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)) { recieved.erase(recieved.end()-1, recieved.end()); }
                    else { recieved += event.text.unicode; }
                    t.setString(recieved);
                    if(t.getGlobalBounds().left >= 0.2)t.move(-(t.getGlobalBounds().width-oldSize)/2, 0);
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        open = false;
                    }
                default:
                    break;
                }
            }

            window->draw(t);

            window->display();
            window->clear();
        }
    }
        
        
    void TextMenu::displayText(sf::RenderWindow* window, std::string s , sf::Color c ){
        open = true;
        t.setString(s);
        t.setPosition(window->getSize().x/2 - ((s.size()/2)*t.getCharacterSize()), window->getSize().y/2 - t.getCharacterSize()/2);
        window->clear(c);

        while(open){
            
            sf::Event event;
            while (window->pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) window->close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        open = false;
                    }
                default:
                    break;
                }
            }

            window->draw(t);

            window->display();
                
        }
    }