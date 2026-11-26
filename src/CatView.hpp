#ifndef CAT_VIEW_HPP
#define CAT_VIEW_HPP

#include "Cat.hpp"
#include <memory>
#include <string>

enum class Expression { Idle, Happy, Eating, Full, Overfed, Hungry };

class CatView {
private:
    std::shared_ptr<Cat> cat;
    float phase;                       

    Expression current = Expression::Idle;
    Expression followUp = Expression::Idle;
    bool hasFollowUp = false;
    float expressionTimer = 0.f;
    float followUpSeconds = 0.f;

    float time = 0.f;
    float bounceT = 0.f;               
    std::string bubble;
    float bubbleTimer = 0.f;

    bool wasHungry = false;
    float cryTimer = 0.f;              
    bool alertPending = false;

    Expression baseExpression() const; 

public:
    static constexpr int HUNGRY_BELOW = 30;   
    static constexpr int SLEEPY_FROM = 90;    

    CatView(std::shared_ptr<Cat> catPtr, float phaseOffset);

    void update(float dt);

    void react(Expression first, float firstSeconds, Expression then, float thenSeconds);
    void say(const std::string& text, float seconds);

    bool takeHungryAlert();

    const Cat& getCat() const;
    Expression getExpression() const;
    std::string textureName() const;   
    float swayDegrees() const;
    float squash() const;
    float bounceOffset() const;        
    bool hasBubble() const;
    const std::string& bubbleText() const;
};

#endif // CAT_VIEW_HPP
