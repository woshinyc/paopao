//
//  enumWhole.h
//  paopao
//
//  Created by NycMac on 13-7-10.
//
//

#ifndef paopao_enumWhole_h
#define paopao_enumWhole_h
#define fullNum  (int)(worldWidth/paopaoWidth)
#define ballTypeNum arc4random()%6+1
#define defaultLine  4
#define paopaoWidth 28
#define paopaoHeight 28
#define paopaoSpeed 9
#define paopaoCPP ccp(CCDirector::sharedDirector()->getWinSize().width/2,paopaoWidth/2)
#define worldHeight CCDirector::sharedDirector()->getWinSize().height
#define worldWidth CCDirector::sharedDirector()->getWinSize().width
typedef enum
{
 fullLine     ,
 unFullLine   ,


}LineType;

#endif
