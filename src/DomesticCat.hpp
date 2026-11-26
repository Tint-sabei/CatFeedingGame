#ifndef DOMESTIC_CAT_HPP
#define DOMESTIC_CAT_HPP

#include "Cat.hpp"

class DomesticCat : public Cat {
public:
    DomesticCat();
    DomesticCat(std::string name, int age, int fullnessLevel);
    DomesticCat(const DomesticCat& other);
    DomesticCat& operator=(const DomesticCat& other);

    ~DomesticCat();

    std::shared_ptr<Cat> clone() const override;

    std::string getType() const override;
    void sound() const override; 

};

#endif // DOMESTIC_CAT_HPP