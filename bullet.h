#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>

using namespace std;
class bullet{
public:
    bullet(sf::Vector2f size){
          Bullet.setSize(size);
          Bullet.setFillColor(sf::Color::White);
          Bullet.setPosition(0,-200);
    }
    void setpos(sf::Vector2f pos){
        Bullet.setPosition(pos);

    }
    void draw(sf::RenderWindow &window){
         window.draw(Bullet);
    }

    sf::Vector2f getpos(){
    return Bullet.getPosition();
    }
    void shoot(float speed){
    Bullet.move(sf::Vector2f(0,-speed));
    }
    sf::RectangleShape getShape(){
        return Bullet;
    }
    bool notOnScreen(){
        return Bullet.getPosition().y<=0;
    }
    void removeMe(){
        Bullet.setPosition(-200,-200);
    }
    void color(int r){
        switch(r){
                case 0:
                    Bullet.setFillColor(sf::Color::Green);
                    break;
                case 1:
                    Bullet.setFillColor(sf::Color::Red);
                    break;
                case 2:
                    Bullet.setFillColor(sf::Color::Blue);
                    break;
                default:
                    Bullet.setFillColor(sf::Color::White);
                }
    }
private:
    sf::RectangleShape Bullet;


};


#endif // BULLET_H_INCLUDED
