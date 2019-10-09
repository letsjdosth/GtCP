#include <vector>
#include <tuple>
#include <set>

#include <iostream>
#include <algorithm>

using namespace std;

class Union_Find{
    private:
        vector<int> link;
        vector<int> size;
        int num_nodes;
    public:
        int weight_sum;
        Union_Find(int n){
            num_nodes = n;
            for(int i=0; i<=n; i++) link.push_back(i); //index 0은 더미 (헷갈려서...)
            for(int i=0; i<=n; i++) size.push_back(1);
            weight_sum=0;
        }
        int find(int x){
            //원소 x의 대표값을 반환한다. O(logn)
            while(x != link[x]) x=link[x];
            return x;
        }
        int find_path_compress(int x){
            //O(inv_Ackermann(n))
            if(x == link[x]) return x;
            return link[x] = find_path_compress(link[x]);
        }

        bool same(int a, int b){
            //원소 a, b가 같은 집합인지 확인한다
            return find(a)==find(b);
        }
        void unite(int a, int b){
            //원소 a와 b가 속한 집합을, 기존에 원소가 많았던 쪽으로 합친다.
            int a_rep, b_rep;
            a_rep = find(a);
            b_rep = find(b);
            if(size[a_rep] < size[b_rep]){
                swap(a_rep,b_rep);
                swap(a,b);
            }
            size[a_rep] += size[b_rep];
            link[b] = a;
        }
        void print_link(){
            cout << "node: ";
            for(int i=1; i<=num_nodes; i++){
                 cout << i << " ";
            }
            cout << "\nlink: ";
            for(int i=1; i<=num_nodes; i++){
                 cout << link[i] << " ";
            }
            cout << "\n";
        }
};

//sort callback
bool compare_weight(tuple<int,int,int>& a, tuple<int,int,int>& b){
    int a_weight = std::get<2>(a);
    int b_weight = std::get<2>(b);
    if(a_weight < b_weight) {
        return true;
    } else if(a_weight == b_weight) {
        if(std::get<0>(a) < std::get<0>(b)) return true;
        if(std::get<0>(a) > std::get<0>(b)) return false;
        if(std::get<0>(a) == std::get<0>(b)) {
            if (std::get<1>(a) <= std::get<1>(b)) return true;
            else return false;
        }
    } else {
        return false;
    } 
}

Union_Find kruskal(vector<tuple<int,int,int>> graph_sorted_edge){
    //graph의 node 수 세기 (더 좋은방법? 이거 복잡도를 늘릴것이다..)
    set<int> node_vector;
    for(tuple<int,int,int> edge : graph_sorted_edge){
        node_vector.insert(std::get<0>(edge));
        node_vector.insert(std::get<1>(edge));
    }
    int num_nodes = node_vector.size();
    
    //sorting 자리

    //make minimum spanning tree
    Union_Find min_span_tree = Union_Find(num_nodes);
    for(tuple<int,int,int> edge : graph_sorted_edge){
        int a = std::get<0>(edge);
        int b = std::get<1>(edge);
        int weight = std::get<2>(edge);
        if(!min_span_tree.same(a,b)){
            min_span_tree.unite(a,b);
            min_span_tree.weight_sum += weight;
        }
    }
    return min_span_tree;
}

int main(){
    //edge list expression
    //      (3) - 2 - (5) - 3 - (9) 
    //      /     |         |     \ 
    //   1 -     (6)       (3)     - 4
    //      \     |         |     / 
    //      (5) - 5 - (2) - 6 - (7)
    vector<tuple<int,int,int>> weighted_edges;
    weighted_edges.push_back({1,2,3}); weighted_edges.push_back({1,5,5});
    weighted_edges.push_back({2,3,5}); weighted_edges.push_back({2,5,6});
    weighted_edges.push_back({3,4,9}); weighted_edges.push_back({3,6,3});
    weighted_edges.push_back({4,6,7});
    weighted_edges.push_back({5,6,2});

    //sort by weight <-다른 그래프 경우에도 무결함이 확인되면 이부분을 위 kruskal 함수 앞부분에 넣는게 좋을 듯
    sort(weighted_edges.begin(), weighted_edges.end(), compare_weight);
    for(int i=0; i<0; i++){ //for debuging(sort)
        cout << std::get<0>(weighted_edges[i]) << std::get<1>(weighted_edges[i]) << std::get<2>(weighted_edges[i]) << endl;
    }

    Union_Find ex_min_span_tree = kruskal(weighted_edges);
    cout << "minimum spanning tree --- weight : " << ex_min_span_tree.weight_sum << " (true : 20)" << endl;
    ex_min_span_tree.print_link();
}