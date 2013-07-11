//
//  Ball.cpp
//  paopao
//
//  Created by NycMac on 13-7-10.
//
//

#include "Ball.h"
#include "enumWhole.h"
bool Ball::init()
{
    if (!CCSprite::init()) {
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
