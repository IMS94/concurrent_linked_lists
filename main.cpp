#include <iostream>
#include <random>
#include <set>
#include <algorithm>
#include "linked_list.cpp"

#define RANGE_FROM 0
#define RANGE_TO 65535
#define N 1000

using namespace std;

/**
 * Configures the required numbers for the performance test
 * @param numbers The vector to which the random numbers will be copied
 */
void configure_elements(vector<unsigned short> *numbers) {
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
    copy(set.begin(), set.end(), numbers->begin());
}

int main() {
    vector<unsigned short> numbers(N);
    cout << "Starting configuration" << endl;
    configure_elements(&numbers);

    default_random_engine random_engine;
    cout << "Shuffling numbers in the vector" << endl;
    shuffle(numbers.begin(), numbers.end(), random_engine);

    cout << "Populating Linked List" << endl;
    linked_list list;
    for (unsigned short i : numbers) {
        cout << "Adding " << i << endl;
        list.insert(i);
    }
}