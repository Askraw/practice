#include<iostream>
#include<future>
#include<chrono>
using namespace std;

// We know three ways of associating a task with a std::future. They are std::async, std::packaged_task and std::promise.
void printOK(){
    cout << "async execute OK\n" << flush;
}

void threadFun(int i, promise<int>& pro){
    this_thread::sleep_for(chrono::milliseconds(1000*i));
    cout << "thread " << i << " starting\n ";
    if(i == 9){
        pro.set_value(10);
    }
}
void asyncFun(future<void>& fut){
    fut.get();
    return;
}
// wait_for 的future对象如果说async就不会阻塞 timeout  输出的说deferred 延迟！
// By using std::async you cannot run your task on a specific thread anymore, where std::packaged_task can be moved to other threads.
//  async    人如其名 async 就是 get的是哈异步调用这个async绑定的func 而 task需要手动去invoke
int main(){
    future<void> fut = async(printOK);
    thread threads[10];
    promise<int> num;
    future<int> fut2 = num.get_future();
    for(int i=0; i<10; i++){
        threads[i] = thread(threadFun, i, ref(num));
    }
    std::chrono::milliseconds span (1100);
    // if shared state is not ready block this thread  until its ready
    // fut2.wait();
    while(fut2.wait_for(span)==std::future_status::timeout)
        cout << "wait." << flush;
    cout << "future val: " << fut2.get() << endl;
    for(thread& th : threads) th.join();
    fut.get();
    // thread t1(ref(fut));
    // t1.join();
    return 0;
}