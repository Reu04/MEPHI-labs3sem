#pragma once

#include <iostream>
#include <string>

#include "SharedPtr.h"

void TestSharedPtrFunction() {
    std::cout << std::endl;
    SharedPtr<int> ptr1(new int(15));

    assert(*ptr1 == 15);

    SharedPtr<int> ptr2(ptr1);

    assert(*ptr1 == *ptr2);
    assert(ptr1.Get() == ptr2.Get());
    assert(ptr1.UseCount() == ptr2.UseCount());

    assert(ptr2.UseCount() == 2);
    std::cout << "SharedCount_ Object 1(int): " << ptr2.UseCount() << std::endl;



    SharedPtr<int> ptr5(new int(20));

    assert(*ptr5 == 20);

    assert(ptr5.UseCount() == 1);
    std::cout << "SharedCount_ Object 2(int): " << ptr5.UseCount() << std::endl;



    SharedPtr<std::string> ptr3(new std::string("Tagir"));

    assert(*ptr3 == "Tagir");

    SharedPtr<std::string> ptr4(ptr3);

    assert(*ptr3 == *ptr4);
    assert(ptr3.Get() == ptr4.Get());
    assert(ptr3.UseCount() == ptr4.UseCount());

    assert(ptr4.UseCount() == 2);
    std::cout << "SharedCount_ Object 3(string): " << ptr4.UseCount() << std::endl;
    std::cout << std::endl;



    // Operator =
    ptr1 = ptr5;

    assert(*ptr1 == *ptr5);
    assert(ptr1.Get() == ptr5.Get());
    assert(ptr1.UseCount() == ptr5.UseCount());

    assert(ptr2.UseCount() == 1);
    std::cout << "SharedCount_ Object 1(int): " << ptr2.UseCount() << std::endl;
    assert(ptr5.UseCount() == 2);
    std::cout << "SharedCount_ Object 2(int): " << ptr5.UseCount() << std::endl;
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
    assert(ptr1.Unique() == false);
    std::cout << "Is ptr1 unique: " << ptr1.Unique() << std::endl;

    assert(ptr2.Unique() == true);
    std::cout << "Is ptr2 unique: " << ptr2.Unique() << std::endl;

    assert(ptr3.Unique() == false);
    std::cout << "Is ptr3 unique: " << ptr3.Unique() << std::endl;

    assert(ptr4.Unique() == false);
    std::cout << "Is ptr4 unique: " << ptr4.Unique() << std::endl;

    assert(ptr5.Unique() == false);
    std::cout << "Is ptr5 unique: " << ptr5.Unique() << std::endl;
    std::cout << std::endl;

    // Reset()
    assert(ptr5.UseCount() == 2);
    std::cout << "SharedCount_ Object 2(int) before Reset(): " << ptr5.UseCount() << std::endl;

    ptr1.Reset(new int(1110));

    assert(*ptr1 == 1110);
    std::cout << "*Object 1 after Reset(): " << *ptr1 << std::endl;

    assert(ptr1.UseCount() == 1);
    std::cout << "SharedCount_ Object 1(int) after Reset(): " << ptr1.UseCount() << std::endl;

    assert(ptr5.UseCount() == 1);
    std::cout << "SharedCount_ Object 2(int) after Reset(): " << ptr5.UseCount() << std::endl;
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
    TestSharedPtrFunction();

    return 0;
}