//
//  MaskSprite.cpp
//  RunnerPreMash
//
//  Created by firedragonpzy on 13-4-27.
//
//

#include "MaskSprite.h"

bool MaskSprite::init()
{
    bool bRet = false;
    do {
        bRet = true;
    } while (0);
    return  bRet;
}


MaskSprite* MaskSprite::create(const char *pszFilename)
{
    MaskSprite *sprite = new MaskSprite();
    if (sprite && sprite->initWithFile(pszFilename)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    sprite = NULL;
    return NULL;
}

void MaskSprite::update(float dt)
{
    
    if (getPositionX() > CCDirector::sharedDirector()->getWinSize().width) {
        this->setPosition(ccp(0,getPositionY() - getContentSize().height));
    }else
    {
        this->setPosition(ccp(getPositionX()+1,getPositionY()));
    }
    mask();
}


void MaskSprite::onEnter()
{
    CCSprite::onEnter();
     this->scheduleUpdate();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    sourceTexture =((HelloWorld*)getParent())->getSourceTexture();
}


void MaskSprite::onExit()
{
    CCSprite::onExit();
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}


bool MaskSprite::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    if (isContaintTouchLocation(pTouch)) {
        return true;
    }else
    {
        return false;
    }

}

void MaskSprite::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    CCPoint sub = pTouch->getDelta();
    CCPoint newPos = ccpAdd(this->getPosition(), sub);
    this->setPosition(newPos);
    mask();

}


CCRect MaskSprite::atlasRect()
{
    CCSize cSize = this->getContentSize();
    CCPoint point = this->getAnchorPointInPoints();
    return CCRectMake(-point.x, -point.y, cSize.width, cSize.height);
}

bool MaskSprite::isContaintTouchLocation(CCTouch *pTouch)
{
    return atlasRect().containsPoint(convertTouchToNodeSpaceAR(pTouch));
}


bool MaskSprite::isContaintRect(CCRect rect)
{
    return atlasRect().intersectsRect(rect);
}

void MaskSprite::mask()
{
    sourceTexture->begin();
    
	ccBlendFunc blendFunc;
    
	blendFunc.src = GL_ZERO;			
	blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;	
	this->setBlendFunc(blendFunc);
    
    this->visit();
    
	sourceTexture->end();
}


