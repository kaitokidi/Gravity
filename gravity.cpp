//LUDUM DARE 30
#include <map>
#include <string>
#include <sstream>   
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
namespace sf{
	bool operator< (const sf::Color& c1, const sf::Color& c2){
		if(c1.r < c2.r) return true;
		else if(c1.r > c2.r) return false;
		else if(c1.g < c2.g) return true;
		else if(c1.g > c2.g) return false;
		else if(c1.b < c2.b) return true;
		else if(c1.b > c2.b) return false;
		else if(c1.a < c2.a) return true;
		else if(c1.a > c2.a) return false;
		else return false;
	}
}
sf::Color getColisionColor(float posx, float posy, sf::Image& img, sf::Sprite& bSprite){
	return img.getPixel( posx/bSprite.getScale().x, posy/bSprite.getScale().y);
}


int main(){
    
    sf::Vector2f v = sf::Vector2f(0,0);
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Gravity");
   
    const float g = (int)window.getSize().y*2 ;

    sf::RectangleShape r(sf::Vector2f(window.getSize().x/10, window.getSize().y/10));
    r.setPosition(0,0); r.setFillColor(sf::Color::White);
    
	float ground = window.getSize().y-2;
//     float ground = window.getSize().y*6/7;
    sf::Clock timer;
    float deltatime = 0;
	
	sf::Text text; sf::Font font; 
	if(! font.loadFromFile("font.ttf")) std::cout << "penguin" << std::endl;
	text.setFont(font); text.setPosition(0,0); text.setString("penguin <3");
	
	sf::Image bimg;
	sf::Texture bTex;
	sf::Sprite bSprite;
	
	std::map<sf::Color, sf::Time> colorsColiding;

	int pantalla = 0;
	bool reboot = false;
	bool needshiet = true;
	
    //GAME LOOP
    while(window.isOpen()){
		if(needshiet){
			v = sf::Vector2f(0,0);
			colorsColiding.clear();
			r.setPosition(0,0);
			std::stringstream s;
			s << "board" << pantalla;		
			std::string board = s.str();
			if(!bimg.loadFromFile(board+".png")) std::cout << "I CAN'T LOAD BOARD IMAGE" << std::endl;
			if(!bTex.loadFromFile(board+".png")) std::cout << "I CAN'T LOAD BOARD texture" << std::endl;
			bSprite.setTexture(bTex, true);
			bSprite.scale(window.getSize().x/bSprite.getGlobalBounds().width , 
							window.getSize().y/bSprite.getGlobalBounds().height);
			
			needshiet = false;
			deltatime = 0;
		}
		
        deltatime = timer.restart().asSeconds();
        
        sf::Event event;
        while(window.pollEvent(event)) if (event.type == sf::Event::Closed) window.close(); 
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))  v.y = (int)window.getSize().y/2 * -1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) v.x = (int)window.getSize().x/20 * -1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  v.x = 0;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) v.x = window.getSize().x/20;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  v.y = (int)window.getSize().y * -1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { reboot = true; v.x = 0; }
        r.move(v * deltatime);
        
        if( (r.getPosition().y + r.getSize().y) < ground || v.y < 0) v.y += g *deltatime;
        else {
            r.setPosition(r.getPosition().x, ground - r.getSize().y);
            v.y = 0;
        }
        
        sf::FloatRect fr = r.getGlobalBounds();

		if(r.getPosition().y >= 0) {
			sf::Color color = getColisionColor(r.getPosition().x, r.getPosition().y, bimg, bSprite);
			if(color != sf::Color::Black) colorsColiding[color]  += sf::seconds(deltatime);
			sf::Color color2 = getColisionColor(r.getPosition().x + fr.width, r.getPosition().y, bimg, bSprite);
			if(color2 != sf::Color::Black) colorsColiding[color2] += sf::seconds(deltatime);
			sf::Color color3 = getColisionColor(r.getPosition().x, r.getPosition().y + fr.height , bimg, bSprite);
			if(color3 != sf::Color::Black) colorsColiding[color3] += sf::seconds(deltatime);
			sf::Color color4 = getColisionColor(r.getPosition().x + fr.width, r.getPosition().y + fr.height, bimg, bSprite);
			if(color4 != sf::Color::Black) colorsColiding[color4] += sf::seconds(deltatime);
		}
		
		std::stringstream ss;
		for (std::map<sf::Color, sf::Time>::iterator it=colorsColiding.begin(); it!=colorsColiding.end(); ++it){
			std::string col = "wat:";
			sf::Color aux = (it->first);
			if(aux.r > aux.g and aux.r > aux.b) {
				if(aux.g < 100) col = "Red:";
				else col = "Yellow";
			}
			else if(aux.g > aux.r and aux.g > aux.b) col = "Green:";
			else if(aux.b > aux.g and aux.b > aux.r) col = "Blue:";
			if((int)(it->second).asSeconds() > 0) 
				ss << "   " << col << " " << (int)(it->second).asSeconds();		
		}
		std::string str = ss.str();
		text.setString(str);
		
		int max = 0;
		int min = 99999999;
		if(colorsColiding[sf::Color::White] != sf::seconds(0.0) || reboot){
			for (std::map<sf::Color, sf::Time>::iterator it=colorsColiding.begin(); it!=colorsColiding.end(); ++it){
				int num = (int)(it->second).asSeconds();
				if(num > 0) {
					if(num > max) max = num; if(num < min) min = num;
				}
			}
			//if(! max - min <= 3) reboot = true;
			if(max - min <= 3 || reboot) {
				if(!reboot)text.setString("YouWonTheGame!");
				else text.setString(" Nice try!");
				window.clear();
				window.draw(bSprite);
				window.draw(text);
				window.draw(r);
				window.display();
				sf::Clock c; float t = 0;
				while(t < 3){
					t += c.restart().asSeconds();
					timer.restart();
				}
				if(!reboot) ++pantalla;
				needshiet = true;
				reboot = false;
			}
			else reboot = true;
		}
		
        window.clear();
		window.draw(bSprite);
		window.draw(text);
        window.draw(r);
        window.display();
    }
}
