#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<future>
#include<condition_variable>
#include<chrono>
#include<functional>
using namespace std;

static const int maxItemRepositorySize = 10;
static const int maxItemToProduce = 100;

typedef struct {
    int item_buf[maxItemRepositorySize]; // max item in repo, similar to threads pool
    size_t read_pos;
    size_t write_pos;
    mutex mtx;
    condition_variable repo_not_full;
    condition_variable repo_not_empty;
}ItemRepository;

ItemRepository itemRepo; 

void ProduceItem(ItemRepository& iRepo, int item){
    unique_lock<mutex> lock(iRepo.mtx);
    while(((iRepo.write_pos+1) % maxItemRepositorySize) == iRepo.read_pos){
        cout << "Producers is Waiting for an empty slow ...\n";
        (iRepo.repo_not_full).wait(lock);
    }
    (iRepo.item_buf)[iRepo.write_pos] = item;
    (iRepo.write_pos)++;

    if(iRepo.write_pos == maxItemRepositorySize)
        iRepo.write_pos = 0;
    (iRepo.repo_not_empty).notify_all();
    lock.unlock();
}

int ConsumeItem(ItemRepository& iRepo){
    int data;
    unique_lock<mutex> lock(iRepo.mtx);
    while(iRepo.write_pos == iRepo.read_pos){
        cout << "Consumer is waiting for items ...\n";
        (iRepo.repo_not_empty).wait(lock);
    }
    data = (iRepo.item_buf)[iRepo.read_pos];
    (iRepo.read_pos)++;

    if(iRepo.read_pos >= maxItemRepositorySize)
        iRepo.read_pos = 0;
    (iRepo.repo_not_full).notify_all();
    lock.unlock();

    return data;
}

void ProduceTask(){
    for(int i=1; i<=maxItemRepositorySize; i++){
        cout << "Produce the " << i << "^th item..." << endl;
        ProduceItem(ref(itemRepo), i);
    }
}

void ConsumeTask(){
    static int cnt = 0;
    while(1){
        // this_thread::sleep_for(chrono::milliseconds(1000));
        int item = ConsumeItem(ref(itemRepo));
        cout << "Counsume the " << item << "^th item" << endl;
        if(++cnt == maxItemRepositorySize) break;
    }
}

// initilize  the ItemRepository
void initItemRepository(ItemRepository& iRepo){
     iRepo.write_pos = 0; 
     iRepo.read_pos = 0; 
}

int main(){
    
    initItemRepository(ref(itemRepo));
    thread produce(ProduceTask);
    thread consume(ConsumeTask);
    produce.join();
    consume.join();
}
