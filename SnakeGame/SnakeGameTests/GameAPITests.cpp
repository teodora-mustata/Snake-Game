#include "pch.h"
#include "GameAPI.h"
#include "MockObserverMap.h"

TEST(GameAPITests, ElapsedTimeIncreases) {
    GameAPI api;
    api.initialize();

    api.update(1.25);
    EXPECT_NEAR(api.getElapsedTime(), 1.25, 0.01);
}

TEST(GameAPITests, AttachMapObserverWorks) {
    GameAPI api;
    MockObserverMap obs;

    EXPECT_NO_THROW(api.attachMapObserver(&obs));
}

TEST(GameAPITests, APIProvidesSnakeAndFruits) {
    GameAPI api;
    api.initialize();

    auto snake = api.getSnakeBody();
    EXPECT_FALSE(snake.empty());

    auto fruits = api.getFruits();
    EXPECT_FALSE(fruits.empty());
}
