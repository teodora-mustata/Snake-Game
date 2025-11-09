#include "GameFactory.h"
#include "GameAPI.h"

IGameAPI* createGameAPI() {
    return new GameAPI();
}
