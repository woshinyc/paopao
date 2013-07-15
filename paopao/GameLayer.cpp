//
//  GameLayer.cpp
//  paopao
//
//  Created by NycMac on 13-7-10.
//
//

#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Tool.h"
#include "LineInfo.h"

using namespace CocosDenshion;
CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
     allSize=CCDirector::sharedDirector()->getWinSize();
    spriteBatch=CCSpriteBatchNode::create("ballC.png");
    addChild(spriteBatch);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ballC.plist");
    setTouchEnabled(true);

    //开始创建泡泡
    //************************************************
    for (int n=0; n<defaultLine; n++) {
        if (n%2==0) {
            this->getAlinePaoPao(fullLine,n);
        }else{
            this->getAlinePaoPao(unFullLine,n);
        }
    }

    //结束创建泡泡
    //************************************************
 this->createBall();
    schedule(schedule_selector(GameLayer::step), 1/60);
    return true;
}

#pragma mark-创建泡泡
void GameLayer::getAlinePaoPao(LineType type,int lineNum)
{
    float paoHeight =allSize.height-paopaoWidth*lineNum;
    if (allPaopaoArray==NULL) {
        allPaopaoArray=CCArray::create();
        allPaopaoArray->retain();
    }
    int x=0;
    allSize=CCDirector::sharedDirector()->getWinSize();
    x=allSize.width*0.5 -fullNum*0.5*paopaoWidth;
    
    if (type==fullLine) {
        for (int n=0; n<fullNum; n++) {
            Ball *thisBall=Ball::getBall();
           
            allPaopaoArray->addObject(thisBall);
            thisBall->setAnchorPoint(ccp(0, 1));
             thisBall->setPosition(ccp(paopaoWidth*n, paoHeight));
            spriteBatch->addChild(thisBall);
        }
    }else if (type==unFullLine)
    {
        for (int n=0; n<fullNum-1; n++) {
             Ball *thisBall=Ball::getBall();
            allPaopaoArray->addObject(thisBall);
            thisBall->setAnchorPoint(ccp(0, 1));
             thisBall->setPosition(ccp(paopaoWidth*(n+0.5), paoHeight));
            spriteBatch->addChild(thisBall);
        }
    }
     
    
}
#pragma mark - 创建大炮
 void GameLayer::createCannon()
{

}
#pragma mark - 制作新的泡泡
void GameLayer::createBall()
{
    Ball *aBall=Ball::getBall();
    aBall->setPosition(paopaoCPP);
    spriteBatch->addChild(aBall);
    
    beFireBall=aBall;
}

#pragma mark - 发射泡泡
void GameLayer::fireBall(CCPoint po)
{
    CCPoint beganPo=beFireBall->getPosition();
    CCPoint endPo=po;
    CCPoint absolutePo=Tool::getOffset(beganPo, endPo);
    float radian=ccpToAngle(absolutePo);
    //beFireBall->speed=paopaoSpeed;
    beFireBall->setSpeedAndRadian(paopaoSpeed, radian);

}
#pragma mark-触摸
void GameLayer::ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch *touch = (CCTouch *)(*it);
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);

    
}
void GameLayer::ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    CCTouch *touch = (CCTouch *)(*iter);
    CCPoint touchLocation = touch->getLocationInView();
  touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
}
void GameLayer::ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent)
{
    CCSetIterator iter = pTouches->begin();
    CCTouch *touch = (CCTouch *)(*iter);
    CCPoint touchLocation = touch->getLocationInView();
  touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    this->fireBall(touchLocation);
    
}


#pragma mark-计时器
void GameLayer::step()
{
    bool pengzhuang =false;
    if (beFireBall!=NULL&&beFireBall->speed>0) {
        beFireBall->setPositionX(beFireBall->getPosition().x+beFireBall->speedX);
        beFireBall->setPositionY(beFireBall->getPosition().y+beFireBall->speedY);
        CCSize spriteSize=beFireBall->getContentSize();
        CCPoint upPoint   =beFireBall->convertToWorldSpace(ccp(spriteSize.width/2, spriteSize.height));
        CCPoint downPoint  =beFireBall->convertToWorldSpace(ccp(spriteSize.width/2,0));
        CCPoint leftPoint  =beFireBall->convertToWorldSpace(ccp(0,spriteSize.height/2));
        CCPoint rightPoint =beFireBall->convertToWorldSpace(ccp(spriteSize.width,spriteSize.height/2));
        //setTextureRect
        //*****************得到碰撞点
        
        //*****************碰撞墙壁
        if (leftPoint.x<3) {
            beFireBall->speedX=fabsf(beFireBall->speedX);
        }
        
        if (rightPoint.x>allSize.width-3) {
            beFireBall->speedX=-fabsf(beFireBall->speedX);
        }
        if (upPoint.y>allSize.height-2) {
            beFireBall->beStop();
            pengzhuang=true;
            allPaopaoArray->addObject(beFireBall);
        }

    }
    if (allPaopaoArray!=NULL) {
        int nub=allPaopaoArray->count();
        for (int n=0; n<nub; n++) {
            Ball *thisBall=( Ball *)allPaopaoArray->objectAtIndex(n);
            if (thisBall->isDrop==false &&beFireBall->isCollision(thisBall)) {
                beFireBall->beStop();
                pengzhuang=true;
                allPaopaoArray->addObject(beFireBall);
                
            }
            if (thisBall->isDrop) {
                thisBall->setPositionY(thisBall->getPositionY()-10);
            }
        }
    }

    if (pengzhuang) {
        this->findOtherSame(beFireBall);
        this->createBall();
    }
    int endNub=allPaopaoArray->count();
    for (int n=endNub-1; n>=0; n--) {
        Ball *thisBall=( Ball *)allPaopaoArray->objectAtIndex(n);
        if (thisBall->getPositionY()<0) {
            thisBall->removeFromParent();
            allPaopaoArray->removeObject(thisBall);
        }
    }

}
#pragma mark - 检测
void GameLayer::findOtherSame(Ball *sameBall)
{
    int nub=allPaopaoArray->count();
    for (int n=0; n<nub; n++) {
        Ball *thisBall=( Ball *)allPaopaoArray->objectAtIndex(n);
        if (thisBall->isDrop==false) {
            if (thisBall!=sameBall&&sameBall->isCollision(thisBall)&&thisBall!=beFireBall&&sameBall->typeNum==thisBall->typeNum) {
                if (sameBall!=beFireBall) {
                    thisBall->isDrop=true;
                    sameBall->isDrop=true;
                    beFireBall->isDrop=true;
                }
               
                this->findOtherSame(thisBall);
            }
        }
    }

}


