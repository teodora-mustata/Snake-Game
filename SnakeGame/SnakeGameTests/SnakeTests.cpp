#include "pch.h"
#include <gtest/gtest.h>
#include "Snake.h"
#include "Map.h"
#include "MockObserverSnake.h"

TEST(SnakeLogicTests, SnakeStartsAlive) {
    Snake snake(5, 5);
    EXPECT_TRUE(snake.isAlive());
}

TEST(SnakeLogicTests, SnakeDoesNotReverseDirection) {
    Map map(10, 10);
    Snake snake(5, 5);

    snake.setDirection(Direction::Right);
    snake.setDirection(Direction::Left);

   
    snake.move(map);
    EXPECT_EQ(snake.getBody().front(), std::make_pair(6, 5));
}

TEST(SnakeLogicTests, SnakeGrowsWhenEatingFruit) {
    Map map(10, 10);
    Snake snake(5, 5);

    map.spawnFruit(6, 5);
    int before = snake.getBody().size();

    snake.setDirection(Direction::Right);
    snake.move(map);

    EXPECT_EQ(snake.getBody().size(), before + 1);
}

TEST(SnakeLogicTests, SnakeHitsSelf) {
    Map map(10, 10);
    Snake snake(5, 5);

    map.spawnFruit(6, 5);  
    snake.setDirection(Direction::Right);
    snake.move(map);

    map.spawnFruit(6, 6);  
    snake.setDirection(Direction::Down);
    snake.move(map);

    map.spawnFruit(5, 6); 
    snake.setDirection(Direction::Left);
    snake.move(map);

    snake.setDirection(Direction::Up);
    snake.move(map);

    EXPECT_FALSE(snake.isAlive());
}

TEST(SnakeLogicTests, SnakeNotifiesEatFruit) {
    Map map(10, 10);
    Snake snake(5, 5);
    MockObserverSnake obs;

    snake.attach(&obs);
    map.spawnFruit(6, 5);

    EXPECT_CALL(obs, update(SnakeEvent::Move)).Times(1);
    EXPECT_CALL(obs, update(SnakeEvent::AteFruit)).Times(1);

    snake.setDirection(Direction::Right);
    snake.move(map);
}

TEST(SnakeLogicTests, SnakeNotifiesHitWall) {
    Map map(3, 3);
    Snake snake(2, 1);
    MockObserverSnake obs;

    snake.attach(&obs);
    snake.setDirection(Direction::Right);

    EXPECT_CALL(obs, update(SnakeEvent::HitWall)).Times(1);

    snake.move(map);
}