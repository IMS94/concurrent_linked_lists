#include <iostream>
#include <random>
#include <set>
#include <algorithm>

#define RANGE_FROM 0
#define RANGE_TO 65535
#define N 1000

using namespace std;

void configure(vector<unsigned short> *numbers) {
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

    default_random_engine random_engine;
    cout << "Shuffling numbers in the vector" << endl;
    shuffle(numbers->begin(), numbers->end(), random_engine);
}


int main() {
    vector<unsigned short> numbers(N);
    cout << "Starting configuration" << endl;
    configure(&numbers);

    for (unsigned short i : numbers) {
        cout << i << " ";
    }
}