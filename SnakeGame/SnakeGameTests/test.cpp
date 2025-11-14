#include "pch.h"
#include "Map.h"
#include "Snake.h"
#include "Score.h"
#include "GameController.h"
#include "GameAPI.h"

TEST(SnakeLogicTests, SnakeStartsAlive) {
    Snake snake(5, 5);
    EXPECT_TRUE(snake.isAlive());
}

TEST(SnakeLogicTests, SnakeMovesCorrectly) {
    Map map(10, 10);
    Snake snake(5, 5);
    snake.setDirection(Direction::Right);
    snake.move(map);

    auto body = snake.getBody();
    EXPECT_EQ(body.front(), std::make_pair(6, 5));
}

TEST(SnakeLogicTests, SnakeDiesWhenHitsWall) {
    Map map(5, 5);
    Snake snake(4, 2);
    snake.setDirection(Direction::Right);
    snake.move(map);
    EXPECT_FALSE(snake.isAlive());
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

TEST(MapTests, FruitSpawnsInsideBounds) {
    Map map(10, 10);
    map.spawnFruit(3, 4);
    auto fruits = map.getFruits();

    ASSERT_FALSE(fruits.empty());
    EXPECT_EQ(fruits.front(), std::make_pair(3, 4));
}