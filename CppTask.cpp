#include <iostream>
#include <thread>
#include <chrono> 
#include <cstdlib>
#include <algorithm>
#include <list>
#include <vector>

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
public:
    int field1;
};

class Child2 : public IBaseClass {
public:
    int field2;
};


std::vector<int> unique_numbers;

std::list<std::unique_ptr<Child1>> instances_1;
std::list<std::unique_ptr<Child2>> instances_2;

bool CheckIfExist(int numToCheck) {
    if (unique_numbers.size() == 0)
        return false;
    return std::find(unique_numbers.begin(), unique_numbers.end(), numToCheck) != unique_numbers.end();
}

int GetUniqueRandom() {
    int randomNum;
    do
    {
        randomNum = rand() % 200 + 1;
        //std::cout << CheckIfExist(randomNum) << std::endl;
    } while (CheckIfExist(randomNum));
    return randomNum;
}

int main()
{
    srand(time(0));
    for (int i = 1; i <= 10; i++) {
        int numA = rand() % 10 + 1;
        int numB = rand() % 10 + 1;
        for (int j = 1; j <= numA; j++) {
            std::cout << "loop_a =" << j << std::endl;
            instances_1.push_back(std::make_unique<Child1>());
            Child1* obj = new Child1();
            obj->field1 = GetUniqueRandom();
            unique_numbers.push_back(obj->field1);
        }
        
        for (int j = 1; j <= numB; j++) {
            std::cout << "loop_b =" << j << std::endl;
            instances_2.push_back(std::make_unique<Child2>());
            Child2* obj = new Child2();
            obj->field2 = GetUniqueRandom();
            unique_numbers.push_back(obj->field2);
        }

        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}