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
static const int maxItemToProduce = 20;

typedef struct{
    int item_buf[maxItemRepositorySize];
    size_t write_pos;
    size_t read_pos;
    size_t item_produce;
    size_t item_consume;
    mutex mtx;
    mutex p_cnt_mtx;
    mutex c_cnt_mtx;
    condition_variable repo_not_empty;
    condition_variable repo_not_full;
}ItemRepository;

void initItemRepo(ItemRepository& iRepo){
    iRepo.write_pos = 0;
    iRepo.read_pos = 0;
    iRepo.item_produce = maxItemToProduce;
    iRepo.item_consume = maxItemToProduce;
}
void produceItem(ItemRepository& iRepo, int item){
    unique_lock<mutex> ulk(iRepo.mtx);
    (iRepo.repo_not_full).wait(ulk, [&iRepo]()->bool{ 
        cout << "Producers is Waiting for an empty slow ...\n";
        return iRepo.read_pos!= 1+iRepo.write_pos;
        });
    (iRepo.item_buf)[iRepo.write_pos++] = item;
    if(iRepo.write_pos == maxItemRepositorySize)
        iRepo.write_pos =  0;
    ulk.unlock();
    (iRepo.repo_not_empty).notify_all();
}

int consumeItem(ItemRepository& iRepo){
    unique_lock<mutex> ulk(iRepo.mtx);
    (iRepo.repo_not_empty).wait(ulk, [&iRepo]()->bool{ 
        cout << "Consumer is waiting for items ...\n";
        return iRepo.read_pos != iRepo.write_pos;
        });
    int res = (iRepo.item_buf)[iRepo.read_pos++];
    if(iRepo.read_pos == maxItemRepositorySize)
        iRepo.read_pos = 0;
    ulk.unlock();
    (iRepo.repo_not_full).notify_all();
    return res;
}

void produce(ItemRepository& iRepo){
    while(1){
        this_thread::sleep_for(chrono::milliseconds(1000));  // simulation for produce
        unique_lock<mutex> plk(iRepo.p_cnt_mtx);
        if(iRepo.item_produce <= 0) return;

        produceItem(ref(iRepo), maxItemToProduce-iRepo.item_produce);
        cout << "Produce the " << maxItemToProduce-iRepo.item_produce << "^th item..." << endl;
        iRepo.item_produce--;
        // cout << "now irepo.item_produce: " << iRepo.item_produce << endl;
    }
}

void  consume(ItemRepository& iRepo){
    while(1){
        this_thread::sleep_for(chrono::milliseconds(500)); // simulation for cunsume
        unique_lock<mutex>  clk(iRepo.c_cnt_mtx);
        if(iRepo.item_consume <= 0) return;

        int item = consumeItem(ref(iRepo));
        cout << "Consume the " << item << "^th item..." << endl;
        iRepo.item_consume--;
    }
}

int main(){
    ItemRepository iRepo;
    initItemRepo(ref(iRepo));
    vector<thread> ths;
    ths.emplace_back(produce, ref(iRepo));
    ths.emplace_back(produce, ref(iRepo));
    ths.emplace_back(produce, ref(iRepo));
    ths.emplace_back(consume, ref(iRepo));
    ths.emplace_back(consume, ref(iRepo));
    ths.emplace_back(consume, ref(iRepo));
    ths.emplace_back(consume, ref(iRepo));
    ths.emplace_back(consume, ref(iRepo));
    for(auto& th : ths)
        th.join();
    return 0;
}