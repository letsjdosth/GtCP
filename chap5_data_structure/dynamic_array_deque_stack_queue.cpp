#include <iostream>
#include <algorithm>

#include <deque>
#include <stack>
#include <queue>

using namespace std;

int main() {
    deque<int> d; //앞뒤로 넣고뺀다. O(1)(in average)
    d.push_back(5);
    d.push_back(2);
    d.push_front(3);
    d.push_front(4);
    cout << "front: " << d.front() <<" back: " << d.back() <<"\n";
    d.pop_back();
    d.pop_front();
    cout << "front: " << d.front() <<" back: " << d.back() <<"\n";

    stack<int> s; //뒤로 넣고뺀다 LIFO. (위로 서류더미 쌓는다고 생각). O(1)
    s.push(2);
    s.push(5);
    cout << s.top() << "\n";
    s.pop();
    cout << s.top() << "\n";
    
    queue<int> q; //뒤로넣고 앞으로뺀다 FIFO. O(1)
    q.push(2);
    q.push(5);
    cout << "front: " << q.front() <<" back: " << q.back() <<"\n";
    q.pop();
    cout << "front: " << q.front() <<" back: " << q.back() <<"\n";
}