//
//  MaskSprite.h
//  RunnerPreMash
//
//  Created by firedragonpzy on 13-4-27.
//
//

#ifndef __RunnerPreMash__MaskSprite__
#define __RunnerPreMash__MaskSprite__

#include "cocos2d.h"
#include "HelloWorldScene.h"
USING_NS_CC;

class MaskSprite : public CCSprite, public CCTargetedTouchDelegate {
    
public:
    bool init();
    void onEnter();
    void onExit();
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    CCRect atlasRect();
    bool isContaintTouchLocation(CCTouch *pTouch);
    bool isContaintRect(CCRect rect);
    void update(float dt);
    void mask();
    
    static MaskSprite* create(const char *pszFilename);
private:
    CCRenderTexture *sourceTexture;
};

#endif /* defined(__RunnerPreMash__MaskSprite__) */
