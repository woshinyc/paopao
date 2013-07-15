//
//  Ball.cpp
//  paopao
//
//  Created by NycMac on 13-7-10.
//
//

#include "Ball.h"
#include "enumWhole.h"
#include "AppDelegate.h"
#include "GameLayer.h"
bool Ball::init()
{
    if (!SpriteBase::init()) {
        return false;
    }
    
    return true;
}

Ball* Ball::getBall()
{
    Ball *ball=Ball::create();
    int numType=ballTypeNum;
    CCString *st=CCString::createWithFormat("ball%i.png",numType);
    ball->initWithSpriteFrameName(st->getCString());
    ball->typeNum=numType;
    return ball;
}
int Ball::getLineNub()
{
    float height =worldHeight-this->getPositionY();
    int lineNub=height/paopaoHeight;
    return lineNub;
}
int Ball::getNubInLine()
{
    float x=this->getRectangle().origin.x;
    int nubInLine=(int)x/paopaoWidth;
    return nubInLine;
}
void Ball::beStop()
{
    SpriteBase::beStop();
      // setPositionY((int)(getPositionY()/paopaoHeight)*paopaoHeight);
    float height=CCDirector::sharedDirector()->getWinSize().height;
//    //int addY=(int)getPositionY()%paopaoHeight;
//  int addY= (int)(height-getPositionY())%paopaoHeight;
//    CCLog("addY=%i",addY);
//    if (addY==0) {
//          setPositionY(getPositionY()+addY);
//    }else{
//      setPositionY(getPositionY()+addY-paopaoHeight);
//    }
    int lineNum=(int)((height-getPositionY())/paopaoHeight);
    if (((int)(height-getPositionY())%paopaoHeight)>paopaoHeight*0.1) {
        lineNum++;
    }
    CCLog("n=%i",lineNum);
    setPositionY(height-paopaoWidth*lineNum);


    
    if (mainLayer!=NULL) {
          GameLayer *gl=(GameLayer *)mainLayer;
        bool isFull=(int)(getPositionY()/paopaoHeight)%2==0?!gl->firstLineIsFull:gl->firstLineIsFull;
        int nn=0;
        if (((int)getPositionX()%paopaoWidth)>paopaoWidth*0.5) {
            nn=1;
        }
        if (isFull) {
              setPositionX((0.5+nn+(int)(getPositionX()/paopaoWidth))*paopaoWidth);
        }else{
         setPositionX((nn+(int)(getPositionX()/paopaoWidth))*paopaoWidth);
        }
        
    }
  
 
  
 
    
}
