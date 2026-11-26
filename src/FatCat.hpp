#ifndef FAT_CAT_HPP
#define FAT_CAT_HPP

#include "Cat.hpp"

class FatCat : public Cat {
public:
    FatCat();
    FatCat(std::string name, int age, int fullnessLevel);
    FatCat(const FatCat& other);
    FatCat& operator=(const FatCat& other);

    ~FatCat();

    std::shared_ptr<Cat> clone() const override;

    std::string getType() const override;
    void sound() const override; 

};

#endif // FAT_CAT_HPP