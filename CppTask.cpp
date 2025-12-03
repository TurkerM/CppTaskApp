#include <iostream>
#include <thread>
#include <chrono> 
#include <cstdlib>

class IBaseClass {
public:
    virtual void PublicFunc() {
        std::cout << "Public in base" << std::endl;
    }

private:
    virtual void PrivateFunc() {
        std::cout << "Private in base" << std::endl;
    }

protected:
    virtual void ProtectedFunc() {
        std::cout << "Protected in base" << std::endl;
    }
};

class Child1 : public IBaseClass {
    int field1;
};

class Child2 : public IBaseClass {
    int field2;
};

int main()
{
    for (int i = 1; i <= 10; i++) {
        int numA = rand() % 10 + 1;
        int numB = rand() % 10 + 1;
        for (int j = 1; j <= numA; j++) {
            std::cout << "loop_a =" << j << std::endl;
        }
        
        for (int j = 1; j <= numB; j++) {
            std::cout << "loop_b =" << j << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}