#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<thread>

void thread_task(){
    std::cout << "hello thread" << std::endl;
}

int main(int argc, char **argv){
    std::thread t(thread_task);
    t.join();

    return EXIT_SUCCESS;
}
