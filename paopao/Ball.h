//
//  Ball.h
//  paopao
//
//  Created by NycMac on 13-7-10.
//
//

#ifndef __paopao__Ball__
#define __paopao__Ball__

#include <iostream>
#include "SpriteBase.h"
class Ball:public SpriteBase
{
public:
    virtual bool init();
    CREATE_FUNC(Ball);
    static Ball *getBall();
    int typeNum;
    int getLineNub();
    int getNubInLine();
    bool isDrop;
    
 
    
};

#endif /* defined(__paopao__Ball__) */
