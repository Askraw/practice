#include <iostream>
#include <utility>
#include <thread>
#include <chrono>
#include <functional>
#include <atomic>

using namespace std;
void f1(int n){
    cout << "thread " << n <<"executing\n";
    this_thread::sleep_for(chrono::milliseconds(10));
}

void f2(int& n){
    for(int i=0; i<5; i++){
        cout << "thread 2 exectuing\n";
        ++n;
        this_thread::sleep_for(chrono::milliseconds(10));
    }
}

int main(){
    int n = 0;
    thread t1;
    thread t2(f1, n+1);
    thread t3(f2, ref(n));
    thread t4(std::move(t3)); // t3 has been deleted

    t2.join();
    // t3.join();
    t4.join();
    cout << "final value of n is " << n << endl;
    return 0;
}