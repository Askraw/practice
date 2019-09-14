#include<iostream>
#include<future>
#include<chrono>
using namespace std;

void task_print(){
    cout << "task_print staring, plz waiting...\n";
    this_thread::sleep_for(chrono::milliseconds(500));
    cout << "thread PACKAGED_TASK id: " << this_thread::get_id() << endl;
}
void async_print(string str){
    cout << str << " async_print staring, plz waiting...\n";
    this_thread::sleep_for(chrono::milliseconds(2000));
    cout << " thread " << str << " id: " << this_thread::get_id() << endl;
    return ;
}
int main(){
    cout << " thread MAIN id: " << this_thread::get_id() << endl;
    packaged_task<void()> task(task_print); 
    future<void> fut = task.get_future();                                   // invoke and run in this thread unless it is bind to  ohter thread
    future<void> fut3 = async(async_print, "launch::deferred");             //  kind of call in this thread
    future<void> fut2 = async(launch::async, async_print, "launch::async"); // run in a new thread immediately
    task();
    fut.get();
    fut3.get();
    return 0;
}