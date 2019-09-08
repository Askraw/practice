#include<iostream>
#include<thread>
#include<mutex>
using namespace std;

volatile int counter(0);
mutex mtx;

void attempt_10k_increate(){
    for(int i=0; i<10000; i++){
        // if(mtx.try_lock()){
        //     ++counter;
        //     mtx.unlock();
        // }
        mtx.lock();
        ++counter;
        mtx.unlock();
    }
}

int main(){
    thread threads[10];
    for(int i=0; i<10; i++){
        threads[i] = thread(attempt_10k_increate);
    }
    for(auto& th: threads) th.join();
    cout << counter << " successful  increases of the counter\n";
    return 0;

}