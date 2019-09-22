#include<iostream>
#include<future>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<memory>
#include<string>
#include<map>
#include<functional>
#include<assert.h>
#include<stdio.h>

using namespace std;

class Stock{
public:
    string _key;
    double _price;
    Stock() = default;
    Stock(const string& key): _key(key){}
private:
};

class StockFactroy : public enable_shared_from_this<StockFactroy>{   // in memory.h enable_shared_from_this  get [this] ptr!!
public:
    shared_ptr<Stock> get(const string &key){
        shared_ptr<Stock> pStock;
        unique_lock<mutex> lock(_mutex);
        weak_ptr<Stock>& wkStock = _stocks[key];
        pStock = wkStock.lock();
        if(!pStock){
            pStock.reset(new Stock(key), 
                         bind(&StockFactroy::weakDeleteCallback, 
                              weak_ptr<StockFactroy>(shared_from_this()), 
                              std::placeholders::_1));
            wkStock = pStock;
        }
        return pStock;
    }
private:
    mutable mutex _mutex;   // caution!! keyword mutable 它能让本不能修改的变量或者
                            // 应该说const的变量在外面仍说const但是内部作出修改，类似局部修改const满足自己的要求
    map<string, weak_ptr<Stock>> _stocks;

    static void weakDeleteCallback(const weak_ptr<StockFactroy>& wkFactory, Stock *stock){
        shared_ptr<StockFactroy> factory(wkFactory.lock());
        if(factory){
            factory->removeStock(stock);
        }
        delete stock;
    }
    void removeStock(Stock *stock){
        if(stock){
            unique_lock<mutex> lock(_mutex);
            _stocks.erase(stock->_key); 
        }
    }
};
void testLongLiftFactory(){
    shared_ptr<StockFactroy> factory(new StockFactroy);
    {
        shared_ptr<Stock> stock1 = factory->get("NYSE:IBM");
        shared_ptr<Stock> stock2 = factory->get("NYSE:IBM");
        assert(stock1 == stock2) ;
    }
}
void print(string str){
    cout << str << endl;
}
int main(){
    testLongLiftFactory();
    // auto func = bind(print,  std::placeholders::_1);
    // func("string");
    return 0;
}