#include "AssetManager.hpp"
#include "CatView.hpp"
#include "DomesticCat.hpp"
#include "Exceptions.hpp"
#include "FatCat.hpp"
#include "Food.hpp"
#include "GameState.hpp"
#include "GameUtils.hpp"
#include "Renderer.hpp"
#include "StrayCat.hpp"

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <vector>

namespace {

const std::size_t MAX_CATS = 6;

void syncViews(const GameState& game, std::vector<CatView>& views) {
    const auto& cats = game.getCats();
    while (views.size() < cats.size())
        views.emplace_back(cats[views.size()], static_cast<float>(views.size()) * 1.7f);
}

void feedSelected(GameState& game, std::vector<CatView>& views, AssetManager& assets,
                  std::vector<std::pair<float, std::string>>& pendingSounds,
                  int foodChoice, std::size_t selected) {
    if (selected >= views.size()) return;

    std::shared_ptr<Food> food;                 
    std::string eatSound, phrase;
    if (foodChoice == 1)      { food = Food::createFish();    eatSound = "munch";  phrase = "Yum! Fish!"; }
    else if (foodChoice == 2) { food = Food::createDryFood(); eatSound = "crunch"; phrase = "Crunchy!"; }
    else                      { food = Food::createMilk();    eatSound = "splash"; phrase = "Mmm, milk!"; }

    FeedResult result = game.feedCat(static_cast<int>(selected), food);
    assets.play(eatSound);

    if (result == FeedResult::Fed) {
        views[selected].react(Expression::Eating, 0.9f, Expression::Happy, 1.6f);
        views[selected].say(phrase, 1.8f);
        pendingSounds.emplace_back(0.9f, "happy");
    } else if (result == FeedResult::Overfed) {
        views[selected].react(Expression::Overfed, 2.2f, Expression::Idle, 0.f);
        views[selected].say("Too full!!", 2.2f);
        pendingSounds.emplace_back(0.3f, "buzz");
    }
}

void addNewCat(GameState& game, std::vector<CatView>& views, AssetManager& assets, std::size_t& selected) {
    static const char* names[MAX_CATS] = {"Mimi", "Chonky", "Ghost", "Luna", "Oreo", "Pixel"};
    std::size_t n = game.getCats().size();
    if (n >= MAX_CATS) {
        assets.play("buzz");
        return;
    }
    std::string name = names[n];
    if (n % 3 == 0)      addGenericCat<DomesticCat>(game, name, 2, 40);
    else if (n % 3 == 1) addGenericCat<FatCat>(game, name, 4, 40);
    else                 addGenericCat<StrayCat<std::string>>(game, name, 1, 40);

    syncViews(game, views);
    selected = views.size() - 1;
    views[selected].react(Expression::Happy, 1.0f, Expression::Happy, 0.f);
    views[selected].say("Hello!", 1.5f);
    assets.play("pop");
}

} 

int main() {
    try {
        AssetManager assets(ASSET_DIR);

        sf::RenderWindow window(sf::VideoMode({Renderer::WIDTH, Renderer::HEIGHT}), "Cat Feeding Game",
                                sf::Style::Titlebar | sf::Style::Close);
        window.setFramerateLimit(60);
        Renderer renderer(window, assets);

        GameState& game = GameState::getInstance();
        addGenericCat<DomesticCat>(game, "Mimi", 3, 80);
        addGenericCat<FatCat>(game, "Chonky", 5, 60);
        addGenericCat<StrayCat<std::string>>(game, "Ghost", 2, 40);

        std::vector<CatView> views;
        syncViews(game, views);
        std::size_t selected = 0;
        std::vector<std::pair<float, std::string>> pendingSounds;   

        sf::Clock clock;
        float totalTime = 0.f;

        while (window.isOpen()) {
            while (const std::optional<sf::Event> event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                } else if (const auto* click = event->getIf<sf::Event::MouseButtonPressed>()) {
                    selected = Renderer::slotAt(static_cast<float>(click->position.x), views.size());
                } else if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {
                    switch (key->code) {
                        case sf::Keyboard::Key::Escape: window.close(); break;
                        case sf::Keyboard::Key::Left:
                            if (!views.empty()) selected = (selected + views.size() - 1) % views.size();
                            break;
                        case sf::Keyboard::Key::Right:
                            if (!views.empty()) selected = (selected + 1) % views.size();
                            break;
                        case sf::Keyboard::Key::Num1: case sf::Keyboard::Key::Numpad1:
                            feedSelected(game, views, assets, pendingSounds, 1, selected); break;
                        case sf::Keyboard::Key::Num2: case sf::Keyboard::Key::Numpad2:
                            feedSelected(game, views, assets, pendingSounds, 2, selected); break;
                        case sf::Keyboard::Key::Num3: case sf::Keyboard::Key::Numpad3:
                            feedSelected(game, views, assets, pendingSounds, 3, selected); break;
                        case sf::Keyboard::Key::S:
                            if (selected < views.size()) {
                                game.makeCatSound(selected);        
                                assets.play("meow");
                                views[selected].react(Expression::Happy, 1.0f, Expression::Happy, 0.f);
                                views[selected].say("Meow!", 1.2f);
                            }
                            break;
                        case sf::Keyboard::Key::N: addNewCat(game, views, assets, selected); break;
                        default: break;
                    }
                }
            }

            float dt = std::min(clock.restart().asSeconds(), 0.05f);
            totalTime += dt;
            game.tick(dt);                                   
            bool hungryCry = false;
            for (CatView& v : views) {
                v.update(dt);
                if (v.takeHungryAlert()) hungryCry = true;
            }
            if (hungryCry) assets.play("meow");

            for (auto& p : pendingSounds) p.first -= dt;
            for (auto it = pendingSounds.begin(); it != pendingSounds.end();) {
                if (it->first <= 0.f) {
                    assets.play(it->second);
                    it = pendingSounds.erase(it);
                } else {
                    ++it;
                }
            }

            window.clear();
            renderer.draw(views, selected, totalTime, game.getScore());
            window.display();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
