#ifndef BUTTON_H
#define BUTTON_H
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <string.h>

class Button{

public:

    //CONSTRUCTOR
    
    /* Initialize the private variables */
    Button();
    
    /* Initialize the button with the parameters as the text, texture, size and position */
    Button(std::string text, std::string texturePath, float sizeX, float sizeY);

    /* Initialize the button with the parameters as the text, texture, size and position */
    Button(std::string text, std::string texturePath, std::string pressedTexturePath, float sizeX, float sizeY);
    
    
    // SET PROPERTIES 
    
    /* Set the text on the button */
    void setText(std::string s);

    /* Set the Texture that will be used as default button image */
    void setTexture(std::string name);

    /* Set the Texture that will be used as default button pressed image */
    void setPressedTexture(std::string name);

    /* Set the position of the button */
    void setPosition(float x, float y);
    void setPosition(sf::Vector2f position);

    /* Set the size of the button passed as parameter */
    void setSize(float x, float y);
    void setSize(sf::Vector2f size);

    /* Set the size of the characters of the button text*/
    void setCharacterSize(uint u);

    /* Set the text on the button and scale the button 
    so the text fits on it */
    void setTextResizeButton(std::string s);

    /* Set the text on the button and scale the text 
    so the it fits on the button */
    void setTextResizeText(std::string s);

    /* Set the color of the button's text*/
    void setTextColor(sf::Color c);

    /*Set the Font passed as a parameter as the one used by the button*/
    void setFont(sf::Font f);

    /* Enable the change of texture when the button is clicked */
    void enableClickEffect();

    /* Disable the change of texture when the button is clicked */
    void disableClickEffect();



    //  GET INFORMATION
    
    /* The return indicates if the button is
    clicked or not*/
    bool isClicked();

    /* Return true if the button has been clicked and this function has 
     not been checked yet */
    bool hasBeenClicked();

    /* Return the time passed since the last time the button
    has been clicked (returned in a float as seconds)*/
    float timeSinceLastClick();

    /* Returns wether ClickEffect is activated or not */
    bool clickEffectActivated();

    /* Returns the string setted on the text*/
    std::string getText();

    /* Return the position of the button*/
    sf::Vector2f getPosition();

    /* Return the size of the button*/
    sf::Vector2f getSize();

    /* Returns the characterSize*/
    uint getCharacterSize();

    /* Returns the color of the button's text*/
    sf::Color getTextColor();


    // ACTION PERFORM 

    /* Draw the button on the window passed as parameter */
    void draw(sf::RenderWindow &w);

    /* Update the private variables if needed acordingly to the event*/
    void handleEvent(sf::Event e);

    
private:

    bool clicked;
    bool is_clicked;
    bool clickEffect;

    sf::Font font;
    sf::Text text;
    sf::Clock clock;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Texture pressed_texture;
    float time_since_last_click;

};

#endif // BUTTON_H
