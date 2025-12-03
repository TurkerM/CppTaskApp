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

struct Node
{
    IBaseClass* data;
    Node* next;
    Node* prev;

    Node(IBaseClass* d) : data(d), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
public:
    Node* head = nullptr;
    Node* tail = nullptr;

    void add(IBaseClass* obj) {
        Node* n = new Node(obj);

        if (!head) {
            head = tail = n;
            return;
        }

        tail->next = n;
        n->prev = tail;
        tail = n;
    }

    Node* findByField(int value) {
        Node* cur = head;
        while (cur) {
            // Child1 mi Child2 mi kontrol ederek
            // unique field'ı karşılaştır
            if (auto c1 = dynamic_cast<Child1*>(cur->data)) {
                if (c1->field1 == value) return cur;
            }
            if (auto c2 = dynamic_cast<Child2*>(cur->data)) {
                if (c2->field2 == value) return cur;
            }
            cur = cur->next;
        }
        return nullptr;
    }
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
    DoublyLinkedList dll;

    for (int i = 1; i <= 10; i++) {
        int numA = rand() % 10 + 1;
        int numB = rand() % 10 + 1;
        for (int j = 1; j <= numA; j++) {
            std::cout << "loop_a =" << j << std::endl;
            auto instance = std::make_unique<Child1>();
            instance->field1 = GetUniqueRandom();
            unique_numbers.push_back(instance->field1);
            dll.add(instance.get());
            instances_1.push_back(std::move(instance));
        }
        
        for (int j = 1; j <= numB; j++) {
            std::cout << "loop_b =" << j << std::endl;
            auto instance = std::make_unique<Child2>();
            instance->field2 = GetUniqueRandom();
            unique_numbers.push_back(instance->field2);
            dll.add(instance.get());
            instances_2.push_back(std::move(instance));
        }

        int randomValue = unique_numbers[rand() % unique_numbers.size()];
        std::cout << "Searching for: " << randomValue << std::endl;

        // DLL içinde ara
        Node* found = dll.findByField(randomValue);
        if (found) {
            std::cout << "Found instance!" << std::endl;
        }
        else {
            std::cout << "Not found!" << std::endl;
        }

        //std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}