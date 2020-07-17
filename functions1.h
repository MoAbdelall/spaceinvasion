#ifndef FUCTIONS1_H_INCLUDED
#define FUCTIONS1_H_INCLUDED
//void collcheck(bullet bullet,alien alien){
//    sf::FloatRect alienBox = alien.getShape.getGlobalBounds();
//    sf::FloatRect bulletBox = bullet.getShape.getGlobalBounds();
//    if(alienBox.intersects(bulletBox){
//        alien.kill();
//    }
//}
float onesLeft(bool*arr,int arrSize){
    if (arr[0]==0){
        return 0;
    }
    else if(arrSize==1){
        return 1;
    }
    else{
        return 1+onesLeft(arr+1,arrSize-1);
    }
}
float onesRight(bool*arr,int arrSize){
        if (arr[arrSize-1]==0){
        return 0;
        }
    else if(arrSize==1){
        return 1;
    }
    else{
        return 1+onesRight(arr,arrSize-1);
    }
}
void gameOver(sf::RenderWindow &window,int score){
    sf::Font font;
    font.loadFromFile("pixelated.ttf");
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("score: "+to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Green);
    sf::FloatRect scoreBox=scoreText.getGlobalBounds();

    sf::Text gameOverText;
    gameOverText.setFont(font);
    if (score<240){
        gameOverText.setString("GAME OVER");
    }
    else{
        gameOverText.setString("GOOD JOB");
    }
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Green);
    sf::FloatRect gameOverBox=gameOverText.getGlobalBounds();
    gameOverText.setPosition(window.getSize().x/2-gameOverBox.width/2,window.getSize().y/2-gameOverBox.height/2);
    scoreText.setPosition(window.getSize().x/2-scoreBox.width/2,window.getSize().y/2-scoreBox.height/2+gameOverBox.height*2);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(gameOverText);
        window.draw(scoreText);
        window.display();
    }
}
/*void loadingScreen(sf::RenderWindow &window){
    sf::Font font;
    font.loadFromFile("pixelated.ttf");
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setString("....... ");
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::Green);
    sf::FloatRect scoreBox=scoreText.getGlobalBounds();

    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("Loading");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Green);
    sf::FloatRect gameOverBox=gameOverText.getGlobalBounds();
    gameOverText.setPosition(window.getSize().x/2-gameOverBox.width/2,window.getSize().y/2-gameOverBox.height/2);
    scoreText.setPosition(window.getSize().x/2-scoreBox.width/2,window.getSize().y/2-scoreBox.height/2+gameOverBox.height*2);

        window.clear();
        window.draw(gameOverText);
        window.draw(scoreText);
        window.display();

}*/
#endif // FUCTIONS1_H_INCLUDED
