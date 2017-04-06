#ifndef LAB_2_TEST_H
#define LAB_2_TEST_H

#define RANGE_FROM 0
#define RANGE_TO 65535
#define N 1000

#include "linked_list.h"
#include <vector>
#include <set>
#include<algorithm>
#include <random>
#include <ctime>

using namespace std;

/**
 * Operations to be invoked concurrently.
 */
enum Op {
    MEMBER,
    INSERT,
    DELETE
};

/**
 * Base class for performance tests. Has the functions required to configure tests.
 */
class test {

private:
    unsigned short iterations;

    /**
    * Configures the required numbers for the performance test
    * @param numbers The vector to which the random numbers will be copied
    */
    void configure_elements() {
        list = new linked_list();

        vector<unsigned short> numbers(N);
        cout << "Starting configuration" << endl;

        set<unsigned short> set;

        random_device rand_device;
        mt19937 generator(rand_device());
        uniform_int_distribution<unsigned short> distribution(RANGE_FROM, RANGE_TO);

        while (set.size() < N) {
            unsigned short num = distribution(generator);
            set.insert(num);
        }
        cout << "Random numbers generated successfully" << endl;

        cout << "Copying to a vector" << endl;
        copy(set.begin(), set.end(), numbers.begin());

        default_random_engine random_engine;
        cout << "Shuffling numbers in the vector" << endl;
        shuffle(numbers.begin(), numbers.end(), random_engine);

        cout << "Populating Linked List" << endl;
        for (unsigned short i : numbers) {
            list->insert(i);
        }
        cout << "Linked list created successfully" << endl;
    }

protected:
    linked_list *list;
    vector<Op> execution_plan;
    default_random_engine random_engine;
    int insert_ops;
    int delete_ops;
    int member_ops;

    /**
     * Sets up the test. Populates the linked list and etc
     */
    virtual void setup_test() {
        configure_elements();

        cout << "Shuffling the execution plan" << endl;
        shuffle(execution_plan.begin(), execution_plan.end(), random_engine);
        cout << "Execution plan shuffled successfully" << endl;
    }

    /**
     * Tear down the test.
     */
    virtual void teardown_test() {
        delete (list);
        execution_plan.clear();
    };

    virtual void run()= 0;

public:
    test(int n, unsigned int m, unsigned short iter, float member_percentage,
         float insert_percentage, float delete_percentage) {

        iterations = iter;

        insert_ops = int(m * insert_percentage);
        delete_ops = int(m * delete_percentage);
        member_ops = int(m * member_percentage);

        // Initialize everything to MEMBER type operation
        Op ops[m]{};

        cout << "Setting up " << insert_ops << " insert operations" << endl;
        for (int i = 0; i < insert_ops; i++) {
            ops[i] = INSERT;
        }

        cout << "Setting up " << delete_ops << " delete operations" << endl;
        for (int i = insert_ops; i < insert_ops + delete_ops; i++) {
            ops[i] = DELETE;
        }

        copy(&ops[0], &ops[m], back_inserter(execution_plan));
    }

    /**
     * This method has to be called in order to run the actual test.
     */
    void run_test() {
        for (int i = 0; i < iterations; i++) {
            cout << "\nRunning " << i << "th test iteration" << endl;
            setup_test();
            cout << "Test setup successful" << endl;

            const clock_t start = clock();
            run();
            cout << "Test took " << float(clock() - start) / CLOCKS_PER_SEC << " seconds to execute\n\n" << endl;
            teardown_test();
        }
    }
};

#endif //LAB_2_TEST_H
