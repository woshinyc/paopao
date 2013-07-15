//
//  SpriteBase.cpp
//  NycGame
//
//  Created by NycMac on 13-6-12.
//
//

#include "SpriteBase.h"
#include "enumWhole.h"


bool SpriteBase::init()
{
    if (!CCSprite::init()) {
        return false;
    }
    
    return true;
}
CCPoint SpriteBase::getCenterPoint()
{
  CCRect rect= this->getRectangle();
    return ccp(rect.origin.x+rect.size.width*0.5,rect.origin.y+rect.size.height*0.5);
}
CCRect SpriteBase::getRectangle()
{
    float x=this->getPosition().x-this->getContentSize().width*this->getAnchorPoint().x;
    float y=this->getPosition().y+this->getContentSize().height*(1-this->getAnchorPoint().y);
    CCRect rect=CCRectMake(x, y, this->getContentSize().width, this->getContentSize().height);
//    CCLog("aax=%f,y=%f w=%f,h=%f",x,y,rect.size.width,rect.size.height);
    return rect;
}


void SpriteBase::setHealthNum(int num)
{
    healthNum=num;
    if (healthNum<=0) {
        this->isUseless=true;
    }
}
int  SpriteBase::getHealthNum()
{
    return healthNum;

}
void SpriteBase::beAttack(int num)
{
    this->setHealthNum(healthNum-num);
}

void SpriteBase::setSpeedAndRadian(float _speed,float _radian)
{
    speed=_speed;
    radian=_radian;
    speedX=_speed *cosf(_radian);
    speedY=_speed *sinf(_radian);
    
}
bool SpriteBase::isCollision(SpriteBase *sp)
{
    CCRect sp1Rect=this->getRectangle();
    CCRect sp2Rect=sp->getRectangle();
    return sp1Rect.intersectsRect(sp2Rect);
}
bool SpriteBase::isCollision(SpriteBase *sp ,float num)
{
    CCRect sp1Rect=this->getRectangle();
    CCRect sp2Rect=sp->getRectangle();
    return sp1Rect.intersectsRect(sp2Rect);
}

void SpriteBase::beStop()
{
    speedX=0;
    speedY=0;
    speed=0;
    radian=0;

}
bool SpriteBase::isRoundCollision(SpriteBase *sp)
{
    CCRect sp1Rect=this->getRectangle();
    CCRect sp2Rect=sp->getRectangle();
    CCPoint point1=ccp((sp1Rect.origin.x+sp1Rect.size.width/2),(sp1Rect.origin.y-sp1Rect.size.height/2));
    CCPoint point2=ccp((sp2Rect.origin.x+sp2Rect.size.width/2),(sp2Rect.origin.y-sp2Rect.size.height/2));
    float distance= ccpDistance(point1, point2);
    return distance<sp1Rect.size.width*0.7;
}

