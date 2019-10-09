#include <iostream>

using namespace std;

typedef double (* vFunctionCall)(double args);

double ternary_search(vFunctionCall conv_func, double leftlim, double rightlim){
    double epsilon = 0.001; //error upperbound
    if ((rightlim - leftlim) < epsilon){
        return (rightlim + leftlim)/2;
    }
    
    double mid1 = (2*leftlim + rightlim)/3;
    double mid2 = (leftlim + 2* rightlim)/3;
    double result;
    
    cout << mid1 << " and " << mid2;
    cout << " (" << conv_func(mid1) << " and " << conv_func(mid2) <<")" << endl;

    if(conv_func(mid1) < conv_func(mid2)){
        result = ternary_search(conv_func, leftlim, mid2);
    } else {
        result = ternary_search(conv_func, mid1, rightlim);
    }
    return result;
}

double example_convex_function(double x){
    double result = (x - 3.5) * (x - 3.5) + 2;
    return result;
}

int main(){
    double ex_argmin;
    double ex_min;
    ex_argmin = ternary_search((vFunctionCall)example_convex_function, 0, 10);
    ex_min = example_convex_function(ex_argmin);
    cout << "minimum : " << ex_min << " at " << ex_argmin << endl;

}