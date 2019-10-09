#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

//O(logn). a,b의 최대공약수. 유클리드 알고리즘
int gcd(int a, int b){
    if(b==0) return a;
    return gcd(b, a%b);
}

//ax+by=gcd(a,b)를 만족하는 <x,y,gcd(a,b)>
tuple<int,int,int> extended_gcd(int a, int b){
    if(b==0){
        return {1,0,a};
    } else {
        int x,y,g;
        tie(x,y,g) = extended_gcd(b, a%b);
        return {y, x-(a/b)*y, g}; //함수선언부의 return 자료형이 int라서 (a/b)에서 무언가 소수점이 남으면 잘린다.
    }
}

long long int effective_pow(int base, int exponent){
    if(exponent==0) return 1;
    long long u = effective_pow(base, exponent/2); //함수선언부의 arg 자료형이 int라서 exponent/2가 0.5가 붙어있을경우 잘려서 들어간다
    //64bit processor-os, 8byte int. -9,223,372,036,854,775,808~9,223,372,036,854,775,807
    u = u*u;
    if(exponent%2==1) u*=base; //exponent/2에서 0.5잘렸을경우 보정
    return u;
}

int effective_mod_pow(int base, int exponent, int modulo){
    if(exponent==0) return 1%modulo;
    long long u = effective_mod_pow(base, exponent/2, modulo); //effective_pow 주석 참고
    u = (u*u)%modulo;
    if(exponent%2==1) u=(base*u)%modulo; //exponent/2에서 0.5잘렸을경우 보정
    return u;
}

//ax+by=c를 만족하는 x,y 정수쌍 중 하나 리턴
pair<int,int> solve_diophantine_eq(int a, int b, int c){
    int gcd_of_a_b = gcd(a,b);
    if(c%gcd_of_a_b!=0){
        cout << "no solution! (input: "<<a<<"x+"<<b<<"y="<<c<<")"<<endl;
        return {0,0}; //음.. 예외처리할수있는 에러를 냈으면좋겠음(c++에서 예외 어케다루냐?)
    } else {
        int x,y,g;
        int multiplier = c/gcd_of_a_b;
        tie(x,y,g) = extended_gcd(a, b);
        return {x*multiplier, y*multiplier};
    }
}



int main(){
    cout << "<gcd>\ngcd(30,12)? : " << gcd(30,12) << " (true: 6)\n";
    cout << "gcd(35,42)? : " << gcd(35,42) << " (true: 7)\n";


    int temp_x, temp_y, temp_gcd;
    cout << "<extended gcd>\nx,y satisfying 8x+30y=gcd(30,12)? : ";
    tie(temp_x, temp_y, temp_gcd) = extended_gcd(30,12);
    cout << "x: " << temp_x << " y: " << temp_y << " gcd: " << temp_gcd << " --> 30*"<< temp_x << "+12*" << temp_y << "=" << temp_gcd << "\n";
    cout << "x,y satisfying 8x+30y=gcd(8,30)? : ";
    tie(temp_x, temp_y, temp_gcd) = extended_gcd(8,30);
    cout << "x: " << temp_x << " y: " << temp_y << " gcd: " << temp_gcd << " --> 8*"<< temp_x << "+30*" << temp_y << "=" << temp_gcd << "\n";

    cout <<"<pow>\n2^39? " << effective_pow(2, 39) << "\n";
    cout <<"3^6? " << effective_pow(3, 6) << "\n";

    cout <<"<pow&mod>\n2^39 mod 3? " << effective_mod_pow(2, 39, 3) << "\n";
    cout <<"3^6 mod 7? " << effective_mod_pow(3, 6, 7) << "\n";

    
    //Diophantine eq. p 186
    cout << "<Diophantine equation>\n39x+15y=12. x, y? : ";
    pair<int,int> solution = solve_diophantine_eq(39, 15, 12);
    cout << solution.first <<", " << solution.second << "\n";
    cout << "verify: 39*" << solution.first <<"+15*" << solution.second << "=" << 39*solution.first+15*solution.second << "\n";

    cout << "<Diophantine equation>\n39x+15y=11. x, y? : ";
    pair<int,int> solution2 = solve_diophantine_eq(39, 15, 11);
}