#ifndef CAT_HPP
#define CAT_HPP

#include <string>
#include <iostream>
#include <memory> 

class Cat {
protected:
    std::string name;
    int age;
    int fullnessLevel;
    static int catCount; 

public:
    Cat();
    Cat(std::string name, int age, int fullnessLevel);
    Cat(const Cat& other);
    Cat& operator=(const Cat& other);

    virtual ~Cat();

    static int getCatCount();
    
    virtual std::shared_ptr<Cat> clone() const = 0; 
    virtual std::string getType() const = 0;
    virtual void sound() const = 0; 

    std::string getName() const;
    int getAge() const;
    int getFullnessLevel() const;

    void update(int value);
};

#endif // CAT_HPP