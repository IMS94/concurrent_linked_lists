#include <iostream>
#include "serial_test.h"
#include "mutex_test.h"
#include "rw_lock_test.h"

using namespace std;

int main(int argc, char **argv) {
    cout << "Running the serial test" << endl;
    serial_test test(1000, 10000, 1, 0.8, 0.1, 0.1);
    vector<float> serial_results = test.run_test();

    for (float a:serial_results) {
        cout << a << " ";
    }

    cout << "\n\n\n" << endl;

    cout << "Running the mutex test" << endl;
    mutex_test mutex_test(1000, 10000, 1, 0.8, 0.1, 0.1, 4);
    vector<float> mutex_results = mutex_test.run_test();

    for (float a:mutex_results) {
        cout << a << " ";
    }

    cout << "\n\n\n" << endl;

    cout << "Running the read write lock test" << endl;
    rw_lock_test rw_lock_test(1000, 10000, 1, 0.8, 0.1, 0.1, 4);
    vector<float> rw_lock_results = rw_lock_test.run_test();

    for (float a:rw_lock_results) {
        cout << a << " ";
    }
	
	//For calculate mean,std and sample size 
	cout << "\n\n" << endl;
    double sum = std::accumulate(mutex_results.begin(), mutex_results.end(), 0.0);
    double mean = sum / mutex_results.size();

    double sq_sum = std::inner_product(mutex_results.begin(), mutex_results.end(), mutex_results.begin(), 0.0);
    double stdev = std::sqrt(sq_sum / mutex_results.size() - mean * mean);
    double n= std::pow(((100*1.96*stdev)/(5*mean)),2);
    cout <<" Mutex mean : "<< mean*1000 << endl;
    cout <<"std : "<< stdev*1000 << endl;
    cout << "n : " << n <<endl;
}