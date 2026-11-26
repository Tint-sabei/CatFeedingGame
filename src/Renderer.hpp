#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "AssetManager.hpp"
#include "CatView.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class Renderer {
private:
    sf::RenderWindow& window;
    const AssetManager& assets;
    sf::VertexArray background;

    void drawEllipse(float cx, float cy, float rx, float ry, const sf::Color& color);
    void drawText(const std::string& str, unsigned size, float x, float y,
                  const sf::Color& color, bool centered, bool bold);
    void drawIcon(const std::string& name, float x, float y, float scale, float alpha = 255.f);
    void drawCat(const CatView& view, float cx, float scale, bool selected);
    void drawBubble(const std::string& text, float cx, float topY);
    void drawBar(float cx, float y, int fullness);

public:
    static constexpr unsigned WIDTH = 900;
    static constexpr unsigned HEIGHT = 600;

    Renderer(sf::RenderWindow& win, const AssetManager& assetManager);

    void draw(const std::vector<CatView>& views, std::size_t selected, float totalTime, int score);

    static std::size_t slotAt(float x, std::size_t count);
};

#endif // RENDERER_HPP
