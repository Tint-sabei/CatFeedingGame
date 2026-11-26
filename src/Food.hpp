#ifndef FOOD_HPP
#define FOOD_HPP

#include <iostream>
#include <memory> 

class Food {
public:
    Food();
    virtual ~Food();

    virtual void treat() const = 0;
    virtual void eat() const = 0;

    static std::shared_ptr<Food> createFish();
    static std::shared_ptr<Food> createDryFood();
    static std::shared_ptr<Food> createMilk();
};

class Fish : public Food {
public:
    Fish();
    ~Fish();
    void treat() const override ;
    void eat() const override;
};

class DryFood : public Food {
public:
    DryFood();
    ~DryFood();
    void treat() const override;
    void eat() const override;
};

class Milk : public Food {
public:
    Milk();
    ~Milk();
    void treat() const override;
    void eat() const override;
};

#endif // FOOD_HPP