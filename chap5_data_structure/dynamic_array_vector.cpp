#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int print_vector(std::vector<int> v){
    for(int i=0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}

int main(){
    //vector
    vector<int> v;
    v.push_back(3);
    v.push_back(2);
    v.push_back(5);

    cout << v[0] << " " << v[1] << " " << v[2] << "\n";
    v.pop_back();
    cout << v.back() << "\n";

    vector<int> v2 = {2,4,2,5,1};
    vector<int> v3(8); //size 8, initial value 0
    vector<int> v4(8,2); //size 8, initial value 2

    //vector iteration
    for(int i=0; i < v.size(); i++){
        cout << v[i] << "\n";
    }
    for(auto x : v) { //값을 복사하며 순회
        cout << x << "\n";
    }
    for(const auto& x : v) { //참조로 순회
        cout << x << "\n";
    }

    //iterator
    vector<int> v5 = {5,2,3,1,2,5,7,1};
    sort(v5.begin(), v5.end());
    print_vector(v5);
    reverse(v5.begin(), v5.end());
    print_vector(v5);
    random_shuffle(v5.begin(), v5.end());
    print_vector(v5);
}