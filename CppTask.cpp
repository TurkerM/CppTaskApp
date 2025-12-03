#include <iostream>

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
    std::cout << "Hello World!\n";
}