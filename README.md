# 🐍 Snake Game (C++ & Qt)

Snake game implemented in **C++** using the **Qt Framework**, structured into multiple logical modules and following clean architecture principles, using Observer and Factory design patterns.

---

## 🎮 Features - Core Gameplay

- Smooth automatic snake movement
- Player controls using W/A/S/D
- Random fruit spawning at timed intervals
- Eating fruits increases snake length
- Difficulty increasing the more you play, with faster snake speed and more fruits appearing
- Collecting fruits grants points
- A leaderboard with the best scores
- Game over on:
  - Hitting a wall  
  - Hitting its own body  

---

## 🧰 Technologies Used

- **C++17**
- **Qt 6.10**
- **GTest/GMock** for unit testing
- OOP Principles (Encapsulation, Responsibility Separation)
- Observer & Factory design patterns

---

## 🧠 Architecture & Design Patterns

The project uses two main design patterns to keep the code clean, modular, and easy to extend.

### 🔔 Observer Pattern

Used for communication between the game logic and the UI, without creating direct dependencies.

Snake notifies its observers when it moves, eats a fruit, or dies.

Map notifies observers when fruits appear or are removed.

✔ Keeps UI independent from game logic

✔ Easy to add new observers

### 🏭 Factory Pattern

A small factory centralizes the creation of main game object (IGameAPI).

✔ Avoids duplicate initialization code

✔ Makes testing easier
