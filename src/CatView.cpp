#include "CatView.hpp"
#include <algorithm>
#include <cmath>
#include <utility>

namespace {
const float PI = 3.14159265f;
}

CatView::CatView(std::shared_ptr<Cat> catPtr, float phaseOffset)
    : cat(std::move(catPtr)), phase(phaseOffset) {}

Expression CatView::baseExpression() const {
    int fullness = cat->getFullnessLevel();
    if (fullness >= SLEEPY_FROM) return Expression::Full;
    if (fullness < HUNGRY_BELOW) return Expression::Hungry;
    return Expression::Idle;
}

void CatView::update(float dt) {
    time += dt;
    bounceT = std::max(0.f, bounceT - dt / 0.7f);
    if (bubbleTimer > 0.f) bubbleTimer -= dt;

    bool hungry = cat->getFullnessLevel() < HUNGRY_BELOW;
    if (hungry) {
        cryTimer -= dt;
        if (!wasHungry || cryTimer <= 0.f) {
            cryTimer = 9.f;
            alertPending = true;
            if (!hasBubble()) say("I'm hungry!", 2.5f);
        }
    }
    wasHungry = hungry;

    if (expressionTimer > 0.f) {
        expressionTimer -= dt;
        if (expressionTimer <= 0.f && hasFollowUp) {
            current = followUp;
            expressionTimer = followUpSeconds;
            hasFollowUp = false;
        }
    }
}

void CatView::react(Expression first, float firstSeconds, Expression then, float thenSeconds) {
    current = first;
    expressionTimer = firstSeconds;
    followUp = then;
    followUpSeconds = thenSeconds;
    hasFollowUp = thenSeconds > 0.f;
    bounceT = 1.f;
}

void CatView::say(const std::string& text, float seconds) {
    bubble = text;
    bubbleTimer = seconds;
}

bool CatView::takeHungryAlert() {
    bool result = alertPending;
    alertPending = false;
    return result;
}

const Cat& CatView::getCat() const { return *cat; }

Expression CatView::getExpression() const {
    return expressionTimer > 0.f ? current : baseExpression();
}

std::string CatView::textureName() const {
    const std::string type = cat->getType();
    std::string key = "stray";
    if (type == "Domestic Cat") key = "domestic";
    else if (type == "Fat Cat") key = "fat";

    std::string mood = "idle";
    switch (getExpression()) {
        case Expression::Idle:    mood = "idle";  break;
        case Expression::Happy:   mood = "happy"; break;
        case Expression::Eating:  mood = "eat";   break;
        case Expression::Full:    mood = "full";  break;
        case Expression::Overfed: mood = "over";  break;
        case Expression::Hungry:  mood = "hungry"; break;
    }
    return "cats/" + key + "_" + mood;
}

float CatView::swayDegrees() const { return 2.f * std::sin(time * 2.f + phase); }

float CatView::squash() const { return 1.f + 0.015f * std::sin(time * 3.f + phase); }

float CatView::bounceOffset() const {
    return -std::fabs(std::sin(bounceT * 3.f * PI)) * bounceT * 35.f;
}

bool CatView::hasBubble() const { return bubbleTimer > 0.f; }

const std::string& CatView::bubbleText() const { return bubble; }
