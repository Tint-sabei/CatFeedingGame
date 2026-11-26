#include "GameState.hpp"            
#include "Cat.hpp"                 
#include "FatCat.hpp"               
#include "Exceptions.hpp"           
#include <algorithm>
#include <iostream>                 

#include "FeedingStrategy.hpp"      
#include "GameUtils.hpp"            

namespace {
std::unique_ptr<FeedingStrategy> chooseStrategy(const Cat& cat) {
    if (dynamic_cast<const FatCat*>(&cat))
        return std::make_unique<FatCatFeeding>();      // FatCat gets bonus
    return std::make_unique<NormalFeeding>();          // Normal feeding
}
}

GameState::GameState() = default;

GameState& GameState::getInstance() {
    static GameState instance;     
    return instance;
}

void GameState::addCat(const std::shared_ptr<Cat>& cat) {
    cats.push_back(cat);           
}

void GameState::showCats() const {
    std::cout << "\n=== All Cats ===\n";
    for (size_t i = 0; i < cats.size(); ++i) {
        std::cout << "[" << i << "] "                         
                  << cats[i]->getType() << " - "              
                  << cats[i]->getName() << ", Age: "          
                  << cats[i]->getAge() << ", Fullness: "      
                  << cats[i]->getFullnessLevel() << "\n";
    }
}

void GameState::showTotalCats() const {
    std::cout << "\nTotal Cats: " << Cat::getCatCount() << "\n";
}

void GameState::makeCatSound(size_t index) const {
    if (index < cats.size())               
        cats[index]->sound();              
    else
        std::cout << "Invalid Cat Index.\n"; 
}

FeedResult GameState::feedCat(int index, const std::shared_ptr<Food>& food) {
    if (index < 0 || index >= static_cast<int>(cats.size())) {
        std::cout << "Invalid Cat index.\n";
        return FeedResult::InvalidIndex;
    }

    try {
        std::cout << "\nFeeding " << cats[index]->getName() << " with food...\n";

        displayInfo(*food);  

        std::unique_ptr<FeedingStrategy> strategy = chooseStrategy(*cats[index]);

        cats[index]->update(strategy->getFullnessIncrease());

        std::cout << "Fullness after feeding: " << cats[index]->getFullnessLevel() << "\n";
        score += 10;
        return FeedResult::Fed;

    } catch (const FullnessTooHighException& e) {
        std::cerr << "Error: " << e.what() << "\n";
        score = std::max(0, score - 5);
        return FeedResult::Overfed;
    }
}

const std::vector<std::shared_ptr<Cat>>& GameState::getCats() const {
    return cats;
}

void GameState::tick(float seconds) {
    hungerTimer += seconds;
    while (hungerTimer >= HUNGER_INTERVAL) {
        hungerTimer -= HUNGER_INTERVAL;
        for (const auto& cat : cats) {
            try {
                cat->update(-chooseStrategy(*cat)->getHungerPerTick());
            } catch (const FullnessTooHighException&) {
                // cannot happen when fullness goes down; 
            }
        }
    }
}

int GameState::getScore() const {
    return score;
}
