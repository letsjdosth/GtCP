#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

void print_vector(vector<int> vec){
    for(auto u : vec){
        cout.width(3); cout.fill(' ');
        cout << u;
    }
}

bool prime(int n){
    if(n<2) return false;
    for(int x=2; x*x<=n; x++){ //sqrt(n) 이하만 확인해보면 된다
        if(n%x==0) return false;
    }
    return true;
}

vector<int> factors(int n){
    vector<int> factors_vec;
    for(int x=2; x*x<=n; x++){
        while(n%x==0){ //같은 x로 여러번 나눠질경우 계속 나눠야하기 때문에 while 사용함
            factors_vec.push_back(x);
            n/=x;
        }
    }
    if(n>1) factors_vec.push_back(n); //자기가 소수일때를 위해?
    return factors_vec;
}


double prime_counting_function(int n){
    //n이하 소수개수에 대한 근사값
    return n/log(n);
}

int num_divisors(int n){
    //약수 개수
    vector<int> factors_n = factors(n);
    int result_num = 1;
    int last_factor = 1;
    int exponent = 1;

    for(int i=0; i<factors_n.size(); i++){
        if(factors_n[i]==last_factor){
            exponent++;
            continue;
        }
        result_num *= exponent+1;
        
        //초기화
        last_factor = factors_n[i];
        exponent = 1;
    }
    return result_num;
}

int sum_divisors(int n){
    //모든 약수의 합
    vector<int> factors_n = factors(n);
    int last_factor = factors_n[0];
    int stage_val = factors_n[0];
    double result_sum = 1;

    for(int i=1; i<factors_n.size(); i++){ //음 루프구조가맘에안든다. 지금은 i-1번째를 처리하게되어있음
        if(factors_n[i]==last_factor && i!=factors_n.size()-1){
            stage_val *= factors_n[i];
            continue;
        }

        //이번인수가 전 인수랑 다르면 전 인수에대해 처리하자
        result_sum *= ((stage_val*last_factor - 1)/(last_factor-1)) ;
        
        //이번인수로 다음iter 위해 세팅
        last_factor = factors_n[i];
        stage_val= factors_n[i];
    }
    result_sum *= ((stage_val*last_factor -1)/(last_factor-1));
    return (int)result_sum;
}

//O(nlogn)
vector<int> sieve_of_eratosthenes(int n){
    //vector idx가 소수이면 0, 아니면 1인 벡터를 반환(거꾸로임에 주의!)(에라토스테네스의 체 이용)
    vector<int> sieve(n+1); //bool로해도되지만..
    sieve[0]=1; sieve[1]=1; //0, 1자리는 그냥 1 넣자 (idx 당기느니 그냥 1 넣기로 함)

    for(int x=2; x<=n; x++){
        if(sieve[x]) continue;
        for(int u=2*x; u<=n; u+=x){//x가 소수면 x의 배수 죄다 1 넣자
            sieve[u] =1;
        }
    }
    return sieve;

}


int main(){
    cout << "prime? 7:" << prime(7) << " (true:1)\n";
    cout << "prime? 35:" << prime(35) << " (true:0)\n";
    cout << "factor of 24? "; print_vector(factors(24)); cout << "\n";
    cout << "factor of 34? "; print_vector(factors(34)); cout << "\n";
    cout << "factor of 37? "; print_vector(factors(37)); cout << "\n";

    cout << "approx number of prime number under 100? " << prime_counting_function(100) << "\n";

    cout << "number of divisor of 12? " << num_divisors(12) << " (true:6)\n";
    cout << "number of divisor of 35? " << num_divisors(35) << " (true:4)\n";

    cout << "sum of divisor of 12? " << sum_divisors(12) << " (true:28)\n";
    cout << "sum of divisor of 35? " << sum_divisors(35) << " (true:48)\n";

    cout << "Sieve of Eratosthenes:(!prm=0 if prime, !prm=1 if not prime) \nnum  :";
    for(int i=0; i<=20; i++){
        cout.width(3); cout.fill(' ');
        cout << i;
    } 
    cout << "\n!prm :"; print_vector(sieve_of_eratosthenes(20)); cout << endl;

}

