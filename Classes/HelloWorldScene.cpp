#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World!!!", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("character.jpg");
    sprite->setTag(1);

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/5, visibleSize.height/2));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    sprite->runAction( MoveTo::create(2.0f, Point(visibleSize.width/5, sprite->getContentSize().height/2)) );

    //  Create a "one by one" touch event listener
    // (processes one touch at a time)
    direction = false;  // TODO: enum

    // イベント
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);

    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
    printf("onTouchBegan\n");

    Size visibleSize = Director::getInstance()->getVisibleSize();
    auto sprite = this->getChildByTag(1);

    auto actionManager = Director::getInstance()->getActionManager();
    bool is_lock = actionManager->getNumberOfRunningActionsInTarget(sprite) ? true : false;

    if (!is_lock) {
        if (direction) {
            // Move down
            printf("%f\t%f\n", visibleSize.width/5, visibleSize.height);
            sprite->runAction( MoveTo::create(2.0f, Point(visibleSize.width/5, sprite->getContentSize().height/2)) );
            direction = false;
        } else {
            // Move up
            printf("%f\t%f\n", visibleSize.width/5, visibleSize.height);
            sprite->runAction( MoveTo::create(2.0f, Point(visibleSize.width/5, visibleSize.height - sprite->getContentSize().height/2)) );
            direction = true;
        }
    }

    return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
    printf("onTouchMoved\n");
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    printf("onTouchEnded\n");
}
