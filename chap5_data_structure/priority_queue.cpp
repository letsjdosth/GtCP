#include <iostream>
#include <algorithm>

#include <queue>

using namespace std;

int main(){
    priority_queue<int> q; //기본적으로 값에의해 내림차순 정렬됨. 최대최소값에서만 넣고뺄때 사용. heap기반. O(logn)
    //multiset(역시 자동정렬됨)에 원소추가/탐색/삭제연산 붙인것이라 생각

    q.push(3);
    q.push(5);
    q.push(7);
    q.push(2);
    cout << q.top() << "\n"; //7. 기본적으로는 최대원소에서 넣고 뺴짐.
    q.pop();
    cout << q.top() << "\n"; //5
    q.pop();
    q.push(6);
    cout << q.top() << "\n"; //6
    

    priority_queue<int, vector<int>, greater<int>> min_q; //최소값에서 넣고빼지는 priority queue 선언
    min_q.push(3);
    min_q.push(5);
    cout << min_q.top() << "\n"; //3
}

