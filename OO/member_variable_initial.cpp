#include<string>
#include<iostream>
using namespace std;

// class define out of funtion(include main func) call defaulf construct func for default type like int
// but apple a in main() the price is random
class subapple{
    public:
        int mem;
        // subapple() = delete;
        subapple() = default;
        subapple(int i): mem(i){}
};

class apple{
    public:
        int price;
        string kind;
        // static int id; // need to initial
        const static int id = 10;
        subapple sa;
        void printApple();
};

void apple::printApple(){
    cout << "price: " << price << " kind: " << kind << endl;
    cout << "id: " << apple::id << endl;   // static member need add class::  to reference!!!
    cout << "sa.mem: " << sa.mem << endl;
    return ;
}
apple b;
int main(){
    apple a;
    a.printApple();

    int i = int();            // 0
    int *p = new int;         // 不确定值
    int *q = new int();       // 0
    cout << "i: " << i << endl;
    cout << "p: " << *p << endl;
    cout << "q: " << *q << endl;
    b.printApple();
    return 0;
}