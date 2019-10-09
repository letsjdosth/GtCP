#include <iostream>
#include <algorithm>

#include <map>
#include <unordered_map>

using namespace std;

int main(){
    map<string,int> m; //key,value 쌍. 항상 key로 정렬됨. 2진트리 사용. O(logn)
    unordered_map<string,int> un_m; //key,value 쌍. hash 이용.(=python dict). O(1) in avg
    m["monkey"] = 4;
    m["banana"] = 3;
    m["harpsichord"] = 9;
    cout << m["banana"] << "\n";

    cout << m["aybabtu"] << "\n"; //key가 없었으면 그냥 생성하고 바로 0이 value로 들어감.

    if(m.count("aybabtu")){
        cout << "there is the key, 'aybabtu'!\n";
    }
    
    //순회
    for (auto x : m) {
        cout << "key value: " << x.first << " " << x.second << "\n";
    }

}