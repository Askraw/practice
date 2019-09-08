#include<string>
#include<iostream>
using namespace std;

int main(){
    string *ptr = new string("hellow");
    delete ptr;
    cout << *ptr << endl;
    cout << ptr << endl;
}