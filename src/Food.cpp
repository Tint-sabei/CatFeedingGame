#include "Food.hpp"       
#include <iostream>       
#include <memory>        

Food::Food() {}

Food::~Food() {}

std::shared_ptr<Food> Food::createFish() { 
    return std::make_shared<Fish>(); 
}

std::shared_ptr<Food> Food::createDryFood() { 
    return std::make_shared<DryFood>(); 
}

std::shared_ptr<Food> Food::createMilk() { 
    return std::make_shared<Milk>(); 
}

Fish::Fish() { 
    std::cout << "Fish created\n"; 
}

Fish::~Fish() { 
    std::cout << "Fish destroyed\n"; 
}

void Fish::treat() const { 
    std::cout << "Treat: Fish\n"; 
}

void Fish::eat() const { 
    std::cout << R"(


        *==== FISH =====*

             /`·.¸
            /¸...¸`:·
        ¸.·´  ¸   `·.¸.·´)
        : © ):´;      ¸  {
        `·.¸ `·  ¸.·´\`·¸)
            `\\´´\¸.·´



    
    )" << "\n";
}

DryFood::DryFood() { 
    std::cout << "DryFood created\n"; 
}

DryFood::~DryFood() { 
    std::cout << "DryFood destroyed\n"; 
}

void DryFood::treat() const { 
    std::cout << "Treat: DryFood\n"; 
}

void DryFood::eat() const { 
    std::cout << R"(


        *==== DRY FOOD =====*

                           
          ___,.-------..____
     _,-'' xxxxxxxxxxxxxxxxx`'-.
  ;' xxxxxxxxxxxxxxxxxxxxxxxxx  :  
  (xxxxxxxxxxxxxxxxxxxxxxxxxxxxx  )
   :.xxxxxxxxxxxxxxxxxxxxxxxxx    :
    `.`--.___  xxxxxxxx _____-- .'
      `.     ``-------''     ,'
         -.               ,-
            `-._______.-'


    )" << "\n";
}

Milk::Milk() { 
    std::cout << "Milk created\n"; 
}

Milk::~Milk() { 
    std::cout << "Milk destroyed\n"; 
}

void Milk::treat() const { 
    std::cout << "Treat: Milk\n"; 
}

void Milk::eat() const { 
    std::cout << R"(

           *==== MILK =====*

               _________
              | _______ |
             / \         \
            /___\_________\
            |   | \       |
            |   |  \      |
            |   |   \     |
            |   | M  \    |
            |   |     \   |
            |   |\  I  \  |
            |   | \     \ |
            |   |  \  L  \|
            |   |   \     |
            |   |    \  K |
            |   |     \   |
            |   |      \  |
            |___|_______\_|

    
    )" << "\n";
}
