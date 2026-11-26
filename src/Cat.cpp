#include "Cat.hpp"
#include <iostream>

#include "Exceptions.hpp"


int Cat::catCount = 0;

Cat::Cat() : name("Unnamed"), age(0), fullnessLevel(100) { catCount++; }

Cat::Cat(std::string name, int age, int fullnessLevel)
    : name(name), age(age), fullnessLevel(fullnessLevel) { catCount++; }

Cat::Cat(const Cat& other)
    : name(other.name), age(other.age), fullnessLevel(other.fullnessLevel) { catCount++; }

Cat& Cat::operator=(const Cat& other) {
    if (this == &other) return *this;
    name = other.name;
    age = other.age;
    fullnessLevel = other.fullnessLevel;
    return *this;
}

Cat::~Cat() { catCount--; }

int Cat::getCatCount() { 
    return catCount; }

std::string Cat::getName() const { 
    return name; 
}
int Cat::getAge() const { 
    return age; 
}
int Cat::getFullnessLevel() const { 
    return fullnessLevel; 
}

void Cat::update(int value) {
    fullnessLevel += value;
    if (fullnessLevel < 0)
        fullnessLevel = 0;               

    if (fullnessLevel > 100) {
        fullnessLevel = 100;
        throw FullnessTooHighException();
    }
}

