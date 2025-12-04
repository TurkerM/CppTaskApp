#include <iostream>
#include <thread>
#include <chrono> 
#include <cstdlib>
#include <algorithm>
#include <list>
#include <vector>

//3 farklı türden donksiyon içeren (public, private, protected) interface (abstract class)
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

//Interface'i extend'leyen class 1
class Child1 : public IBaseClass {
public:
    int field1;
};

//Interface'i extend'leyen class 2
class Child2 : public IBaseClass {
public:
    int field2;
};

//Doubly linked list'in nodları için tanımlanan struct
struct Node
{
    IBaseClass* data;
    Node* next;
    Node* prev;

    Node(IBaseClass* d) : data(d), next(nullptr), prev(nullptr) {}
};

//Doubly linked list sınıfı (her iki sınıftan instance'ların tutulacağı list sınıfı)
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

    //field'e göre node aranıp bulunmasını sağlayan metot
    Node* findByField(int value) {
        Node* cur = head;
        while (cur) {
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

//Gelen değerin daha önce alınmış olup olmadığını check edip bool değer döndüren sınıf
bool CheckIfExist(int numToCheck) {
    if (unique_numbers.size() == 0)
        return false;
    return std::find(unique_numbers.begin(), unique_numbers.end(), numToCheck) != unique_numbers.end();
}

//CheckIfExist fonksiyonundan da faydalanarak gereken unique random integer'ın return edilmesini sağlayan fonksiyon
int GetUniqueRandom() {
    int randomNum;
    do
    {
        randomNum = rand() % 200 + 1;
    } while (CheckIfExist(randomNum));
    return randomNum;
}

int main()
{
    srand(time(0)); //random değerlerin program her çalıştığında farklı random üretmesini sağlayan kod
    DoublyLinkedList dll;

    //10 kere dönecek, bir saniyelik periyodu da içinde kapsamış bulunan for döngüsü
    for (int i = 1; i <= 10; i++) {
        int numA = rand() % 10 + 1;
        int numB = rand() % 10 + 1;

        //Child1 Instance'larının ve bunlara istenen şekilde değer atanmasını sağlayan for döngüsü
        for (int j = 1; j <= numA; j++) {
            auto instance = std::make_unique<Child1>();
            instance->field1 = GetUniqueRandom();
            unique_numbers.push_back(instance->field1);
            dll.add(instance.get());
            instances_1.push_back(std::move(instance));
        }
        
        //Child2 Instance'larının ve bunlara istenen şekilde değer atanmasını sağlayan for döngüsü
        for (int j = 1; j <= numB; j++) {
            auto instance = std::make_unique<Child2>();
            instance->field2 = GetUniqueRandom();
            unique_numbers.push_back(instance->field2);
            dll.add(instance.get());
            instances_2.push_back(std::move(instance));
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));   //Döngünün birer saniyelik preiyotlarla çalışmasını sağlayan kod satırı
        std::cout << "Instance'lar olusturuldu ve ilk dongu tamamlandı" << std::endl << "Kalan dongu: " << 10 - i << std::endl;
    }
        //Aranacak değeri random olarak belirleme ve konsola bastırma
        int randomValue = unique_numbers[rand() % unique_numbers.size()];
        std::cout << randomValue << " araniyor." << std::endl;

        //Node'un doubly linked list içerisinde aranması
        Node* found = dll.findByField(randomValue);
        if (found) {
            std::cout << "Instance bulundu!" << std::endl;
        }
        else {
            std::cout << "Instance bulunamadı! :(" << std::endl;
        }
}