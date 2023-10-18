/************************************************************
 * To test if implementation of data structure is correct.  *
 ************************************************************/

#include <iostream>
#include <string>

#include "circular-queue.h"

using namespace std;

// Assert Macros for test cases.
#define ASSERT_TRUE(T) \
    if (!(T))          \
        return false;
#define ASSERT_FALSE(T) \
    if ((T))            \
        return false;

string get_status_str(bool status)
{
    return status ? "PASSED" : "FAILED";
}

// Define the test suites (implementation below).
class DynamicStackTest
{
private:
    bool test_result[4] = {0, 0, 0, 0};
    string test_description[4] = {
        "Test1: new empty stack is valid",
        "Test2: push() an element on zero-element stacks",
        "Test3: peek() and pop() on one-element stack",
        "Test4: peek(), push(), and pop() work properly together",
    };

public:
    string getTestDescription(int test_num);
    void runAllTests();
    void printReport();

    bool test1();
    bool test2();
    bool test3();
    bool test4();
};

class CircularQueueTest
{
private:
    bool test_result[4] = {0, 0, 0, 0};
    string test_description[4] = {
        "Test1: new empty queue is valid",
        "Test2: enqueue() an element on zero-element queues",
        "Test3: peek() and dequeue() on one-element queue",
        "Test4: peek(), enqueue(), and dequeue() work properly together",
    };

public:
    string getTestDescription(int test_num);
    void runAllTests();
    void printReport();

    bool test1();
    bool test2();
    bool test3();
    bool test4();
};

//======================================================================
//================================ MAIN ================================
//======================================================================
int main()
{
    CircularQueueTest cq_test;
    cq_test.runAllTests();
    cq_test.printReport();

    return 0;
}

//======================================================================
//======================== Circular Queue Test =========================
//======================================================================
string CircularQueueTest::getTestDescription(int test_num)
{
    if (test_num < 1 || test_num > 4)
    { // check range.
        return "";
    }
    return test_description[test_num - 1];
}

void CircularQueueTest::runAllTests()
{
    test_result[0] = test1();
    test_result[1] = test2();
    test_result[2] = test3();
    test_result[3] = test4();
}

void CircularQueueTest::printReport()
{
    cout << "  CIRCULAR QUEUE TEST RESULTS  \n"
         << " ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ \n";
    for (int idx = 0; idx < 4; ++idx)
    {
        cout << test_description[idx] << "\n  " << get_status_str(test_result[idx]) << endl
             << endl;
    }
    cout << endl;
}

// Test 1: new empty queue is valid
bool CircularQueueTest::test1()
{

    // Test set up.
    unsigned int capacity = 5;
    CircularQueue queue(capacity);

    // Check that the internal state is set correctly.
    ASSERT_TRUE(queue.size() == 0)
    ASSERT_TRUE(queue.empty())
    ASSERT_FALSE(queue.full())
    ASSERT_TRUE(queue.capacity_ == capacity)
    ASSERT_FALSE(queue.items_ == nullptr)
    ASSERT_TRUE(queue.head_ == 0 && queue.tail_ == 0)

    // Test the default constructor for the queue.
    CircularQueue default_queue;

    // Check that the internal state is set correctly.
    ASSERT_TRUE(default_queue.size() == 0)
    ASSERT_TRUE(default_queue.empty())
    ASSERT_FALSE(default_queue.full())
    ASSERT_TRUE(default_queue.capacity_ == 16)
    ASSERT_FALSE(default_queue.items_ == nullptr)
    ASSERT_TRUE(default_queue.head_ == 0 && default_queue.tail_ == 0)

    // Return true to signal all tests passed.
    return true;
}

// Test 2: enqueue() an element on zero-element queues
bool CircularQueueTest::test2()
{

    // Test set up.
    unsigned int capacity = 5;
    CircularQueue queue1(capacity);
    CircularQueue queue2(capacity);

    // Try to enqueue data to the queues.
    ASSERT_TRUE(queue1.enqueue(100))
    ASSERT_TRUE(queue2.enqueue(100))

    // Check that the internal state is correct.
    ASSERT_TRUE(queue1.size() == queue2.size() && queue1.size() == 1)
    ASSERT_FALSE(queue1.items_ == nullptr)
    ASSERT_FALSE(queue2.items_ == nullptr)
    ASSERT_TRUE(queue1.items_[queue1.head_] == 100)
    ASSERT_TRUE(queue2.items_[queue2.head_] == 100)
    ASSERT_TRUE(queue1.head_ == 0 && queue1.tail_ == 1)
    ASSERT_TRUE(queue2.head_ == 0 && queue2.tail_ == 1)

    // Return true to signal all tests passed.
    return true;
}

// Test 3: peek() and dequeue() on one-element queue
bool CircularQueueTest::test3()
{

    // Test set up.
    unsigned int capacity = 5;
    CircularQueue queue1(capacity);
    CircularQueue queue2(capacity);

    // Check peek on an empty queue.
    ASSERT_TRUE(queue1.peek() == CircularQueue::EMPTY_QUEUE)

    // Add data to the queues.
    ASSERT_TRUE(queue1.enqueue(100))
    ASSERT_TRUE(queue2.enqueue(200))

    // Peek at the top element, then remove it.
    ASSERT_TRUE(queue1.peek() == 100 && queue1.dequeue() == 100)
    ASSERT_TRUE(queue2.peek() == 200 && queue2.dequeue() == 200)

    // Check the resulting sizes of the queues.
    ASSERT_TRUE(queue1.size_ == queue2.size_ && queue1.size_ == 0)
    ASSERT_TRUE(queue1.empty() && queue2.empty())

    // Check that the peek on an empty queue still gives expected value.
    ASSERT_TRUE(queue2.peek() == CircularQueue::EMPTY_QUEUE)

    // Return true to signal all tests passed.
    return true;
}

// Test 4: peek(), enqueue(), and dequeue() work properly together
bool CircularQueueTest::test4()
{
     unsigned int capacity = 5;
    CircularQueue queue1(capacity);
    CircularQueue queue2(capacity);

    ASSERT_TRUE(queue1.peek() == CircularQueue::EMPTY_QUEUE)

    // Add data to the queues.
    ASSERT_TRUE(queue1.enqueue(100))
    ASSERT_TRUE(queue1.enqueue(200))
    ASSERT_TRUE(queue1.enqueue(300))
    ASSERT_TRUE(queue1.peek() == 100 && queue1.dequeue() == 100)
    ASSERT_TRUE(queue1.enqueue(400))
    ASSERT_TRUE(queue1.enqueue(500))
    ASSERT_TRUE(queue1.enqueue(600))
    ASSERT_FALSE(queue1.enqueue(700))
    ASSERT_TRUE(queue1.peek() == 200 && queue1.dequeue() == 200)
    ASSERT_TRUE(queue1.size_ == 4 )
    ASSERT_TRUE(queue1.enqueue(800))
    ASSERT_TRUE(queue1.peek() == 300 && queue1.dequeue() == 300)
    ASSERT_TRUE(queue1.enqueue(900))
    ASSERT_TRUE(queue1.peek() == 400 && queue1.dequeue() == 400)
    ASSERT_TRUE(queue1.enqueue(110))
    ASSERT_TRUE(queue1.peek() == 500 && queue1.dequeue() == 500)
    ASSERT_TRUE(queue1.enqueue(120))
    ASSERT_TRUE(queue1.peek() == 600 && queue1.dequeue() == 600)
    ASSERT_TRUE(queue1.enqueue(130))
    ASSERT_FALSE(queue1.enqueue(140))
    ASSERT_FALSE(queue1.enqueue(150))
    ASSERT_TRUE(queue1.peek() == 800 && queue1.dequeue() == 800)
    ASSERT_TRUE(queue1.peek() == 900 && queue1.dequeue() == 900)
    ASSERT_TRUE(queue1.peek() == 110 && queue1.dequeue() == 110)
    ASSERT_TRUE(queue1.peek() == 120 && queue1.dequeue() == 120)
    ASSERT_TRUE(queue1.peek() == 130 && queue1.dequeue() == 130)
    ASSERT_TRUE(queue1.dequeue() == -999 && queue1.size_ == 0 && queue1.empty())
    ASSERT_TRUE(queue1.enqueue(100))
    ASSERT_TRUE(queue1.enqueue(200))
    ASSERT_TRUE(queue1.enqueue(300))
    ASSERT_TRUE(queue1.enqueue(400))
    ASSERT_TRUE(queue1.enqueue(500))
    ASSERT_FALSE(queue1.enqueue(600))

    queue1.~CircularQueue();

    ASSERT_TRUE(queue1.items_ == nullptr)
    ASSERT_FALSE(queue1.enqueue(500))

    return true;
}
