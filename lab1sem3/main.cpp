#include <iostream>
#include <string>

#include "UserInterface.h"

void TestFunction() {
    std::cout << std::endl;
    SharedPtr<int> ptr1(new int(15));
    SharedPtr<int> ptr2(ptr1);
    assert(ptr2.Use_count() == 2);
    std::cout << "SharedCount Object 1(int): " << ptr2.Use_count() << std::endl;

    SharedPtr<int> ptr5(new int(20));
    assert(ptr5.Use_count() == 1);
    std::cout << "SharedCount Object 2(int): " << ptr5.Use_count() << std::endl;

    SharedPtr<std::string> ptr3(new std::string("Tagir"));
    SharedPtr<std::string> ptr4(ptr3);
    assert(ptr4.Use_count() == 2);
    std::cout << "SharedCount Object 3(string): " << ptr4.Use_count() << std::endl;
    std::cout << std::endl;

    // Operator =
    ptr1 = ptr5;
    assert(ptr2.Use_count() == 1);
    std::cout << "SharedCount Object 1(int): " << ptr2.Use_count() << std::endl;
    assert(ptr5.Use_count() == 2);
    std::cout << "SharedCount Object 2(int): " << ptr5.Use_count() << std::endl;
    std::cout << std::endl;

    // Operator *
    assert(*ptr2 == 15);
    std::cout << "*Object 1: " << *ptr2 << std::endl;
    assert(*ptr5 == 20);
    std::cout << "*Object 2: " << *ptr5 << std::endl;
    assert(*ptr3 == "Tagir");
    std::cout << "*Object 3: " << *ptr3 << std::endl;
    std::cout << std::endl;

    // Unique()
    assert(ptr1.Unique() == 0);
    std::cout << "Is ptr1 unique: " << ptr1.Unique() << std::endl;
    assert(ptr2.Unique() == 1);
    std::cout << "Is ptr2 unique: " << ptr2.Unique() << std::endl;
    assert(ptr3.Unique() == 0);
    std::cout << "Is ptr3 unique: " << ptr3.Unique() << std::endl;
    assert(ptr4.Unique() == 0);
    std::cout << "Is ptr4 unique: " << ptr4.Unique() << std::endl;
    assert(ptr5.Unique() == 0);
    std::cout << "Is ptr5 unique: " << ptr5.Unique() << std::endl;
    std::cout << std::endl;

    // Reset()
    assert(ptr5.Use_count() == 2);
    std::cout << "SharedCount Object 2(int) before Reset(): " << ptr5.Use_count() << std::endl;
    ptr1.Reset(new int(1110));
    assert(*ptr1 == 1110);
    std::cout << "*Object 1 after Reset(): " << *ptr1 << std::endl;
    assert(ptr1.Use_count() == 1);
    std::cout << "SharedCount Object 1(int) after Reset(): " << ptr1.Use_count() << std::endl;
    assert(ptr5.Use_count() == 1);
    std::cout << "SharedCount Object 2(int) after Reset(): " << ptr5.Use_count() << std::endl;
    std::cout << std::endl;

    // Swap()
    ptr1.Swap(ptr5);
    assert(*ptr1 == 20);
    std::cout << "*Object 1 after Swap(): " << *ptr1 << std::endl;
    assert(*ptr5 == 1110);
    std::cout << "*Object 2 after Swap(): " << *ptr5 << std::endl;
    std::cout << std::endl;
}

int main() {
    TestFunction();
    UI();

    return 0;
}