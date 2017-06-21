#include <iostream>
#include <thread>
#include <string>
#include <chrono>

#include "semaphore.h"

using namespace std;

void func(string name, Semaphore &s) {
    s.wait();
    std::this_thread::sleep_for(chrono::seconds(1));
    cout << " Hi from " << name << endl;
    s.signal();
}

int main() {
    Semaphore sem(1);
    thread th1(func, "first", ref(sem));
    thread th2(func, "second", ref(sem));
    th1.join();
    th2.join();
    return 0;
}