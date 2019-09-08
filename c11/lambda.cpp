#include<iostream>
using namespace std;    

// ---------------------------------------------------------------------------------------------------------
//
// [capture](parameters) mutable ->return-type{statement}
// if lambda function dont have return value, [capture](parameters) mutable {statement}
//
// ---------------------------------------------------------------------------------------------------------
//
// lambda function is always const function, so it cannot change non-static member value(pass-by-value) 
// for pass-by-reference, change member's value, in fact, the reference is not changed, thus its ok
//
// ---------------------------------------------------------------------------------------------------------
//
// [] include params the lambda function catches. such as = means all Capture all variables in the parent scope  pass-by-value
// & means all Capture all variables in the parent scope  pass-by-reference
// and it can direct single or multiple variables, but when '=' in "[]" you can't add any single variable pass-by-value, neither nor '&'
//
// ----------------------------------------------------------------------------------------------------------

int main(){
    int val = 0;
    // auto const_val_lambda = [=](){val = 3;};  // expression must be a modifiable lvalue
    auto mutable_val_lambda = [=]() mutable{val = 3;}; // mutable make it const function can change mutable type value
    auto mutable_ref_lambda = [&]() mutable{val = 5;}; // pass-by-reference is okay

    int j = 10;            
    auto by_val_lambda = [=]()->int{ return j + 1; };
    auto by_ref_lambda = [&]()->int{ return j + 1; };
    cout<<"by_val_lambda: "<<by_val_lambda()<<endl;
    cout<<"by_ref_lambda: "<<by_ref_lambda()<<endl;
                           
    ++j;                   
    cout<<"by_val_lambda: "<<by_val_lambda()<<endl;  // expect 11 j was regarded as a constant once it was established (same name as parent scope j, but it is a constant in its scope)
    cout<<"by_ref_lambda: "<<by_ref_lambda()<<endl;  // expect
                           
    return 0;              
}