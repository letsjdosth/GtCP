#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(string a, string b) {
    if(a.size()==b.size()) return a<b;
    else return a.size() < b.size();

}

int main()
{
    vector<string> v = {"yeeun", "abc", "sdfadsf"};
    sort(v.begin(), v.end(), comp);

}