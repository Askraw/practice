#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<future>
#include<condition_variable>
#include<chrono>
#include<functional>
using namespace std;

// scene: order and cook in restaurant
// use async  packaged_task promise
class Food
{
private:
    /* data */
    string m_str;
public:
    Food(string str): m_str(str){};
    Food(Food&& _food){
        m_str = move(_food.m_str);
    }
    string getName() const{
        return m_str;
    }
    ~Food(){};
};

void cook(const string str, promise<Food>& prom){
    Food food(str);
    prom.set_value(move(food));
    // prom.set_value(food);   ERROR: this method call Food::Food(const Food&)
}

Food cook2(const string str){
    Food food(str);
    return food;
}

int main(){
    promise<Food> prom;
    future<Food> fut = prom.get_future();
    thread th(cook, "twice cooked pork", ref(prom));
    Food food = fut.get();
    cout << food.getName() << " has been finished, enjoy it!\n";
    th.join();
    packaged_task<Food(string)> cooker(cook2);  // task<return value(parameters)> !!
    future<Food> fut2 = cooker.get_future();
    // thread th2(move(cooker), "twice cooked pork2");
    thread th2(ref(cooker), "twice cooked pork2");                       // each one is okay in this sample
    Food food2 = fut2.get();
    cout << food2.getName() << " has been finished, enjoy it!\n";
    th2.join();
    future<Food> fut3 = async(launch::async, bind(cook2, "twice cooked pork3"));
    cout << fut3.get().getName() << " has been finished, enjoy it!\n";
    return 0;
}



