#define CATCH_CONFIG_MAIN
// This tells Catch to provide a main() - only do this in one cpp file

#include "semaphore.h"

#include <thread>
#include <string>
#include <chrono>
#include <catch.hpp>
#include <vector>

using namespace std;

template <typename T>
void sum(T a, T b, T& res, Semaphore &s) {
//    cout << "1 enter" << endl;
    s.wait();
//    cout << "1 start" << endl;
    std::this_thread::sleep_for(std::chrono::seconds(4));
    res = a + b;
//    cout << "2 should start" << endl;
    s.signal();
}

template <typename T>
void multiply(T a, T b, T& res, Semaphore &s) {
//    cout << "2 enter" << endl;
    s.wait();
//    cout << "2 start" << endl;
    res = a * b;
    s.signal();
}

SCENARIO("Semaphore Class Testing") {
    GIVEN("Semaphore") {
        Semaphore semaphore(1);
        
        WHEN("Two threads initialised") {
            int result = 0;
            vector<thread> threads(2);
            
            threads[0] = thread(sum<int>, 10, 10, ref(result), ref(semaphore));
            // threads[0] should enter first
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            threads[1] = thread(multiply<int>, 100, 100, ref(result), ref(semaphore));
            
            threads[0].join();
            threads[1].join();
            THEN("Result should be equal to 100 * 100 ~ 10000") {
                REQUIRE(result == 10000);
            }
        }
        
        WHEN("Two threads initialised") {
            string result;
            vector<thread> threads(2);
            
            threads[1] = thread([&](string& str) {
                semaphore.wait();
                str += "First Function -> ";
                semaphore.signal();
            }, ref(result));
            
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
            
            threads[0] = thread([&](string& str) {
                semaphore.wait();
                str += "Second Function";
                semaphore.signal();
            }, ref(result));
            
            threads[0].join();
            threads[1].join();
            
            THEN("Result should be equal to First Function -> Second Function") {
                REQUIRE(result == "First Function -> Second Function");
            }
        }
    }
}