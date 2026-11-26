#include "FeedingStrategy.hpp"  

int NormalFeeding::getFullnessIncrease() const {
    return 20;  // Standard fullness gain
}

int FatCatFeeding::getFullnessIncrease() const {
    return 30;  // Fat cats get more fullness when fed
}

int NormalFeeding::getHungerPerTick() const {
    return 1;
}

int FatCatFeeding::getHungerPerTick() const {
    return 2;
}
