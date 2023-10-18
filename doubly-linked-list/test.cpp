/************************************************************
 * To test if implementation of data structure is correct.  *
 ************************************************************/

#include <iostream>
#include <string>

// Uncomment the .h files when you're ready to start testing
#include "doubly-linked-list.h"

// Once uncommented, you will need to modify the CMakeLists.txt
// to add the .cpp file to be able to compile again.

// Note: This may require you to "rebuild" or "Reload CMake Project"

using namespace std;


#define ASSERT_TRUE(T) \
    if (!(T))          \
        return false;
#define ASSERT_FALSE(T) \
    if ((T))            \
        return false;


string get_status_str(bool status) {
    return status ? "TEST PASSED" : "TEST FAILED";
}

class DoublyLinkedListTest {
    public:
        bool test1();
        bool test2();
        bool test3();
        bool test4();
        bool test5();
        bool test6();
        bool test7();
        bool test8();
        bool test9();
        bool test10();
};

int main() {

    int grade = 0;
    int double_num_of_tests = 10;
    bool testDouble = true;

    DoublyLinkedListTest double_tests;

    string doubly_test_desc[10] = {
        "Test 1: New empty list is valid",
        "Test 2: insert front and insert back",
        "Test 3: insert",
        "Test 4: remove front and remove back",
        "Test 5: remove",
        "Test 6: search and select",
        "Test 7: insert too many elements should fail",
        "Test 8: multiple valid and invalid inputs and removes",
        "Test 9: replace works",
        "Test 10"
    };

    bool doubly_test_results[double_num_of_tests];
    doubly_test_results[0] = double_tests.test1();
    doubly_test_results[1] = double_tests.test2();
    doubly_test_results[2] = double_tests.test3();
    doubly_test_results[3] = double_tests.test4();
    doubly_test_results[4] = double_tests.test5();
    doubly_test_results[5] = double_tests.test6();
    doubly_test_results[6] = double_tests.test7();
    doubly_test_results[7] = double_tests.test8();
    doubly_test_results[8] = double_tests.test9();
    doubly_test_results[9] = double_tests.test10();


    if (testDouble) {
        cout << "DOUBLY LINKED LIST TESTING RESULTS \n";
        cout << "******************************* \n";
        for (int i = 0; i < double_num_of_tests; ++i) {

            cout << doubly_test_desc[i] << endl
                << get_status_str(doubly_test_results[i]) << endl;
        }
    } 
    return 0;
}

// new empty list
bool DoublyLinkedListTest::test1() {
    DoublyLinkedList list;

    ASSERT_TRUE(list.size() == 0)
    ASSERT_TRUE(list.empty())
    ASSERT_FALSE(list.full());

    return true;
}

// test insert front and back
bool DoublyLinkedListTest::test2() {
    DoublyLinkedList list;

    ASSERT_TRUE(list.insert_front(100))
    ASSERT_TRUE(list.insert_back(200))
    ASSERT_TRUE(list.select(0) == 100)
    ASSERT_TRUE(list.select(1) == 200)

    return true;
}

//test insert
bool DoublyLinkedListTest::test3() {
    DoublyLinkedList list;

    ASSERT_TRUE(list.insert(1, 0))
    ASSERT_TRUE(list.insert(2, 1))
    ASSERT_FALSE(list.insert(3, 3))
    
    ASSERT_TRUE(list.insert(20, 1))
    ASSERT_TRUE(list.select(2) == 2)

    ASSERT_TRUE(list.size() == 3)

    return true;
}

//test remove front and back
bool DoublyLinkedListTest::test4() {
    DoublyLinkedList list;

    ASSERT_FALSE(list.remove_front())
    ASSERT_FALSE(list.remove_back())

    for (int i = 0; i < 5; i++) {
        list.insert_back(i);
    }

    ASSERT_TRUE(list.remove_back())
    ASSERT_TRUE(list.remove_front())
    ASSERT_TRUE(list.size() == 3)
    ASSERT_TRUE(list.select(0) == 1)

    return true;
}

//test remove
bool DoublyLinkedListTest::test5() {
    DoublyLinkedList list;

    ASSERT_FALSE(list.remove(0))
    
    for (int i = 0; i < 5; i++) {
        list.insert_back(i);
    }

    ASSERT_TRUE(list.remove(2))
    ASSERT_TRUE(list.remove(3))
    ASSERT_TRUE(list.remove(0))
    ASSERT_TRUE(list.size() == 2 && list.select(0) == 1)

    return true;
}

//test search and select
bool DoublyLinkedListTest::test6() {
    DoublyLinkedList list;

    for (int i = 0; i < 5; i++) {
        list.insert_back(i);
    }

    ASSERT_TRUE(list.select(2) == list.search(2))
    ASSERT_TRUE(list.select(100) == 4)
    ASSERT_TRUE(list.search(17) == list.size())

    return true;
}

// test capacity (set capacity to 10)
bool DoublyLinkedListTest::test7() {
    DoublyLinkedList list;

    for (int i = 0; i < 10; i++) {
        ASSERT_TRUE(list.insert_back(i));
    }    

    ASSERT_FALSE(list.insert(3, 3));
    ASSERT_FALSE(list.insert_back(4));
    ASSERT_FALSE(list.insert_front(2));

    return true;
}

// multiple valid and invalid inputs and removes
bool DoublyLinkedListTest::test8() {
    DoublyLinkedList list;

    ASSERT_FALSE(list.remove(0))
    ASSERT_TRUE(list.insert_back(32))
    ASSERT_TRUE(list.insert_front(44))
    ASSERT_FALSE(list.insert(12, 3))
    ASSERT_TRUE(list.insert(12, 2))
    ASSERT_TRUE(list.remove_back())
    ASSERT_FALSE(list.remove(5))
    ASSERT_TRUE(list.remove_front())
    ASSERT_TRUE(list.insert_back(88))
    ASSERT_FALSE(list.insert(12345, 6))
    ASSERT_TRUE(list.remove(1))
    ASSERT_TRUE(list.insert(99, 0))

    ASSERT_TRUE(list.select(0) == 99)
    ASSERT_TRUE(list.select(1) == 32)

    return true;
}

bool DoublyLinkedListTest::test9() {
    DoublyLinkedList list;

    for (int i = 0; i < 10; i++) {
        ASSERT_TRUE(list.insert_back(i));
    }

    ASSERT_TRUE(list.replace(2, 200));
    ASSERT_TRUE(list.replace(0, 500));
    ASSERT_TRUE(list.replace(9, 1500));
    ASSERT_FALSE(list.replace(10, 10));
    ASSERT_TRUE(list.select(2) == 200);
    ASSERT_TRUE(list.select(0) == 500);
    ASSERT_TRUE(list.select(9) == 1500);

    return true;
}

bool DoublyLinkedListTest::test10() {
    
    return true;
}

