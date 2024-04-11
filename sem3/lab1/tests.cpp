#include <iostream>
#include <cassert>

#include "SharedPtr.hpp"
#include "UniquePtr.hpp"


using namespace std;


class TestClass {
public:
    static int destructorCalls;

    ~TestClass() {
        destructorCalls++;
    }
};

int TestClass::destructorCalls = 0;

void testSharedPtr() {
    cout << "Starting tests...\n";

    // Test constructor
    SharedPtr<int> sp1(new int(10));
    assert(*sp1 == 10);
    cout << "Constructor test passed\n";

    // Test copy constructor
    SharedPtr<int> sp2 = sp1;
    assert(*sp2 == 10);
    assert(sp1.get() == sp2.get());
    cout << "Copy constructor test passed\n";

    // Test assignment operator
    SharedPtr<int> sp3(new int(20));
    sp2 = sp3;
    assert(*sp2 == 20);
    assert(sp1.get() != sp2.get());
    assert(sp2.get() == sp3.get());
    cout << "Assignment operator test passed\n";

    // Test destructor
    {
        SharedPtr<int> sp4(new int(30));
    } // sp4 goes out of scope here, should be deleted
    cout << "Destructor test passed\n";

    // Test multiple references
    SharedPtr<int> sp5(new int(40));
    SharedPtr<int> sp6 = sp5;
    SharedPtr<int> sp7 = sp5;
    assert(*sp5 == 40);
    assert(*sp6 == 40);
    assert(*sp7 == 40);
    assert(sp5.get() == sp6.get());
    assert(sp5.get() == sp7.get());
    cout << "Multiple references test passed\n";

    // Test with arrays
    SharedPtr<int> sp8(new int[10], [](int* p) { delete[] p; });
    for (int i = 0; i < 10; i++) {
        sp8[i] = i;
    }
    for (int i = 0; i < 10; i++) {
        assert(sp8[i] == i);
    }
    cout << "Array handling test passed\n";

    // Test with custom objects
    {
        SharedPtr<TestClass> sp9(new TestClass());
    } // sp9 goes out of scope here, should be deleted
    assert(TestClass::destructorCalls == 1);
    cout << "Custom objects test passed\n";

    cout << "All tests passed!\n";
}


void testUniquePtr() {
    cout << "Starting tests...\n";

    // Test constructor
    UniquePtr<int> up1(new int(10));
    assert(*up1 == 10);
    cout << "Constructor test passed\n";

    // Test move constructor
    UniquePtr<int> up2 = std::move(up1);
    assert(*up2 == 10);
    assert(up1.get() == nullptr);
    cout << "Move constructor test passed\n";

    // Test move assignment operator
    UniquePtr<int> up3(new int(20));
    up2 = std::move(up3);
    assert(*up2 == 20);
    assert(up3.get() == nullptr);
    cout << "Move assignment operator test passed\n";

    // Test destructor
    {
        UniquePtr<int> up4(new int(30));
    } // up4 goes out of scope here, should be deleted
    cout << "Destructor test passed\n";

    // Test with custom objects
    {
        UniquePtr<TestClass> up5(new TestClass());
    } // up5 goes out of scope here, should be deleted
    assert(TestClass::destructorCalls == 1);
    cout << "Custom objects test passed\n";

    cout << "All tests passed!\n";
}

int main() {
    cout << "Starting SharedPtr tests...\n";
    testSharedPtr();
    cout << "SharedPtr tests passed!\n\n";

    TestClass::destructorCalls = 0;

    cout << "Starting UniquePtr tests...\n";
    testUniquePtr();
    cout << "UniquePtr tests passed!\n\n";

    return 0;
}