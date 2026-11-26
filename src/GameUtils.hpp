#ifndef GAME_UTILS_HPP          
#define GAME_UTILS_HPP

#include "GameState.hpp"        
#include <memory>               

template<typename T>
void displayInfo(const T& item) {
    item.treat();               
    item.eat();                 
}

template<typename CatType>
void addGenericCat(GameState& game, const std::string& name, int age, int fullness) {
    game.addCat(std::make_shared<CatType>(name, age, fullness));  
}

#endif // GAME_UTILS_HPP        
