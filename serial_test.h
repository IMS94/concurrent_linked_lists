#ifndef LAB_2_SERIAL_TEST_H
#define LAB_2_SERIAL_TEST_H

#include "linked_list.h"
#include "test.h"
#include <vector>

using namespace std;

class serial_test : public test {

private:
    unsigned short *random_nums;
    int random_num_count = 100;

protected:
    void run() {
        int op_count = 0;

        cout << "Execution plan got " << execution_plan->size() << " elements" << endl;
        for (Op operation: *execution_plan) {
            switch (operation) {
                case MEMBER:
                    list->member(random_nums[op_count % random_num_count]);
                    break;
                case DELETE:
                    list->remove(random_nums[op_count % random_num_count]);
                    break;
                case INSERT:
                    list->insert(random_nums[op_count % random_num_count]);
                    break;
            }
            op_count++;
        }
        cout << "Execution completed (Op count : " << op_count << ")" << endl;
    }

    void setup_test() {
        test::setup_test();
        random_nums = new unsigned short[random_num_count];

        random_device rand_device;
        mt19937 generator(rand_device());
        uniform_int_distribution<unsigned short> distribution(RANGE_FROM, RANGE_TO);

        for (int i = 0; i < insert_ops; i++) {
            random_nums[i] = distribution(generator);
        }
    }

    void teardown_test() {
        test::teardown_test();
        delete (random_nums);
    }

public:
    serial_test(int n, int m,
                unsigned short iterations,
                float member_percentage,
                float insert_percentage,
                float delete_percentage,
                unsigned short thread_count) : test(n, m, iterations, member_percentage,
                                                    insert_percentage, delete_percentage) {
        cout << "Creating a serial test" << endl;
    }
};


#endif //LAB_2_SERIAL_TEST_H
