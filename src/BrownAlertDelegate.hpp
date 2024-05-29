#pragma once
#include <Geode/Geode.hpp>
using namespace geode::prelude;
class BrownAlertDelegate : public FLAlertLayer {
    protected:
        // layer size is stored here
        cocos2d::CCSize m_pLrSize;
        cocos2d::extension::CCScale9Sprite* m_pBGSprite;
        virtual bool init(
            float width,
            float height,
            const char* bg = "GJ_square01.png",
            const char* _title = ""
        );
        virtual void setup() = 0;
        virtual void keyDown(cocos2d::enumKeyCodes) override;
    public:
        virtual void onClose(cocos2d::CCObject*);
}; // firee made/sent me all of this thank you firee