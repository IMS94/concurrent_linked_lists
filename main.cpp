#include <iostream>
#include "serial_test.h"

using namespace std;

int main(int argc, int **argv) {
    cout << "Running the serial test" << endl;
    serial_test test(1000, 10000, 10, 0.99, 0.005, 0.005, 4);
    test.run_test();
}