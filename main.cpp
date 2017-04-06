#include <iostream>
#include "serial_test.h"
#include "mutex_test.h"

using namespace std;

int main(int argc, char **argv) {
    cout << "Running the serial test" << endl;
    serial_test test(1000, 10000, 10, 0.9, 0.05, 0.05);
    test.run_test();

    cout << "\n\n\n" << endl;

    cout << "Running the mutex test" << endl;
    mutex_test mutex_test(1000, 10000, 10, 0.9, 0.05, 0.05, 4);
    mutex_test.run_test();
}