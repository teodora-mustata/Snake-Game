#include "pch.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Map.h"
#include "Score.h"
#include "Snake.h"
#include "MockObserverMap.h"
#include "MockObserverSnake.h"

TEST(ObserverTests, MapNotifiesFruitSpawn) {
    Map map(10, 10);
    MockObserverMap obs;

    map.attach(&obs);

    EXPECT_CALL(obs, update(MapEvent::FruitSpawned, 3, 4)).Times(1);

    map.spawnFruit(3, 4);
}

TEST(ObserverTests, SnakeNotifiesMovement) {
    Map map(10, 10);
    Snake snake(5, 5);

    MockObserverSnake obs;
    snake.attach(&obs);

    EXPECT_CALL(obs, update(SnakeEvent::Move)).Times(1);

    snake.setDirection(Direction::Right);
    snake.move(map);
}
TEST(ScoreTests, ScoreIncreasesWhenEatingFruit) {
    Map map(10, 10);
    Snake snake(5, 5);
    Score score;
    snake.attach(&score);

    map.spawnFruit(6, 5);
    snake.setDirection(Direction::Right);
    snake.move(map);

    EXPECT_EQ(score.getPoints(), 10);
}