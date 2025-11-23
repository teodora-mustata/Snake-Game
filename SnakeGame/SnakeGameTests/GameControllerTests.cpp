#include "pch.h"
#include <gtest/gtest.h>

#include "GameController.h"
#include "Map.h"
#include "Snake.h"
#include "Score.h"

TEST(GameControllerTests, SnakeMovesWhenUpdated) {
    Map map(20, 20);
    Snake snake(5, 5);
    Score score;

    GameController controller(map, snake, score);

    controller.initialize();
    snake.setDirection(Direction::Right);

    std::pair<int, int> oldHead = snake.getBody().front();

    controller.update(0.5);

    EXPECT_NE(oldHead, snake.getBody().front());
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
TEST(GameControllerTests, FruitSpawnsOverTime) {
    Map map(20, 20);
    Snake snake(10, 10);
    Score score;
    GameController controller(map, snake, score);

    controller.initialize();

    auto f = map.getFruits().front();
    map.removeFruit(f.first, f.second);

    int before = map.getFruits().size();
    EXPECT_EQ(before, 0);

    controller.update(12.0); 

    EXPECT_EQ(map.getFruits().size(), 1);
}
TEST(GameControllerTests, DifficultyIncreases) {
    Map map(20, 20);
    Snake snake(10, 10);
    Score score;
    GameController controller(map, snake, score);

   
    controller.update(35.0);

    int before = map.getFruits().size();
    controller.update(1.5); 

    EXPECT_GE(map.getFruits().size(), before);
}