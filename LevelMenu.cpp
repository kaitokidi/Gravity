#include "LevelMenu.hpp"


    LevelMenu::LevelMenu() {
        open = true;
        actualLvl = 0;
        forward.setPosition(0,0);
        forward.setSize(100,100);
        forward.setTextResizeText(" > ");
        backward.setPosition(0,0);
        backward.setSize(100,100);
        backward.setTextResizeText(" < ");
        centralImage.setText("");
    }
    
    LevelMenu::~LevelMenu(){}
    
    int LevelMenu::display(sf::RenderWindow* window){
        
        forward.setSize(100,100);
        forward.setPosition(window->getSize().x - backward.getSize().x -10, window->getSize().y/2);
        
        backward.setSize(100,100);
        backward.setPosition(0 +10, window->getSize().y/2);
        
        centralImage.setSize(window->getSize().x*3/4, window->getSize().y*3/4);
        centralImage.setPosition(window->getSize().x/2 - centralImage.getSize().x/2, window->getSize().y/2 - centralImage.getSize().y/2);
        centralImage.disableClickEffect();
            
        open = true;
        bool clicked = false;
        bool reloadImage = true;
        while(open){
            
            sf::Event event;
            while (window->pollEvent(event)) {
                forward.handleEvent(event);
                backward.handleEvent(event);
                centralImage.handleEvent(event);
                switch (event.type) {
                case sf::Event::Closed:
                    window->close();
                    exit(0);
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) { window->close(); exit(0);}
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        clicked = true;
                    }
                default:
                    break;
                }
            }
            
            if (forward.hasBeenClicked()) {
                ++actualLvl;

                    std::stringstream str; str << "res/board" << actualLvl << ".txt";       
                    std::string filePath = str.str();

                    std::ifstream myfile;
                    myfile.open(filePath.c_str());
                        
                        std::string actual;   
                        getline (myfile,actual);
                        
                        if(actual == "1") reloadImage = true;
                        else { 
                            reloadImage = false;
                            --actualLvl;
                        }
                        
                        getline (myfile,maxScore);
                        getline (myfile,bestTime);

                    myfile.close();
            }
            if (backward.hasBeenClicked()) {
                if(actualLvl > 0) {
                    --actualLvl;
                    std::stringstream str; str << "res/board" << actualLvl << ".txt";       
                    std::string filePath = str.str();

                    std::ifstream myfile;
                    myfile.open(filePath.c_str());
                        
                        std::string actual;   
                        getline (myfile,actual);
                        
                        if(actual == "1") reloadImage = true;
                        else { 
                            reloadImage = false;
                            ++actualLvl;
                        }
                        
                        getline (myfile,maxScore);
                        getline (myfile,bestTime);

                    myfile.close();
                }
            }
            if (centralImage.hasBeenClicked()) return actualLvl;
            
            if(reloadImage){
                std::stringstream st;
                st << "board" << actualLvl;       
                std::string board = st.str();
                centralImage.setTexture("res/"+board+".png");
            }
            
            window->clear();
            forward.draw(*window);
            backward.draw(*window);
            centralImage.draw(*window);
            text.displayTextPos(window, "Max Score: " + maxScore, sf::Color::White, 0, 0);
            text.displayTextPos(window, "Best Time: " + bestTime, sf::Color::White, 0, 50);
            
            window->display();       
        }
    }