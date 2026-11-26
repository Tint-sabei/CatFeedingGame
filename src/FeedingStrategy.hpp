#ifndef FEEDING_STRATEGY_HPP 
#define FEEDING_STRATEGY_HPP 

class FeedingStrategy {
public:
    virtual int getFullnessIncrease() const = 0;

    virtual int getHungerPerTick() const = 0;

    virtual ~FeedingStrategy() = default;
};

class NormalFeeding : public FeedingStrategy {
public:
    int getFullnessIncrease() const override;
    int getHungerPerTick() const override;
};

class FatCatFeeding : public FeedingStrategy {
public:
    int getFullnessIncrease() const override;
    int getHungerPerTick() const override;
};

#endif // FEEDING_STRATEGY_HPP // 


