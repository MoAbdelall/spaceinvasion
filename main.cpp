#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "aliensClass.h"
#include "bullet.h"

#include "functions1.h"
#include "animationClass.h"
#include <thread>
//#include "Ship.h"
#include<cstdlib>
#include<ctime>
#include<vector>
#include<string>
#include<fstream>
//#include<thread>

 int main()
{
    ifstream highScoreStream;
    highScoreStream.open("highScore.txt");
    string line;
    getline(highScoreStream,line);
    int highScore=atoi(line.c_str());
    highScoreStream.close();
    //cout<<highScore;
    sf::SoundBuffer buffer1;
    sf::SoundBuffer buffer2;
    sf::SoundBuffer buffer3;
    sf::SoundBuffer buffer4;
    sf::SoundBuffer buffer5;
    buffer1.loadFromFile("333782__projectsu012__8-bit-pitch-descalation-effect.wav");
    buffer2.loadFromFile("atari_boom.wav");
    buffer3.loadFromFile("458251__tolerabledruid6__you-died.wav");
    buffer4.loadFromFile("159081__bombstu__atari-st-beat-11.wav");
    buffer5.loadFromFile("344310__musiclegends__laser-shoot.wav");
    sf::Sound sound1;
    sf::Sound sound2;
    sf::Sound sound3;
    sf::Sound sound4;
    sf::Sound sound5;
    sound1.setBuffer(buffer1);
    sound2.setBuffer(buffer2);
    sound3.setBuffer(buffer3);
    sound4.setBuffer(buffer4);
    sound5.setBuffer(buffer5);
    sf::Music music;
    music.openFromFile("393818__sirkoto51__retro-game-overworld-loop-1.wav");
    sf::err().rdbuf(NULL);
    sf::RenderWindow window(sf::VideoMode(600, 700), "space invasion 1.0");
    window.setPosition(sf::Vector2i(400, 0));
    //thread loading(loadingScreen);

    //window.setVerticalSyncEnabled(true);
    //score and lives:
    int lives =3;
    int score=0;
    sf::Font font;
    font.loadFromFile("pixelated.ttf");
    //score:
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("Score: "+to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setPosition(20,20);

    sf::Text highScoreText;
    highScoreText.setFont(font);
    highScoreText.setString("High Score: "+to_string(highScore));
    highScoreText.setCharacterSize(24);
    highScoreText.setFillColor(sf::Color::Green);
    highScoreText.setPosition(20,50);

    //lives:
    sf::Text livesText;
    livesText.setFont(font);
    livesText.setString("lives: "+to_string(lives));
    livesText.setCharacterSize(24);
    livesText.setFillColor(sf::Color::Green);
    livesText.setPosition(400,20);
    //bullet :
    bullet Bullet(sf::Vector2f(4, 16));
    //loading ship:
    sf::Texture shipTexture;
    shipTexture.loadFromFile("space-invaders-ship.png");
    sf::Texture shipTextureDead;
    sf::Texture shipTextureImmune;
    //shipTextureDead.loadFromFile("space-invaders-ship-dead.png");
    //animations:
    float explosionTime=1;
    //animation shipExplosion(9,9,899,857,"explosion-animated-og.png",explosionTime);
    animation shipExplosion(9,9,900,900,explosionTime);
    shipExplosion.start();
    //shipExplosion.setToTexture(shipTextureDead);
    shipTextureDead.loadFromFile("explosion-animated.png");
    shipTexture.setSmooth(true);
    shipTextureDead.setSmooth(true);
    shipTextureImmune.setSmooth(true);
    animation shipImmuneAnimation(2,1,200,100,0.3);
    shipImmuneAnimation.start();
    //shipImmuneAnimation.setToTexture(shipTextureImmune);
    shipTextureImmune.loadFromFile("space-invaders-ship-immune.png");
    sf::Sprite ship;
    ship.setTexture(shipTexture);
    ship.scale(0.5,0.5);
    sf::FloatRect shipBox = ship.getGlobalBounds();
    bool shipKilled=0;
    bool freezeShip=0;
    bool shipImmune=0;
    sf::Clock shipKilledClock;
    shipKilledClock.restart();
//    float x=window.getSize().x/2-shipBox.width/2;
//    float y=window.getSize().y-shipBox.height;
    ship.setPosition(window.getSize().x/2-shipBox.width/2,window.getSize().y-shipBox.height);
    //aliens:
        //aliens motion initial values:
        bool revert=0;
        bool skip=0;
        //aliens clock:

        sf::Clock aliensClock;
        sf::Clock shots;
        //initial position values of aliens:
    bool emptyRowFlag;
    bool emptyRows[8]={0,0,0,0,0,0,0};
    float aliensLeft=50;
    float aliensNewLeft=aliensLeft;
    float aliensRight=aliensLeft+8*55;
    float aliensNewRight= aliensRight;
    float aliensTop=200;
    alien aliens[3][8];
    float xPos=aliensLeft+15*0.5;
    float yPos=aliensTop+0;
    for (int i=0;i<=2;i++){
        for(int j=0;j<=7;j++){

            aliens[i][j].create(i+1,xPos,yPos);
            xPos+=110*0.5;
        }
        xPos=aliensLeft;
        yPos+=100*0.5;
    }
    //Hefnawy
    std::vector<bullet> bulletvec;
    //frames:
    window.setFramerateLimit(60);
        //Hefnawy
    bool isfiring=false;
    //main loop:
    music.setVolume(50);
    music.play();
    while (window.isOpen())
    {
        //Events:
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
                ofstream highScoreOut;
                highScoreOut.open("highScore.txt");
                highScoreOut<<highScore;
                highScoreOut.close();
            }

        }

        //shooting:
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&Bullet.notOnScreen()&&!freezeShip){
                Bullet.setpos(sf::Vector2f(shipBox.left+shipBox.width/2-2,shipBox.top));
                sound5.play();
            }
            if (Bullet.getpos().x!=0.0f &&Bullet.getpos().y!=0.0f){
                Bullet.shoot(5);
                }
            if (Bullet.getpos().y<=50){
              Bullet.removeMe();
            }
        //detecting empty rows:
        for(int j=0;j<=7;j++){
            emptyRowFlag=1;
            for (int i=0;i<=2;i++){
                if (aliens[i][j].alive()){
                    emptyRowFlag=0;
                }
            }
            if (emptyRowFlag==1){
                emptyRows[j]=1;
            }
        }
        //restarting:
          //restarting:
        if(onesLeft(emptyRows,8)==8){
             aliensLeft=50;
             aliensNewLeft=aliensLeft;
             aliensRight=aliensLeft+8*55;
             aliensNewRight= aliensRight;
             aliensTop=200;
             aliensClock.restart();

             for (int i=0;i<=2;i++){
            for(int j=0;j<=7;j++){
                aliens[i][j].bringBack();
                emptyRows[j]=0;
            }}
        }
        //aliens motion:
            srand(time(0));
            aliensRight=aliensLeft+8*55;
            aliensNewLeft=aliensLeft+onesLeft(emptyRows,8)*55;
            aliensNewRight=aliensRight-onesRight(emptyRows,8)*55;
            //detecting boundaries :
                if (aliensNewLeft<=20){
                    if (revert==1){
                        skip=1;
                    }
                    revert=0;
                }
                if (aliensNewRight>=window.getSize().x-20){
                    if (revert==0){
                        skip=1;
                    }
                    revert=1;
                }
            //clock
        if (aliensClock.getElapsedTime()>=sf::seconds(1)){
            if (!skip){
            aliensLeft+=revert?-30:30;
            }

            else{
                aliensTop+=10;
                skip=0;
            }
            aliensClock.restart();
        }
            //redrawing:
        xPos=aliensLeft+15*0.5;
        yPos=aliensTop;
        for (int i=0;i<=2;i++){
            for(int j=0;j<=7;j++){
                //killing
                sf::FloatRect alienBox = aliens[i][j].getShape().getGlobalBounds();
                sf::FloatRect bulletBox = Bullet.getShape().getGlobalBounds();
                if(alienBox.intersects(bulletBox)&&aliens[i][j].alive()){
                    aliens[i][j].kill();
                    Bullet.removeMe();
                    score+=10;
                    sound1.play();
                }
                //changing position:
                aliens[i][j].changePosition(xPos,yPos);
                xPos+=110*0.5;
            }
            xPos=aliensLeft;
            yPos+=100*0.5;
        }
        //ship motion:
        shipBox = ship.getGlobalBounds();
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)||sf::Keyboard::isKeyPressed(sf::Keyboard::A))&&shipBox.left>0&&!freezeShip){
            ship.move(-3,0);

        }
        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)||sf::Keyboard::isKeyPressed(sf::Keyboard::D))&&shipBox.left+shipBox.width<window.getSize().x&&!freezeShip){
            ship.move(3,0);
        }
        if (shots.getElapsedTime()>=sf::seconds(2)){
                isfiring=true;
                shots.restart();
        }


        //draw next frame:
        window.clear();
        //draw aliens:
        for (int i=0;i<=2;i++){
            for(int j=0;j<=7;j++){
                if(aliens[i][j].alive()||aliens[i][j].killAnimation()){
                window.draw(aliens[i][j].getShape());
                }
            }
        }
        //draw other things:
    //Hefnawy
    //aliens bullets:
		if (isfiring==true){
        for(int i=0;i<((rand()%4)+2);i++){
                bullet newBullet(sf::Vector2f(4,16));
                int r=rand()%3;
                int c=rand()%7;
                if(aliens[r][c].alive()==true){
                sf::FloatRect gunBox = aliens[r][c].getShape().getGlobalBounds();
                newBullet.setpos(sf::Vector2f(gunBox.left+gunBox.width/2-2,gunBox.top));
                newBullet.color(r);
                bulletvec.push_back(newBullet);
                isfiring = false;
            }
        }
            shots.restart();
        }
            //Hefnawy
        for (int i = 0; i < bulletvec.size(); i++) {
			bulletvec[i].draw(window);
			bulletvec[i].shoot(-5);
		}
		for (int i=0;i<bulletvec.size();i++){
            sf::FloatRect bullBox = bulletvec[i].getShape().getGlobalBounds();
            if(shipBox.intersects(bullBox)&&!freezeShip&&!shipImmune){
                    bulletvec[i].removeMe();
                    shipKilled=1;
                    shipKilledClock.restart();
                    shipExplosion.start();
                    sound2.play();
                    //ship.setPosition(sf::Vector2f(41235,45215));
                    lives--;
//                    if (lives==0){
//                        music.stop();
//                        if (score<240){
//                        sound3.play();
//                        gameOver(window,score);
//                        }
//                        else{
//                        sound4.play();
//                        gameOver(window,score);
//                        }
//                    }
                }
		}
		//killing ship:
		if (shipKilled){
            //shipExplosion.update();
            //shipExplosion.setToTexture(shipTextureDead);
            ship.setTexture(shipTextureDead);
            ship.setTextureRect(shipExplosion.update());
            freezeShip=1;
            if(shipKilledClock.getElapsedTime()>sf::seconds(explosionTime)){
                freezeShip=0;
                shipKilled=0;
                shipKilledClock.restart();
                ship.setTexture(shipTexture);
                ship.setTextureRect({0,0,100,100});
                    if (lives<=0){
                        music.stop();
                        ofstream highScoreOut;
                        highScoreOut.open("highScore.txt");
                        highScoreOut<<highScore;
                        highScoreOut.close();
                        if (score<240){
                        sound3.play();
                        gameOver(window,score);
                        }
                        else{
                        sound4.play();
                        gameOver(window,score);
                        }
                    }
            }
		}
        if(shipKilledClock.getElapsedTime()<sf::seconds(1)){
            shipImmune=1;
            if(!shipKilled){
                //shipImmuneAnimation.update();
                //shipImmuneAnimation.setToTexture(shipTextureImmune);
                ship.setTexture(shipTextureImmune);
                ship.setTextureRect(shipImmuneAnimation.update());
            }
        }
        else{
            shipImmune=0;
            ship.setTexture(shipTexture);
            ship.setTextureRect({0,0,100,100});
        }
        //remove later:
//            shipImmuneAnimation.update();
//                shipImmuneAnimation.setToTexture(shipTextureImmune);
//                ship.setTexture(shipTextureImmune);
        //
       // window.draw(Bullet);
        Bullet.draw(window);
        window.draw(ship);
        scoreText.setString("Score: "+to_string(score));
        window.draw(scoreText);
        if (score>highScore){
            highScore=score;
        }
        highScoreText.setString("High Score: "+to_string(highScore));
        window.draw(highScoreText);
        livesText.setString("lives: "+to_string(lives));
        window.draw(livesText);
        window.display();
    }

    return 0;
}
