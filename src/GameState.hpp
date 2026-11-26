#ifndef GAMESTATE_HPP           
#define GAMESTATE_HPP

#include "Cat.hpp"              
#include "Food.hpp"             
#include <vector>               
#include <memory>               

enum class FeedResult { InvalidIndex, Fed, Overfed };

class GameState {
private:
    std::vector<std::shared_ptr<Cat>> cats;  
    float hungerTimer = 0.f;                 
    int score = 0;

    GameState();  

public:
    GameState(const GameState&) = delete;
    GameState& operator=(const GameState&) = delete;

    static GameState& getInstance();

    void addCat(const std::shared_ptr<Cat>& cat);

    void showCats() const;

    void showTotalCats() const;

    void makeCatSound(size_t index) const;

    FeedResult feedCat(int index, const std::shared_ptr<Food>& food);

    const std::vector<std::shared_ptr<Cat>>& getCats() const;

    void tick(float seconds);

    int getScore() const;

    static constexpr float HUNGER_INTERVAL = 1.5f;
};

#endif // GAMESTATE_HPP         
