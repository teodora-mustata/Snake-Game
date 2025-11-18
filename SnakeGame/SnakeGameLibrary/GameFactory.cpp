

#include "GameFactory.h"
#include "GameAPI.h"

std::unique_ptr<IGameAPI> createGameAPI() {
    return std::make_unique<GameAPI>();
}
