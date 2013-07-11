//
//  LineInfo.h
//  paopao
//
//  Created by NycMac on 13-7-10.
//
//

#ifndef __paopao__LineInfo__
#define __paopao__LineInfo__
#include "ObjectBase.h"
#include "enumWhole.h"
USING_NS_CC;
class LineInfo :public ObjectBase
{
public:
	LineInfo(void);
	~LineInfo(void);
    CCArray *lineArray;
    LineType lineType;
    
};

#endif /* defined(__paopao__LineInfo__) */
