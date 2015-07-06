#include "Effect.hpp"
    
Effect::Effect() { 
    activated = true;
    automatic = true;
    timeCounter = 0;
    actualAnimation = 0;
    timeBetweenAnimations = 1;
}

Effect::~Effect() { }

int Effect::loadAnimation(std::string name, int qtty, std::string ext) { 
    //std::cout << "loadAnimation" << std::endl;
    animation.clear();
    int errorPos = -1;
    for(int i = 0; i < qtty; ++i){
        std::stringstream s;
        s << name << i;
        std::string path = s.str();
        if(!loadFrame(path+"."+ext)) return errorPos = i;
    }
    //std::cout << "done" << std::endl;
    return errorPos;//return -1;
}


bool Effect::loadAnimation(std::vector<sf::Texture>& vector) { 
    animation.clear();
    animation = vector;
    return true;
}

bool Effect::loadHorizontalSpriteSheet(float qtty, std::string spriteSheet){
    sf::Image spriteSheetImage;
    if(! spriteSheetImage.loadFromFile(spriteSheet)) return false;
    else {
        float height = spriteSheetImage.getSize().y;
        float width  = spriteSheetImage.getSize().x/qtty;
        sf::Texture auxText;
        for(int i = 0; i < qtty; ++i){
            if(i*width > spriteSheetImage.getSize().x) return false;
            auxText.loadFromImage(spriteSheetImage, sf::IntRect(i*width,0,width, height));
            animation.push_back(auxText);
        }
    }
    return true;
}

bool Effect::loadVerticalSpriteSheet(float qtty, std::string spriteSheet){
    sf::Image spriteSheetImage;
    if(! spriteSheetImage.loadFromFile(spriteSheet)) return false;
    else {
        float width = spriteSheetImage.getSize().x;
        float height = spriteSheetImage.getSize().y/qtty;
        sf::Texture auxText;
        for(int i = 0; i < qtty; ++i){
            if(i*height > spriteSheetImage.getSize().y) return false;
            auxText.loadFromImage(spriteSheetImage, sf::IntRect(0,i*height,width, height));
            animation.push_back(auxText);
        }
    }
    return true;
}

bool Effect::loadSpriteSheet(float height, float width, float qttyVert, float qttyHoriz, std::string spriteSheet){
    sf::Image spriteSheetImage;
    if(! spriteSheetImage.loadFromFile(spriteSheet)) return false;
    else {
        float width = spriteSheetImage.getSize().x/qttyHoriz;
        float height = spriteSheetImage.getSize().y/qttyVert;
        sf::Texture auxText;
        for(int k = 0; k < qttyVert; ++k){
            if(k*height > spriteSheetImage.getSize().y) return false;
            for(int i = 0; i < qttyHoriz; ++i){
                if(i*width > spriteSheetImage.getSize().x) return false;
                auxText.loadFromImage(spriteSheetImage, sf::IntRect(k*height,i*height,width, height));
                animation.push_back(auxText);
            }
        }
    }
    return true;
}



bool Effect::loadFrame(std::string name, int position) { 
    if(position >= animation.size()) return false;
    return animation[position].loadFromFile(name);
}

bool Effect::loadFrame(std::string name) { 
    sf::Texture text;
    if(! text.loadFromFile(name)) return false;
    else animation.push_back(text);
    return true;
}

void Effect::updateAnimation(float deltatime) { 
    timeCounter += deltatime;
    if(timeCounter > timeBetweenAnimations){
        timeCounter = 0;
        if(automatic){
            inc_actualAnim();
            this->setTexture(animation[actualAnimation]);
        }
    }
}

void Effect::draw(sf::RenderWindow& window) {
    if(activated){
        window.draw((*this));
    }
}

void Effect::setActualAnimation(int newPosition)    { 
    actualAnimation = newPosition%animation.size(); 
}

int Effect::inc_actualAnim() { 
    actualAnimation = (actualAnimation+1)%animation.size();
}

int Effect::dec_actualAnim() { 
    actualAnimation = (actualAnimation-1)%animation.size();
}

void Effect::active()   { activated = true;  }
void Effect::inactive() { activated = false; }

void Effect::enableAutomaticAnimation()     { automatic = true;  }
void Effect::disableAutomaticAnimation()    { automatic = false; }

int Effect::getActualAnimation()                    { return actualAnimation;       }
float Effect::getTimeBetweenAnimations()            { return timeBetweenAnimations; }
void Effect::setTimeBetweenAnimations(float time)   { timeBetweenAnimations = time; }