#include <Geode/Geode.hpp>
#include <Geode/utils/random.hpp>

using namespace geode::prelude;
using namespace geode::utils::random;

#include <Geode/modify/GJBaseGameLayer.hpp>
class $modify(GJBaseGameLayerMod, GJBaseGameLayer) {
	void handleButton(bool down, int button, bool isPlayer1) {
		GJBaseGameLayer::handleButton(down, button, isPlayer1);

		if (!down)
			return;
		if (!Mod::get()->getSettingValue<bool>("enabled"))
			return;

		Generator rng;
		int chance = Mod::get()->getSettingValue<int>("chance");
		if (rng.generate(1, 101) <= chance)
			createImage();
	}

	void createImage() {
		FMODAudioEngine::sharedEngine()->playEffect("jumpscare-sound.mp3"_spr);
		Generator rng;

		std::string name = "neru-jumpscare-" + std::to_string(rng.generate(1,6)) + ".png";
		name = Mod::get()->expandSpriteName(name.c_str()).c_str();
		auto jumpscare = CCSprite::create(name.c_str());

		auto winSize = CCDirector::get()->getWinSize();
		jumpscare->setPosition({winSize.width / 2, winSize.height / 2});
		jumpscare->setAnchorPoint({0.5f, 0.5f});
		jumpscare->setScaleX(winSize.width / jumpscare->getContentSize().width);
		jumpscare->setScaleY(winSize.height / jumpscare->getContentSize().height);
		CCDirector::get()->getRunningScene()->addChild(jumpscare);

		auto fadeOut = CCFadeOut::create(0.5);
		auto remove = CCRemoveSelf::create();
		jumpscare->runAction(CCSequence::create(fadeOut, remove, nullptr));
	}
};