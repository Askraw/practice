#include<future>
#include<iostream>
#include<thread>
#include<chrono>
using namespace std;

int test(int a){
    for(int i=0; i<10; i++){
        this_thread::sleep_for(chrono::milliseconds(3000));
        cout << ++a << endl;
    }
    return a;
}

int main(){
    future<int> ft = async(test, 100);
    this_thread::sleep_for(chrono::milliseconds(3000));
    cout << "waiting result" << endl;
    cout << "get result:" << ft.get() << endl;

    return 0;
}