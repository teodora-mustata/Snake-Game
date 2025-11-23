#include "pch.h"
#include <gtest/gtest.h>
#include "Map.h"
#include "MockObserverMap.h"

TEST(MapTests, FruitSpawnsInsideBounds) {
    Map map(10, 10);
    map.spawnFruit(3, 4);
    auto fruits = map.getFruits();

    ASSERT_FALSE(fruits.empty());
    EXPECT_EQ(fruits.front(), std::make_pair(3, 4));
}

TEST(MapTests, RemoveFruitWorks) {
    Map map(10, 10);
    map.spawnFruit(3, 3);
    map.removeFruit(3, 3);

    EXPECT_FALSE(map.hasFruit(3, 3));
}

TEST(MapTests, MapNotifiesFruitRemoved) {
    Map map(10, 10);
    MockObserverMap obs;
    map.attach(&obs);

    map.spawnFruit(3, 3);

    EXPECT_CALL(obs, update(MapEvent::FruitRemoved, 3, 3)).Times(1);
    map.removeFruit(3, 3);
}
TEST(MapTests, IsInsideWorks) {
    Map map(10, 10);
    EXPECT_TRUE(map.isInside(0, 0));
    EXPECT_FALSE(map.isInside(-1, 5));
    EXPECT_FALSE(map.isInside(20, 5));
}
TEST(MapTests, GetCenterPositionWorks) {
	Map map(10, 10);
	auto center = map.getCenterPosition();
	EXPECT_EQ(center, std::make_pair(5, 5));
}
