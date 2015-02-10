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
                case sf::Event::TextEntered:
                    recieved += event.text.unicode;
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