//
//  GameLayer.h
//  paopao
//
//  Created by NycMac on 13-7-10.
//
//

#ifndef __paopao__GameLayer__
#define __paopao__GameLayer__

#include "cocos2d.h"
USING_NS_CC;
#include "enumWhole.h"
#include "Ball.h"
class GameLayer : public cocos2d::CCLayer
{
public:
    virtual bool init();
     void getAlinePaoPao(LineType type,int lineNum);//获得一列泡泡
    //**
      void step();
    //**
    static cocos2d::CCScene* scene();
    CCArray *allPaopaoArray;
    void menuCloseCallback(CCObject* pSender);
    void createCannon();
    void createBall();
    void fireBall(CCPoint po);
    void findOtherSame(Ball *sameBall);
    CCSize allSize;
    CCSpriteBatchNode *spriteBatch;
    CREATE_FUNC(GameLayer);
    Ball *beFireBall;
    bool firstLineIsFull;
    void findNoKeepBall();
    
    
    
    
    virtual void ccTouchesBegan(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet *pTouches,CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet *pTouches,CCEvent *pEvent);
};
#endif /* defined(__paopao__GameLayer__) */
