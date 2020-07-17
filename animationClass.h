#ifndef ANIMATIONCLASS_H_INCLUDED
#define ANIMATIONCLASS_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <iostream>
class animation {
    public:
    animation (float xFrames,float yFrames,float width,float height,float time){
        dimentions[0]=width/xFrames;
        dimentions[1]=height/yFrames;
        this->xFrames=xFrames;
        this->yFrames=yFrames;
        i=0;
        j=0;
        float nFrames=xFrames*yFrames;
        currentFrameIndex=0;
        //textures.resize(nFrames);
        //this->file=file;
        //this->totalTime=sf::seconds(time);

        //cout<<totalTime.asSeconds()<<endl;
//        int k=0;
//        for(int j=0;j<=yFrames-1;j++){
//            for (int i=0;i<=xFrames-1;i++){
//                //frames.push_back({i*dimentions[0],j*dimentions[1],dimentions[0],dimentions[1]});
//                //sf::Texture newTexture;
//                //textures.push_back(newTexture);
//                textures[k].loadFromFile(file,{i*dimentions[0],j*dimentions[1],dimentions[0],dimentions[1]});
//                //cout<<frames[k].top<<"  "<<frames[k].left<<"  "<<frames[k].width<<"  "<<frames[k].height<<endl;
//                k++;
//                cout<<k<<endl;
//            }
//        }
        this->totalTime=sf::seconds(time);
        this->frameTime=sf::seconds(totalTime.asSeconds()/nFrames);
    }
//    void setToTexture(sf::Texture &texture){
//        //texture.loadFromFile(file,rectangle);
//        texture=textures[currentFrame];
//       // cout<<file<<rectangle.top<<endl;
//    }
    sf::IntRect update(){
         currentFrameIndex=animationClock.getElapsedTime().asSeconds()/frameTime.asSeconds();
       // cout<<frameTime.asSeconds()<<"    "<<currentFrame<<endl;
        if (animationClock.getElapsedTime()>totalTime){
            animationClock.restart();
         //   rectangle=frames[0];
            currentFrameIndex=0;
        }
        //currentFrameIndex=
        i=float(int(currentFrameIndex)%int(xFrames));
        j=float(int(currentFrameIndex/int(yFrames)));
        //cout<<i<<"   "<<j<<endl;
        //i=int(currentFrameIndex)%int(xFrames);
        //j=currentFrameIndex/yFrames;
        currentFrame={i*dimentions[0],j*dimentions[1],dimentions[0],dimentions[1]};
        //currentFrameIndex++;
        return currentFrame;
//        else{
//            rectangle=frames[currentFrame];
//           // cout<<"done this";
//        }
    }
    void start(){
        animationClock.restart();
    }
    private:
        //float time;
        //sf::Texture newTexture;
        //vector<sf::Texture> textures;
        sf::IntRect currentFrame;
        //int nFrames;
        //vector<sf::IntRect> frames;
        sf::Clock animationClock;
        float dimentions[2];
        float i;
        float j;
        float xFrames;
        float yFrames;
        int currentFrameIndex;
        //string file;
        //sf::IntRect rectangle;
        sf::Time totalTime;
        sf::Time frameTime;
};

#endif // ANIMATIONCLASS_H_INCLUDED
