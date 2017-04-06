#include <iostream>
#include "serial_test.h"
#include "mutex_test.h"
#include "rw_lock_test.h"

using namespace std;

int main(int argc, char **argv) {
    cout << "Running the serial test" << endl;
    serial_test test(1000, 10000, 1, 0.8, 0.1, 0.1);
    test.run_test();

    cout << "\n\n\n" << endl;

    cout << "Running the mutex test" << endl;
    mutex_test mutex_test(1000, 10000, 1, 0.8, 0.1, 0.1, 4);
    mutex_test.run_test();

    cout << "\n\n\n" << endl;

    cout << "Running the read write lock test" << endl;
    rw_lock_test rw_lock_test(1000, 10000, 1, 0.8, 0.1, 0.1, 4);
    rw_lock_test.run_test();
}