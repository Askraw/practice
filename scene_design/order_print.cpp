#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<future>
#include<condition_variable>
using namespace std;

// scene description: leetcode 1116 
// input n, output 010203.....0n  

// key point thread call member function need add argument obj's addr, which is "this" in class like line75 76 77
class ZeroEvenOdd{
    private:
        int n;
        condition_variable cv;
        mutex mtx;
        int mark;
        int tmp;
    public:
    ZeroEvenOdd(int n){
        this->n = n;
        mark = 0;
        tmp = 0;
        bool isOdd = n%2;
    }
    void zero(function<void(int)> printNum){
        while(1){
            unique_lock<mutex> lck(mtx);
            cv.wait(lck, [&]()->bool{return mark==0||tmp==n;});
            if(tmp==n) return;
            printNum(0);
            tmp++;
            mark = tmp%2+1;
            cv.notify_all();
        }
    }
    void even(function<void(int)> printNum){
        // unique_lock<mutex> lck(mtx);
        while(1){
            unique_lock<mutex> lck(mtx);
            cv.wait(lck, [&]()->bool{return mark==1||tmp==n;});
            if(tmp==n) {
                if(tmp%2==0 && tmp!=0) printNum(tmp);
                return;
                }
            printNum(tmp);
            mark = 0;
            cv.notify_all();
        }
    }
    void odd(function<void(int)> printNum){
        // unique_lock<mutex> lck(mtx);
        while(1){
            unique_lock<mutex> lck(mtx);
            cv.wait(lck, [&]()->bool{return mark==2||tmp==n;});
            if(tmp==n) {
                if(tmp%2==1) printNum(tmp);
                return;
                }
            printNum(tmp);
            mark = 0;
            cv.notify_all();
        }
    }
};

int main(){
    auto func = [](int x){ cout<<x<<endl;};
    int n;
    cout << "input n: ";
    cin >> n;
    ZeroEvenOdd obj(n);
    vector<thread> vec;
    vec.push_back(thread(&ZeroEvenOdd::zero, &obj, func));
    vec.push_back(thread(&ZeroEvenOdd::even, &obj, func));
    vec.push_back(thread(&ZeroEvenOdd::odd, &obj, func));
    for(auto& th : vec) th.join();
    return 0;
}