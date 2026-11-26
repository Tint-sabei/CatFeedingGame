#include "FatCat.hpp"      
#include <iostream>         

#include "Cat.hpp"          

FatCat::FatCat() : Cat() {}

FatCat::FatCat(std::string name, int age, int fullnessLevel) 
    : Cat(name, age, fullnessLevel) {}

FatCat::FatCat(const FatCat& other) : Cat(other) {}

FatCat& FatCat::operator=(const FatCat& other) { 
    if (this == &other) return *this; 
    Cat::operator=(other);            
    return *this;
}

FatCat::~FatCat() {}

std::shared_ptr<Cat> FatCat::clone() const {
    return std::make_shared<FatCat>(*this);
}

std::string FatCat::getType() const { 
    return "Fat Cat"; 
}

void FatCat::sound() const { 
    std::cout << R"(
                       
                    .       .
             |\_---_/|
            /   o_o   \
            |    U    |
            \  ._I_.  /
             `-_____-'                  
    
        Sound: Mrrrow... *yawn*    
    
    )" << "\n";
}