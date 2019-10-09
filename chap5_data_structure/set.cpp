#include <iostream>
#include <algorithm>

#include <set>
#include <unordered_set>

using namespace std;

int main(){
    //set
    set<int> s; //중복 허용 안함. 항상 정렬되어있음. []를 이용해 index로 원소 접근 불가. O(logn)
    unordered_set<int> un_s; //set과 같으나 정렬되어있지 않음. O(1), 최악의 경우 O(n)

    s.insert(3);
    s.insert(2);
    s.insert(5);
    s.insert(3);
    cout << "size:" << s.size() << " number of 2,3,5: "<< s.count(2) << s.count(3) << s.count(5) << "\n";
    s.erase(3);
    s.insert(4);
    for(auto x : s){
        cout << x << "\n";
    }
    
    auto it = s.find(6); //iterator 반환. 없으면 end()가 반환된다.
    if(it == s.end()){
        cout << "there is no 6! \n";
    }
    auto it2 = s.find(5);
    cout << *it2 << "\n"; //(iterator에 * 붙이면 해당 iterator가 가리키는 곳의 값을 준다)

    auto first = s.begin();
    auto last = s.end();
    last--; //end가 끝의 다음자리를 주므로, 하나 역으로 돌리자.
    cout << "first and last: "<< *first << " " << *last << "\n";

    s.insert(3);
    cout << "s: ";
    for(auto x : s){
        cout << x << " ";
    }
    cout << "\n lower bound of 3: " << *s.lower_bound(3)
    << "\n upper bound of 3: " << *s.upper_bound(3) <<"\n";

}
