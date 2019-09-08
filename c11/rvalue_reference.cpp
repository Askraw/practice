#include<string>
#include<iostream>
using namespace std;

class myClass{
public:
    myClass(const string &_str){
        str = _str;
        cout << "string construct " << endl;
    }
    myClass(const myClass &_myClass){
        str = _myClass.str;
        cout << "copy construct" << endl;
    }
    myClass(const myClass &&_myClass){
        str  = std::move(_myClass.str);
        cout << "rvalue reference effected" << endl;
    }
    ~myClass(){
        cout << str << "is being delete!" << endl;
    }
private:
    string str;
};

myClass func(string s){
    myClass m(s);
    return m;
}

int main(){
    // myClass t = func("hello,world!");
    myClass t("t");
    myClass t2 = myClass("t2");
    myClass t3 = func("t3");
    return 0;
}