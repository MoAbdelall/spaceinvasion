#ifndef ALIENSCLASS_H_INCLUDED
#define ALIENSCLASS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
class alien{
public:
    alien(){

    }
    alien(int type,float x=0,float y=0){
        create(type,x,y);
    }
void create (int type,float x=0,float y=0){
    this->drawMe=1;
    this->type=type;
    this->x=x;
    this->y=y;
    switch(type){
    case 1:
        this->alienTexture.loadFromFile("invader-alien1.png");
        this->deathTexture.loadFromFile("invader-alien1-death2.png");
        break;
    case 2:
        this->alienTexture.loadFromFile("invader-alien2.png");
        this->deathTexture.loadFromFile("invader-alien2-death.png");
        break;
    case 3:
        this->alienTexture.loadFromFile("invader-alien3.png");
        this->deathTexture.loadFromFile("invader-alien3-death.png");
        break;
    default:
        this->alienTexture.loadFromFile("invader-alien1.png");
        this->deathTexture.loadFromFile("invader-alien1-death.png");
    }

    this->alienTexture.setSmooth(true);
    this->shape.setTexture(alienTexture);
    this->shape.scale(0.5,0.5);
    this->shape.setPosition(x,y);
}
void changePosition(float x,float y){
    this->x=x;
    this->y=y;
    this->shape.setPosition(x,y);
}
sf::Sprite getShape(){
return this->shape;
}

void kill(){
    deathTimer.restart();
    this->shape.setTexture(deathTexture);
    this->drawMe=0;
}
bool killAnimation(){
    if (deathTimer.getElapsedTime()<=sf::seconds(0.5)){
        return 1;
    }
    else return 0;
}
void bringBack(){
    this->shape.setTexture(alienTexture);
    drawMe=1;
}
bool alive(){
    return this->drawMe;
}
private:
bool drawMe;
int type;
sf::Texture deathTexture;
sf::Texture alienTexture;
sf::Sprite shape;
float x;
float y;
sf::Clock deathTimer;

};


#endif // ALIENSCLASS_H_INCLUDED
