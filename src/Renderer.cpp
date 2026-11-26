#include "Renderer.hpp"
#include "Cat.hpp"
#include <algorithm>
#include <cmath>
#include <cstdint>

namespace {
const float WIN_W = 900.f;
const float GROUND_Y = 420.f;       
const float SIDE_MARGIN = 20.f;
const float HEAD_HEIGHT = 352.f;    
const float ORIGIN_X = 300.f;       
const float ORIGIN_Y = 400.f;

float slotWidth(std::size_t count) {
    return (WIN_W - 2.f * SIDE_MARGIN) / static_cast<float>(count);
}
}

Renderer::Renderer(sf::RenderWindow& win, const AssetManager& assetManager)
    : window(win), assets(assetManager), background(sf::PrimitiveType::TriangleFan, 4) {
    const sf::Color top(191, 227, 251), bottom(251, 207, 232);
    background[0].position = sf::Vector2f(0.f, 0.f);
    background[1].position = sf::Vector2f(static_cast<float>(WIDTH), 0.f);
    background[2].position = sf::Vector2f(static_cast<float>(WIDTH), static_cast<float>(HEIGHT));
    background[3].position = sf::Vector2f(0.f, static_cast<float>(HEIGHT));
    background[0].color = top;
    background[1].color = top;
    background[2].color = bottom;
    background[3].color = bottom;
}

std::size_t Renderer::slotAt(float x, std::size_t count) {
    if (count == 0) return 0;
    float index = (x - SIDE_MARGIN) / slotWidth(count);
    if (index < 0.f) index = 0.f;
    std::size_t result = static_cast<std::size_t>(index);
    return std::min(result, count - 1);
}

void Renderer::drawEllipse(float cx, float cy, float rx, float ry, const sf::Color& color) {
    sf::CircleShape shape(1.f, 48);
    shape.setOrigin({1.f, 1.f});
    shape.setScale({rx, ry});
    shape.setPosition({cx, cy});
    shape.setFillColor(color);
    window.draw(shape);
}

void Renderer::drawText(const std::string& str, unsigned size, float x, float y,
                        const sf::Color& color, bool centered, bool bold) {
    sf::Text text(assets.getFont(), str, size);
    text.setFillColor(color);
    if (bold) text.setStyle(sf::Text::Bold);
    sf::FloatRect b = text.getLocalBounds();
    text.setOrigin({centered ? b.position.x + b.size.x / 2.f : b.position.x, b.position.y});
    text.setPosition({x, y});
    window.draw(text);
}

void Renderer::drawIcon(const std::string& name, float x, float y, float scale, float alpha) {
    const sf::Texture& tex = assets.texture(name);
    sf::Sprite sprite(tex);
    sprite.setOrigin({static_cast<float>(tex.getSize().x) / 2.f, static_cast<float>(tex.getSize().y) / 2.f});
    sprite.setPosition({x, y});
    sprite.setScale({scale, scale});
    sprite.setColor(sf::Color(255, 255, 255, static_cast<std::uint8_t>(alpha)));
    window.draw(sprite);
}

void Renderer::drawBar(float cx, float y, int fullness) {
    const float width = 110.f, height = 12.f;
    float fraction = std::min(1.f, std::max(0.f, static_cast<float>(fullness) / 100.f));

    sf::RectangleShape back(sf::Vector2f(width, height));
    back.setPosition({cx - width / 2.f, y});
    back.setFillColor(sf::Color(229, 231, 235));
    window.draw(back);

    sf::Color color(34, 197, 94);                                  
    if (fullness < CatView::HUNGRY_BELOW) color = sf::Color(239, 68, 68);   
    else if (fullness < 70) color = sf::Color(250, 204, 21);       
    sf::RectangleShape fill(sf::Vector2f(std::max(4.f, width * fraction), height));
    fill.setPosition({cx - width / 2.f, y});
    fill.setFillColor(color);
    window.draw(fill);
}

void Renderer::drawBubble(const std::string& text, float cx, float topY) {
    sf::Text probe(assets.getFont(), text, 18);
    probe.setStyle(sf::Text::Bold);
    sf::FloatRect b = probe.getLocalBounds();

    float w = b.size.x + 28.f, h = b.size.y + 20.f;
    float x = cx - w / 2.f, y = std::max(40.f, topY);

    sf::RectangleShape box(sf::Vector2f(w, h));
    box.setPosition({x, y});
    box.setFillColor(sf::Color::White);
    box.setOutlineColor(sf::Color(236, 72, 153));
    box.setOutlineThickness(2.f);
    window.draw(box);

    sf::ConvexShape tail(3);
    tail.setPoint(0, sf::Vector2f(cx - 9.f, y + h));
    tail.setPoint(1, sf::Vector2f(cx + 9.f, y + h));
    tail.setPoint(2, sf::Vector2f(cx, y + h + 14.f));
    tail.setFillColor(sf::Color::White);
    window.draw(tail);

    drawText(text, 18, cx, y + 8.f, sf::Color(190, 24, 93), true, true);
}

void Renderer::drawCat(const CatView& view, float cx, float scale, bool selected) {
    const Cat& cat = view.getCat();

    // shadow
    drawEllipse(cx, GROUND_Y + 4.f, 95.f * scale, 14.f * scale, sf::Color(196, 181, 253, 200));

    // the cat picture 
    const sf::Texture& tex = assets.texture(view.textureName());
    sf::Sprite sprite(tex);
    sprite.setOrigin({ORIGIN_X, ORIGIN_Y});
    sprite.setPosition({cx, GROUND_Y + view.bounceOffset() * scale});
    sprite.setScale({scale, scale * view.squash()});
    sprite.setRotation(sf::degrees(view.swayDegrees()));
    window.draw(sprite);

    // name, type, fullness bar 
    if (selected) {
        sf::RectangleShape frame(sf::Vector2f(160.f, 72.f));
        frame.setPosition({cx - 80.f, GROUND_Y + 20.f});
        frame.setFillColor(sf::Color(255, 255, 255, 120));
        frame.setOutlineColor(sf::Color(250, 204, 21));
        frame.setOutlineThickness(3.f);
        window.draw(frame);
        drawIcon("ui/heart", cx - 70.f, GROUND_Y + 36.f, 0.3f);
    }
    drawText(cat.getName(), 18, cx, GROUND_Y + 26.f,
             selected ? sf::Color(190, 24, 93) : sf::Color(55, 65, 81), true, true);
    drawText(cat.getType() + ", age " + std::to_string(cat.getAge()), 12, cx, GROUND_Y + 49.f,
             sf::Color(75, 85, 99), true, false);
    drawBar(cx, GROUND_Y + 68.f, cat.getFullnessLevel());

    if (view.hasBubble())
        drawBubble(view.bubbleText(), cx, GROUND_Y - HEAD_HEIGHT * scale - 50.f);
}

void Renderer::draw(const std::vector<CatView>& views, std::size_t selected, float totalTime, int score) {
    window.draw(background);

    // twinkling sparkles
    const float sx[] = {80.f, 230.f, 420.f, 610.f, 790.f, 520.f};
    const float sy[] = {70.f, 150.f, 60.f, 120.f, 80.f, 190.f};
    for (int i = 0; i < 6; ++i) {
        float s = 0.5f + 0.15f * std::sin(totalTime * 2.f + static_cast<float>(i));
        drawIcon("ui/sparkle", sx[i], sy[i], s, 220.f);
    }

    // floor
    drawEllipse(WIN_W / 2.f, GROUND_Y + 30.f, 440.f, 80.f, sf::Color(233, 213, 255));

    // cats
    std::size_t count = views.size();
    if (count > 0) {
        float slot = slotWidth(count);
        float scale = std::min(0.8f, slot / 330.f);
        for (std::size_t i = 0; i < count; ++i) {
            float cx = SIDE_MARGIN + slot * (static_cast<float>(i) + 0.5f);
            drawCat(views[i], cx, scale, i == selected);
        }
    }

    // top-left counter
    drawText("Cats: " + std::to_string(Cat::getCatCount()) + "     Score: " + std::to_string(score),
             22, 20.f, 14.f, sf::Color(31, 41, 55), false, true);
    drawText("Keep every cat fed - hungry cats cry!", 14, WIN_W - 20.f - 300.f, 20.f, sf::Color(75, 85, 99), false, false);

    // food buttons
    const char* icons[] = {"ui/fish", "ui/dry", "ui/milk"};
    const char* labels[] = {"[1] Fish", "[2] Dry food", "[3] Milk"};
    const float xs[] = {110.f, 380.f, 650.f};
    for (int i = 0; i < 3; ++i) {
        drawIcon(icons[i], xs[i], 548.f, 0.4f);
        drawText(labels[i], 16, xs[i] + 48.f, 538.f, sf::Color(31, 41, 55), false, true);
    }

    // help line
    drawText("Left/Right or click: choose cat    S: meow    N: new cat    Esc: quit", 14,
             WIN_W / 2.f, 578.f, sf::Color(75, 85, 99), true, false);
}
