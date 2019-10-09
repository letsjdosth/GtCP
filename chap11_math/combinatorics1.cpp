#include <iostream>
#include <time.h>

using namespace std;

//binomial coefficient. nCk, or (n, k) 
long long int combination_rec(int n, int k){
    if(k==0) return 1;
    if(n==k) return 1;
    return combination_rec(n-1, k-1) + combination_rec(n-1, k);
}

long long int factorial(int n){
    if (n==0 || n==1) return 1;
    return n*factorial(n-1);
}

long long int combination_direct(int n, int k){
    long long int denominator = factorial(n);
    long long int quotient = factorial(k);
    long long int quotient2 = factorial(n-k);
    return (denominator/quotient2)/quotient; 
    //걍 식을 바로 리턴에 집어넣는것보다.. 이렇게 쓴다고 해서 overflow가 덜 날까?
}

//오버플로우 대책: 그냥 손으로 계산하는정도까지만...for를돌리자 (n부터 k혹은n-k큰쪽번까지곱하고 나누기)

//카탈란 수(Catalan number) Cn :
//1. 여는괄호 닫는괄호 각각 n개로 구성된 올바른 괄호 문자열 수 
//2. n노드 이진트리 수 
//3. n+1노드 루트트리 수
long long int catalan_num_rec(int n){
    if(n==1 || n==0) return 1;
    
    int sum=0;
    for(int i=0; i<n; i++){
        sum+=(catalan_num_rec(i)*catalan_num_rec(n-i-1));
    }
    return sum;
}

long long int catalan_num_comb(int n){
    return combination_direct(2*n, n)/(n+1);
}


int main(){
    cout << "<combination>\n";
    cout << "5C3? " << combination_rec(5, 3) << " " << combination_direct(5, 3) << " (true:10)\n";

    
    //recursive combination
    clock_t start_time, end_time;
    start_time = clock();
    cout << "20C10? " << combination_rec(20, 10) << " (true:184756) (";
    end_time = clock();
    double exe_time = (double)(end_time-start_time)/1000;   
    cout << exe_time << "sec to execute combination(30,15))"<<endl;

    //direct ccombination(recursive factorial)
    start_time = clock();
    cout << "20C10? " << combination_direct(20, 10) << " (true:184756) (";
    end_time = clock();
    exe_time = (double)(end_time-start_time)/1000;   
    cout << exe_time << "sec to execute combination_direct(30,15))"<<endl;

    //비교: overflow가 안 나는 한 factorial을 이용한 계산이 더 빠름
    //하지만 factorial을 이용한 계산은 n이 조금만 커져도 바로 overflow남 (나누기 계산에서 쉽게 망가짐)
    //n, k가 크면 combination 자체를 recursive하게 계산하는 방식이 느려도(사실 매우 느림) 안정적으로 결과를 냄
    //overflow 다루기: factorial이나 뭐..어딘가든.. log씌우고.. 나누기는.. log세계에서 -로 계산 후.. 마지막 결과만 exp씌워서 변환해 돌려주자..
    
    cout << "<catalan number>\n";
    
    cout << "C3? " << catalan_num_rec(3) << " " << catalan_num_comb(3) << " (true:5)\n";

    start_time = clock();
    cout << "C10? " << catalan_num_rec(10) << "(true:16796) (";
    end_time = clock();
    exe_time = (double)(end_time-start_time)/1000;  
    cout << exe_time << "sec to execute catalan_num_rec(10))" << endl;
    
    start_time = clock();
    cout << "C10? " << catalan_num_comb(10) << "(true:16796) (";
    end_time = clock();
    exe_time = (double)(end_time-start_time)/1000;  
    cout << exe_time << "sec to execute catalan_num_comb(10))" << endl;

}