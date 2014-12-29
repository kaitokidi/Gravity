//LUDUM DARE 30
#include <map>
#include <string>
#include <sstream>   
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace sf{
	bool operator< (const sf::Color& c1, const sf::Color& c2){
		if(c1.r < c2.r) return true; else if(c1.r > c2.r) return false;
		else if(c1.g < c2.g) return true; else if(c1.g > c2.g) return false;
		else if(c1.b < c2.b) return true; else if(c1.b > c2.b) return false;
		else if(c1.a < c2.a) return true; else if(c1.a > c2.a) return false;
		else return false;
	}
}
sf::Color getColisionColor(float posx, float posy, sf::Image& img, sf::Sprite& bSprite){
	return img.getPixel( posx/bSprite.getScale().x, posy/bSprite.getScale().y);
}

int main(int argc, const char* argv[]){
    
    sf::Vector2f v = sf::Vector2f(0,0);
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Gravity");
       sf::Vector2f screenSize = sf::Vector2f(window.getSize().x,window.getSize().y);
    float g = (int)screenSize.y*2 ;

    sf::RectangleShape r(sf::Vector2f(screenSize.x/10, screenSize.y/10));
    r.setPosition(0,0); r.setFillColor(sf::Color::White);
    
    sf::Clock timer;
    float deltatime = 0;
	float ground = screenSize.y-4; //  float ground = screenSize.y*6/7;
	
	sf::Text text; sf::Font font; 
	if(! font.loadFromFile("font.ttf")) std::cout << "penguin" << std::endl;
	text.setFont(font); text.setPosition(0,0); text.setString("penguin <3");
	text.setColor(sf::Color(255,255,255));
	
	sf::Image bimg;
	sf::Texture bTex;
	sf::Sprite bSprite;
	
	std::map<sf::Color, sf::Time> colorsColiding;

	int pantalla = 0;
	if(argc > 1) pantalla = atoi(argv[1]);
	bool reboot = false;
	bool needshiet = true;
	
    //GAME LOOP
    while(window.isOpen()){
		if(needshiet){
				ground = screenSize.y-4;
				g = (int)screenSize.y*2;
				v = sf::Vector2f(0,0);
				colorsColiding.clear();
				r = sf::RectangleShape(sf::Vector2f(screenSize.x/10, screenSize.y/10));
				r.setPosition(0,0);
				r.setFillColor(sf::Color::White);
				std::stringstream s;
				s << "board" << pantalla;		
				std::string board = s.str();
				if(!bimg.loadFromFile(board+".png")) std::cout << "I CAN'T LOAD BOARD IMAGE" << std::endl;
				if(!bTex.loadFromFile(board+".png")) std::cout << "I CAN'T LOAD BOARD texture" << std::endl;
				bSprite.setTexture(bTex, true);
				
 				bSprite.setScale(screenSize.x/bSprite.getLocalBounds().width , 
 								screenSize.y/bSprite.getLocalBounds().height);
				
				needshiet = false;
				deltatime = 0;
		}
		
        deltatime = timer.restart().asSeconds();
        
        sf::Event event;
        while(window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close(); 
			if (event.type == sf::Event::Resized) {window.setSize(sf::Vector2u(event.size.width, event.size.height)); needshiet = true;}
			if (pantalla < 2 && event.type == sf::Event::MouseButtonPressed){
					if (event.mouseButton.button == sf::Mouse::Left) {
						r.setPosition(event.mouseButton.x*screenSize.x/window.getSize().x, event.mouseButton.y*screenSize.y/window.getSize().y);
					}
			}
		}
		if(r.getPosition().y > 0){
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up   ))  v.y = (float)screenSize.y/2 * -1;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W   ))  v.y = (float)screenSize.y/2 * -1;
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))  v.y = (float)screenSize.y/1.5 * -1;
		}
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left ))  v.x = (float)screenSize.x/20 * -1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A ))  v.x = (float)screenSize.x/20 * -1;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))  v.x = (float)screenSize.x/20;
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))  v.x = (float)screenSize.x/20;

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) { reboot = true; v.x = 0; }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        
		if(pantalla < 2) r.move(v*3.0f * deltatime);
        else r.move(v * deltatime);
        
		if(r.getPosition().y < 0) {v.y += g*deltatime;}
        if( (r.getPosition().y + r.getSize().y) < ground || v.y < 0) v.y += g *deltatime;
        else {
            r.setPosition(r.getPosition().x, ground - r.getSize().y);
            v.y = 0;
        }
        r.setOutlineColor(sf::Color::White);
		r.setOutlineThickness(1);
        
		if(r.getPosition().x < 1) r.setPosition(1, r.getPosition().y);
        if(r.getPosition().x + r.getSize().x+3 > screenSize.x){
			r.setPosition(screenSize.x-r.getSize().x-3, r.getPosition().y);
			//std::cout << window.getSize().x-r.getSize().x-3 << " my pos ----- wind size" << window.getSize().x << std::endl;
		}
        
   	sf::VertexArray pj(sf::Quads, 4);
        sf::FloatRect fr = r.getGlobalBounds();
	pj[0].position = sf::Vector2<float>(r.getPosition().x, r.getPosition().y);
	pj[1].position = sf::Vector2<float>(r.getPosition().x + fr.width-2, r.getPosition().y);
	pj[3].position = sf::Vector2<float>(r.getPosition().x, r.getPosition().y + fr.height-2);
	pj[2].position = sf::Vector2<float>(r.getPosition().x + fr.width-2, r.getPosition().y + fr.height-2);

	for(int i = 0; i < 4; ++i) pj[i].color = sf::Color::Black;
	
		if(r.getPosition().y >= 0 && r.getPosition().x+r.getSize().x < screenSize.x-1 && r.getPosition().x > 1 && r.getPosition().y+r.getSize().y < screenSize.y) {

			sf::Color color = getColisionColor(r.getPosition().x, r.getPosition().y, bimg, bSprite);
			if(color != sf::Color::Black) colorsColiding[color]  += sf::seconds(deltatime);
			sf::Color color2 = getColisionColor(r.getPosition().x + fr.width, r.getPosition().y, bimg, bSprite);
			if(color2 != sf::Color::Black) colorsColiding[color2] += sf::seconds(deltatime);
			pj[0].color = color; pj[1].color = color2; 
			sf::Color color3 = getColisionColor(r.getPosition().x, r.getPosition().y + fr.height , bimg, bSprite);
			if(color3 != sf::Color::Black) colorsColiding[color3] += sf::seconds(deltatime);
			sf::Color color4 = getColisionColor(r.getPosition().x + fr.width, r.getPosition().y + fr.height, bimg, bSprite);
			if(color4 != sf::Color::Black) colorsColiding[color4] += sf::seconds(deltatime);
			pj[3].color = color3; pj[2].color = color4;   
		}
		else if(r.getPosition().y+fr.height >= 0){
  			sf::Color color3 = getColisionColor(r.getPosition().x, r.getPosition().y + fr.height , bimg, bSprite);
			if(color3 != sf::Color::Black) colorsColiding[color3] += sf::seconds(deltatime);
			sf::Color color4 = getColisionColor(r.getPosition().x + fr.width, r.getPosition().y + fr.height, bimg, bSprite);
			if(color4 != sf::Color::Black) colorsColiding[color4] += sf::seconds(deltatime);
			pj[3].color = color3; pj[2].color = color4;     
		}
		
		std::map<std::string, int> colorTimers;
		colorTimers["Red:"] = colorTimers["Yellow:"] = colorTimers["Green:"] = colorTimers["Blue:"] = 0; 
		
		for (std::map<sf::Color, sf::Time>::iterator it=colorsColiding.begin(); it!=colorsColiding.end(); ++it){
			std::string col = "wat:";
			sf::Color aux = (it->first);
			if(aux.r >= aux.g and aux.r >= aux.b) {
				if(aux.g < 100) col = "Red:";
				else col = "Yellow:";
			}
			else if(aux.g >= aux.r and aux.g >= aux.b) col = "Green:";
			else if(aux.b >= aux.g and aux.b >= aux.r) col = "Blue:";
			if((int)(it->second).asSeconds() > 0) 
				colorTimers[col] += (int)(it->second).asSeconds();
		}
		
		std::stringstream ss;
		for (std::map<std::string, int>::iterator it=colorTimers.begin(); it!=colorTimers.end(); ++it){
			if(it->second > 0) 
				ss << " " << it->first << "" << it->second;		
		}
		std::string str = ss.str();
		text.setString(str);
		
		sf::Text textBg = text;
		textBg.setScale(1.1,1.1);
		textBg.setColor(sf::Color(100,100,100));
		
		int max = 0;
		int qtty = 0;
		int min = 99999999;
		if(colorsColiding[sf::Color::White] != sf::seconds(0.0) || reboot){
			for (std::map<std::string, int>::iterator it=colorTimers.begin(); it!=colorTimers.end(); ++it){
				int num = (int)(it->second);
				if(num > 0) {
					if(num > max) max = num; if(num < min) min = num;
					++qtty;
				}
			}
			if((max - min <= 3 && qtty >= 4) || reboot || pantalla < 2) {
				std::ostringstream oss;
				oss << max;
				std::string strn = oss.str();
				if(!reboot) str = "YouWonTheGame! punctuation = " + strn;	//text.setString("YouWonTheGame!   punctuation = " + strn);
				else str = " Nice try! "; 									//text.setString(" Nice try!");
				window.clear();
				window.draw(bSprite);
				if(pantalla >= 2){
					for(int i = 0; i < str.size(); ++i) {
						text.setString(str[i]);
						textBg.setString(str[i]);
						text.setPosition(text.getCharacterSize()*i, 0);
						textBg.setPosition(text.getCharacterSize()*i, 0);
						window.draw(textBg, sf::BlendAlpha);
						window.draw(text, sf::BlendAlpha);
					}
			    }
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
	window.draw(r);
	window.draw(pj, sf::BlendAlpha);
	for(int i = 0; i < str.size(); ++i) {
		text.setString(str[i]);
		textBg.setString(str[i]);
		text.setPosition(text.getCharacterSize()/1.5*i, 0);
		textBg.setPosition(text.getCharacterSize()/1.5*i, 0);
		window.draw(textBg, sf::BlendAlpha);
		window.draw(text, sf::BlendAlpha);
	}
	window.display();
    }
}
