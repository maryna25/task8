#ifndef semaphore_h
#define semaphore_h

#include <iostream>

#include <mutex>
#include <condition_variable>
#include <exception>
#include <vector>

class Semaphore {
    int counter;
    std::mutex mutex;
    std::condition_variable condVar;
public:
    Semaphore(int count = 0);
    void wait(); // enter()
    void signal(); // leave()
};

#endif /* semaphore_h */