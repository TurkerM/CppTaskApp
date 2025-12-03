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
    for (int i = 0; i <= 10; i++) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << i << std::endl;
    }
}