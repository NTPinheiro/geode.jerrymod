// if you see this i'm sorry for being bad at coding
// idk what i'm doing so half of this is just the default geode template

/**
 * Include the Geode headers.
 */
#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>


// how big is the popup code
// i cant even intereact with discord lol
// it was laggin

/**
 * Brings cocos2d and all Geode namespaces to the current scope.
 */
using namespace geode::prelude;

#include "BrownAlertDelegate.hpp"

class PiLayer : public BrownAlertDelegate {
    protected:
	// you create a class member to keep track
		int m_jerryCount;
		CCLabelBMFont* m_jerryLabel;
        float m_fWidth = s_defWidth;
    	float m_fHeight = s_defHeight;
        virtual void setup() override {
			//  WHATEVER YOU WANT IN HERE
			auto winSize = CCDirector::sharedDirector()->getWinSize();
			auto someSprite = CCSprite::create("pi.png"_spr);
			someSprite->setScale(0.1F); // a BIT TOO BIG
										// its 4000x3000 pixels lmaooooo 
										// WTF
			someSprite->setPosition({winSize / 2}); // the center of the screen
			// or you could also do someSprite->setPosition({winSize.width / 2, winSize.height / 2});
			this->m_mainLayer->addChild(someSprite); // this is for if you dont want to add it to the button menu
			// button menu usually is for menu buttons, or if youre too lazy to put it in the center
			// do you want to make it bigger
			// thats not the image i want there just haven't added it yet
			//xd you can change it lol
			// i know 
			// do you want the button to be on the bottom or top
			// bottom
			// do you want to increase the popup size (height)?
			// yeah because image can be bigger
			// creating a button hold on a second
			// oh it's beautiful

			// rambling between firee and me ^
			
			m_jerryLabel = CCLabelBMFont::create(std::to_string(m_jerryCount).c_str(), "bigFont.fnt");
			m_jerryLabel->setPosition({winSize.width / 2, (winSize.height / 2) + 70});
			this->m_mainLayer->addChild(m_jerryLabel);
			auto pressJerry = CCMenuItemSpriteExtra::create(
				ButtonSprite::create("say hi to jerry"), // creates a box with text on it (also our CCSprite)
				this,
				menu_selector(PiLayer::sayHiToJerry) // gonna change this
			);
			pressJerry->setPositionY(-70); // since its already centered, all we really need to do is change the Y
			this->m_buttonMenu->addChild(pressJerry);
		};
		void sayHiToJerry(CCObject*) {
			web::AsyncWebRequest()
			.post("https://api.ntpinheiro.com/counter")
			.text()
			.then([this](std::string const& jerrycount) {
				m_jerryCount++;
				m_jerryLabel->setString(std::to_string(m_jerryCount).c_str()); // update the counter
			})
			.expect([](std::string const& error) {
				FLAlertLayer::create(
					"Oh no!", // title
					"Something went wrong when trying to update the current count", // content
					"OK" // button
				);
			});
		}
    public:
        static constexpr const float s_defWidth = 250.0f;
        static constexpr const float s_defHeight = 190.0f;
        static PiLayer* create(std::string jerrycount) {
			auto pRet = new PiLayer();
			if (pRet) {
				pRet->m_jerryCount = std::stoi(jerrycount); // convert string to int
				if (pRet->init(PiLayer::s_defWidth, PiLayer::s_defHeight)) {
					pRet->autorelease();
					return pRet;
				}
			}
			CC_SAFE_DELETE(pRet);
			return nullptr;
		};
};

/**
 * `$modify` lets you extend and modify GD's classes.
 * To hook a function in Geode, simply $modify the class
 * and write a new function definition with the signature of
 * the function you want to hook.
 *
 * Here we use the overloaded `$modify` macro to set our own class name,
 * so that we can use it for button callbacks.
 *
 * Notice the header being included, you *must* include the header for
 * the class you are modifying, or you will get a compile error.
 *
 * Another way you could do this is like this:
 *
 * struct MyMenuLayer : Modify<MyMenuLayer, MenuLayer> {};
 */
#include <Geode/modify/MenuLayer.hpp>
class $modify(MyMenuLayer, MenuLayer) {
	/**
	 * Typically classes in GD are initialized using the `init` function, (though not always!),
	 * so here we use it to add our own button to the bottom menu.
	 *
	 * Note that for all hooks, your signature has to *match exactly*,
	 * `void init()` would not place a hook!
	*/
	bool init() {
		/**
		 * We call the original init function so that the
		 * original class is properly initialized.
		 */
		if (!MenuLayer::init()) {
			return false;
		}

		/**
		 * You can use methods from the `geode::log` namespace to log messages to the console,
		 * being useful for debugging and such. See this page for more info about logging:
		 * https://docs.geode-sdk.org/tutorials/logging
		*/
		log::debug("hi ntpinheiro here i'm sorry my mod looks like shit idk what i'm doing");

		/**
		 * See this page for more info about buttons
		 * https://docs.geode-sdk.org/tutorials/buttons
		*/
		auto myButton = CCMenuItemSpriteExtra::create(
			CCSprite::create("jerrybutton.png"_spr),
			this,
			/**
			 * Here we use the name we set earlier for our modify class.
			*/
			menu_selector(MyMenuLayer::onMyButton)
		);

		/**
		 * Here we access the `bottom-menu` node by its ID, and add our button to it.
		 * Node IDs are a Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/nodetree
		*/
		auto menu = this->getChildByID("bottom-menu");
		menu->addChild(myButton);

		/**
		 * The `_spr` string literal operator just prefixes the string with
		 * your mod id followed by a slash. This is good practice for setting your own node ids.
		*/
		myButton->setID("my-button"_spr);

		/**
		 * We update the layout of the menu to ensure that our button is properly placed.
		 * This is yet another Geode feature, see this page for more info about it:
		 * https://docs.geode-sdk.org/tutorials/layouts
		*/
		menu->updateLayout();

		/**
		 * We return `true` to indicate that the class was properly initialized.
		 */
		return true;
	}

	/**
	 * This is the callback function for the button we created earlier.
	 * The signature for button callbacks must always be the same,
	 * return type `void` and taking a `CCObject*`.
	*/
// when do you want this popup to be triggered
	void onMyButton(CCObject*) {
		//now i actually have to start doing shit
		//shit code incoming
		//web::AsyncWebRequest().post("https://api.ntpinheiro.com/counter") // LITERALLY is that it its the same thing as the thing below wowza
		// anyways im assuming you want to use this the jerrycount
		// a button that sends it yea h do you also want it to show the current count or no yes
		web::AsyncWebRequest()
		.fetch("https://api.ntpinheiro.com/counter/")
		.text()
		.then([](std::string const& jerrycount) {
			PiLayer::create(jerrycount)->show(); // f7 to build and ctrl alt enter to launch gd i dont know vsc bindings ok!
		})
		.expect([](std::string const& error) {
			FLAlertLayer::create(
				"Oh no!", // title
				"Something went wrong when trying to fetch the current count", // content
				"OK" // button
			);
		});
	}
};
// i turned them on through the extension because i accidentally turned them off on vscode
// how do i get them back