#ifndef LAB_2_RW_LOCK_TEST_H
#define LAB_2_RW_LOCK_TEST_H

#include "test.h"
#include <pthread.h>
#include <unistd.h>

/**
 * Struct to be used to pass data to the thread functions.
 */
struct rw_lock_thread_context {
    int thread_count;
    int per_thread_op_count;
    unsigned short *random_nums;
    int random_num_count = 100;
    int start_index;
    vector<Op> *execution_plan;
    linked_list *list;
    pthread_rwlock_t *rw_lock;
};

/**
 * Test to test the performance of the Linked List with one mutex as the lock
 */
class rw_lock_test : public test {

private:
    pthread_rwlock_t rw_lock;
    int thread_count;
    int per_thread_op_count;
    pthread_t *threads;
    pthread_attr_t pthread_attr;
    unsigned short *random_nums;
    int random_num_count = 100;

    /**
     * Function to be called by pthreads.
     */
    static void *thread_func(void *c) {
        rw_lock_thread_context *cntx = (rw_lock_thread_context *) c;
        int start_index = cntx->start_index;
        int end_index = start_index + cntx->per_thread_op_count;

        int op_count = 0;
        cout << "Execution plan got ops from " << start_index << " to " << end_index << endl;
        for (int i = start_index; i < end_index; i++) {
            switch ((*cntx->execution_plan)[i]) {
                case MEMBER:
                    pthread_rwlock_rdlock(cntx->rw_lock);
                    cntx->list->member(cntx->random_nums[op_count % cntx->random_num_count]);
                    pthread_rwlock_unlock(cntx->rw_lock);
                    break;
                case DELETE:
                    pthread_rwlock_wrlock(cntx->rw_lock);
                    cntx->list->remove(cntx->random_nums[op_count % cntx->random_num_count]);
                    pthread_rwlock_unlock(cntx->rw_lock);
                    break;
                case INSERT:
                    pthread_rwlock_wrlock(cntx->rw_lock);
                    cntx->list->insert(cntx->random_nums[op_count % cntx->random_num_count]);
                    pthread_rwlock_unlock(cntx->rw_lock);
                    break;
            }
            op_count++;
        }
        cout << "Execution completed (Ops from : " << start_index << " to :" << end_index << ")" << endl;

        delete (cntx);
        pthread_exit(NULL);
    }

protected:

    void run() {

        cout << "Creating " << thread_count << " pthreads" << endl;
        for (int i = 0; i < thread_count; i++) {
            int start_index = per_thread_op_count * i;

            rw_lock_thread_context *c = new rw_lock_thread_context;
            c->random_num_count = random_num_count;
            c->per_thread_op_count = per_thread_op_count;
            c->thread_count = thread_count;
            c->random_nums = random_nums;
            c->start_index = start_index;
            c->execution_plan = &execution_plan;
            c->list = list;
            c->rw_lock = &rw_lock;

            pthread_create(&(threads[i]), &pthread_attr, thread_func, (void *) c);
        }

        for (int j = 0; j < thread_count; ++j) {
            cout << "Waiting for thread " << j << " to finish" << endl;

            void *status;
            int rc = pthread_join(threads[j], &status);

            if (rc) {
                cout << "Error:unable to join," << rc << endl;
                exit(-1);
            }

            cout << "Completed thread id :" << j << ".  exiting with status :" << status << endl;
        }
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

        threads = new pthread_t[thread_count];
        pthread_rwlock_init(&rw_lock, NULL);
    }

    void teardown_test() {
        test::teardown_test();
        delete (random_nums);
        delete (threads);
        pthread_rwlock_destroy(&rw_lock);
    }

public:
    rw_lock_test(int n, int m, unsigned short iter, float member_percentage, float insert_percentage,
                 float delete_percentage, int thread_count) : test(n, m, iter, member_percentage, insert_percentage,
                                                                   delete_percentage) {

        this->thread_count = thread_count;
        per_thread_op_count = m / thread_count;
        cout << "Creating read write lock test" << endl;

        random_num_count = insert_ops > 100 ? insert_ops : 100;

        // Initialize and set thread joinable
        pthread_attr_init(&pthread_attr);
        pthread_attr_setdetachstate(&pthread_attr, PTHREAD_CREATE_JOINABLE);
    }

};

#endif //LAB_2_RW_LOCK_TEST_H
