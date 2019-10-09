#include <vector>
#include <iostream>

using namespace std;

// number_theory1 / 2 .cpp의 것 그대로임 //


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

int effective_mod_pow(int base, int exponent, int modulo){
    if(exponent==0) return 1%modulo;
    long long u = effective_mod_pow(base, exponent/2, modulo); //effective_pow 주석 참고
    u = (u*u)%modulo;
    if(exponent%2==1) u=(base*u)%modulo; //exponent/2에서 0.5잘렸을경우 보정
    return u;
}


// new //

int euler_totient_function(int n){
    //1 이상 n 이하 정수 중 n과 서로소인 정수 개수
    //eulor's phi function이라고도 부르기때문에..

    if(prime(n)) return n-1; //<-소수일땐 빠르게끝내나.. 소수가아닐땐 필요없는계산 또하게만든다.. 넣을까뺄까 고민

    vector<int> n_factors_vec = factors(n);
    int phi = 1; 
    int last_factor = n_factors_vec[0];
    int stage_mul = 1;
    for(int i=1; i<n_factors_vec.size(); i++){
        if(n_factors_vec[i]==last_factor) stage_mul*=n_factors_vec[i];
        else {
            phi *= (stage_mul * (last_factor-1));

            //next stage initialize
            last_factor = n_factors_vec[i];
            stage_mul = 1;
        }
    }
    phi *= (stage_mul * (last_factor-1));
    return phi;
}

int modular_multiplicative_inverse(int x, int modulo){
    return effective_mod_pow(x, euler_totient_function(modulo)-1, modulo);
}



//chinese remainder theorem. 
//x={coeff} mod {modulo}를 만족하는 x 중 하나 리턴 (수학적으로 x는 유일하지 않음)
int solve_mod_eqsystem(vector<pair<int,int>> coeff_modulo_pair_vec){
    int x=0;
    for(int i=0; i<coeff_modulo_pair_vec.size(); i++){
        int midterm = 1;
        for(int j=0; j<coeff_modulo_pair_vec.size(); j++){ //midterm Xi 계산
            if(i==j) continue;
            midterm *= coeff_modulo_pair_vec[j].second;
        }
        x += (coeff_modulo_pair_vec[i].first * midterm * modular_multiplicative_inverse(midterm, coeff_modulo_pair_vec[i].second));
    }
    return x;
}


int main(){
    cout << "<Euler's phi function>\nphi(10)? " << euler_totient_function(7) << "(true:6)\n";
    cout << "phi(10)? " << euler_totient_function(10) << "(true:4)\n";

    cout << "<multiplicative inverse on Zm>\ninv_(4) on Z5? " << modular_multiplicative_inverse(4, 5) << "(true:4)\n";
    cout << "inv_(3) on Z7? " << modular_multiplicative_inverse(3, 7) << "(true:5)\n";


    //chinese remainder theorem example(p188)
    cout << "<chinese remainder theorem>\nsolution of this system? : x=3mod5 & x=4mod7 & x=2mod3\n";
    vector<pair<int,int>> ex_modulo_eq_system = {{3,5}, {4,7}, {2,3}};
    int solution = solve_mod_eqsystem(ex_modulo_eq_system);
    cout << "solution : x=" << solution << " (true:263)\n";
    

}