#include "DomesticCat.hpp"
#include <iostream>

#include "Cat.hpp"

DomesticCat::DomesticCat() : Cat() {}

DomesticCat::DomesticCat(std::string name, int age, int fullnessLevel)
    : Cat(name, age, fullnessLevel) {}

DomesticCat::DomesticCat(const DomesticCat& other) : Cat(other) {}

DomesticCat& DomesticCat::operator=(const DomesticCat& other) {
    if (this == &other) return *this;
    Cat::operator=(other);
    return *this;
}

DomesticCat::~DomesticCat() {}

std::shared_ptr<Cat> DomesticCat::clone() const {
    return std::make_shared<DomesticCat>(*this);
}

std::string DomesticCat::getType() const { 
    return "Domestic Cat"; 
}

void DomesticCat::sound() const {
    std::cout << R"(

             /\_____/\
            /  o   o  \
           ( ==  ^  == )
            )         (
           (           )
          ( (  )   (  ) )
         (__(__)___(__)__)

        Sound: Purrr... meow!
    
    )" << "\n";
}


