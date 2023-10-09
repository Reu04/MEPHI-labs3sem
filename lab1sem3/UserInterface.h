#include <iostream>
#include <vector>
#include "SharedPtr.h"

template<typename T>
void UIAddPtr(std::vector<SharedPtr<T>>& vec, T* object) {
    if (vec.empty()) {
        vec.emplace_back(object);
    } else {
        SharedPtr<T> newPtr(vec[vec.size() - 1]);
        vec.push_back(newPtr);
    }
}

template<typename T>
void UIFunctions(SharedPtr<T>& ptr) {
    std::cout << "Which function do you want to use?\n1. *\n2. Get\n3. Use_count\n4. Unique\n5. Reset\n6. Swap\n7. Exit\n";
    int func;
    std::cin >> func;
    switch (func) {
        case 1:
            std::cout << "\nThe object is: " << *ptr << std::endl;
            break;
        case 2:
            std::cout << "\nThe address of the object is: " << ptr.Get() << std::endl;
            break;
        case 3:
            std::cout << "\nThe number of pointers to the object is: " << ptr.Use_count() << std::endl;
            break;
        case 4:
            std::cout << "\nIs the pointer unique? " << ptr.Unique() << std::endl;
            break;
        case 5:
        {
            std::cout << "\nEnter new object:\n";
            T* newObject = new T;
            std::cin >> *newObject;
            ptr.Reset(newObject);
            std::cout << "\nThe object is:\n" << *ptr << std::endl;
            break;
        }
        case 6:
        {
            std::cout << "\nEnter new object:\n";
            T* newObject1 = new T;
            std::cin >> *newObject1;
            SharedPtr<T> otherPtr(newObject1);
            ptr.Swap(otherPtr);
            std::cout << "\nThe object is: " << *ptr << std::endl;
            break;
        }
        case 7:
            break;
        default:
            std::cout << "Wrong function\n";
            break;
    }
}

template<typename T>
void UINextStep() {
    std::vector<SharedPtr<T>> vec;
    T* object = new T;

    std::cout << "Enter the object:\n";
    std::cin >> *object;

    UIAddPtr<T>(vec, object);

    bool flag = true;
    while (flag) {
        std::cout << "Do you want to continue?\n1. Yes\n0. No\n";
        std::cin >> flag;
        if (!flag) {
            break;
        }
        std::cout << "What do you want to do?\n1. Create a new pointer to the object\n2. Call the function\n3. Delete the ptr\n4. Exit\n";
        int step;
        std::cin >> step;
        switch (step) {
            case 1:
            {
                UIAddPtr<T>(vec, object);
                break;
            }
            case 2:
            {
                std::cout << "Enter the number of the pointer:\n";
                size_t num;
                std::cin >> num;
                UIFunctions(vec[num - 1]); // ПЕРВЫЙ НЕ НОЛЬ
                break;
            }
            case 3:
            {
                std::cout << "Enter the number of the pointer:\n";
                size_t num;
                std::cin >> num;
                vec.erase(vec.begin() + num - 1);
                break;
            }
            case 4:
                flag = false;
                break;
            default:
                std::cout << "Wrong answer\n";
                break;
        }
    }
}

void UI() {
    std::cout << "A pointer to what type of object you want to create?\n1. int\n2. double\n3. char\n4. std::string\n";
    int type;
    std::cin >> type;
    switch (type) {
        case 1:
            UINextStep<int>();
            break;
        case 2:
            UINextStep<double>();
            break;
        case 3:
            UINextStep<char>();
            break;
        case 4:
            UINextStep<std::string>();
            break;
        default:
            std::cout << "Wrong type.\n";
            break;
    }
}