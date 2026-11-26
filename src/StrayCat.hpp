#ifndef STRAY_CAT_HPP
#define STRAY_CAT_HPP

#include "Cat.hpp"
#include <iostream>
#include <memory>

template<typename T>
class StrayCat : public Cat {
private:
    T trait;  

public:
    StrayCat() : Cat(), trait() {}

    StrayCat(std::string name, int age, int fullnessLevel)
        : Cat(name, age, fullnessLevel), trait() {}

    StrayCat(const StrayCat<T>& other)
        : Cat(other), trait(other.trait) {}

    StrayCat<T>& operator=(const StrayCat<T>& other) {  
        if (this == &other) return *this;
        Cat::operator=(other);
        trait = other.trait;
        return *this;
    }

    ~StrayCat() {}

    std::shared_ptr<Cat> clone() const override {
        return std::make_shared<StrayCat<T>>(*this);
    }

    std::string getType() const override {
        return "Stray Cat";
    }

    void sound() const override {
        std::cout << R"(

                |\---/|
                | o_o |
                 \_^_/

       Sound: HISSS! *scratches*

    )" << "\n";
    }

    void describeTrait() const {
        std::cout << "Trait info: " << trait << "\n";
    }
};

#endif // STRAY_CAT_HPP