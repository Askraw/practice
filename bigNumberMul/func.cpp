#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<cstring>
#include<math.h>
using namespace std;

string addBinary(string a, string b, int mode){
    
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());
    string ans = "";
    int c = 0;
    int in = 0;
    while(in<a.length() || in<b.length()){
        int num = (in<a.length()?a[in]-'0':0) + (in<b.length()?b[in]-'0':0)  + c;
        // cout << "num: " << num << endl;
        c = num/mode;
        num = num%mode;
        ans += (num+'0');
        // cout << "cur: " << ans << endl;
        in++;
    }
    if(c == 1) ans += '1';
    reverse(ans.begin(), ans.end());
    return ans;
}

void completeStr(string &a, string &b){
    long long len1 = a.length();
    long long len2 = b.length();
    if(len1 == len2) return ;
    if(len1 < len2){
        for(long long i=len1; i<len2; i++) a = '0'+a;
    } else{
        for(long long i=len2; i<len1; i++) b = '0'+b;
    }
    return ;
}

string TtoK(long long num, int mode){
    string res = "";
    int rem = 0;
    long long  div = num;
    while(div!=0){
        rem = div%mode;
        div = div/mode;
        res += (rem+'0');
    }
    reverse(res.begin(), res.end());
    return res;
}
long long karatsuba(string a, string b, int mode){
    if (mode==10){
        return stoll(a)*stoll(b);
    }
    long long len = max(a.length(), b.length());
    completeStr(a, b);
    if(len == 0) return 0;
    if(len == 1) return (a[0]-'0')*(b[0]-'0');

    long long mid = len/2;
    long long left = len-mid;
    string a1 = a.substr(0, mid);
    string a2 = a.substr(mid, left);
    string b1 = b.substr(0, mid);
    string b2 = b.substr(mid, left);

    long long x1 = karatsuba(a1, b1, mode);
    long long x2 =  karatsuba(a2, b2, mode);
    long long x3 = karatsuba(addBinary(a1, a2, mode), addBinary(b1, b2, mode), mode);

    // return (1<<(2 * left)) * x1 + (1<<(left)) * (x3 - x1 - x2) + x2;
    return pow(mode, 2*left)*x1+pow(mode, left)*(x3-x1-x2)+x2;
}

int main(){
    string a;
    string b;
    int c;
    cin >> a >> b >> c;
    
    cout << addBinary(a, b, c) << endl;
    if(c==10)
        cout << karatsuba(a, b, c) << endl;
    else
        cout << TtoK(karatsuba(a, b, c), c) << endl;
    
    return 0;
}