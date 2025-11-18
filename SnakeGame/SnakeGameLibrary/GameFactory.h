
#pragma once
#include <memory>
#include "IGameAPI.h"

std::unique_ptr<IGameAPI> createGameAPI();
