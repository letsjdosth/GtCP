#include <iostream>
#include <vector>


using namespace std;


class Segment_tree{
    private:
        vector<int> val_vector; //(modified to have length 2^n) original vector
        vector<int> tree; //segment tree (for sum)


        /// used in constructor ///

        //element 개수가 2^n 꼴인지 검사. 아니면 0을 추가해서 맞춘다.
        vector<int> modify_to_2overN_nodes(vector<int> vec){
            int vec_size = vec.size();
            while((vec_size & (vec_size-1)) != 0){ //2^n이면 false가 되어 이 루프를 나온다
                vec.push_back(0);
                vec_size++;
            }
            return vec;
        }
        
        //인스턴스에 저장될 tree vector의 길이 계산용 함수
        int determine_tree_vector_size(){
            return val_vector.size() * 2; 
            //등비수열의 합 공식으로부터(-1 해줘야하지만 idx를 1부터 쓸거라)
        }

        //인스턴스 tree 계산
        vector<int> making_tree(){
            //Before making tree, the instance should have proper value of
            //vector<int> val_vector, int size
            int tree_size = determine_tree_vector_size();

            vector<int> temp_tree(tree_size, 0);
            
            //temp_tree 맨 뒤에 val_vector 복사
            for(int idx = val_vector.size(); idx < tree_size; idx++){
                temp_tree[idx] = val_vector[idx - val_vector.size()];
            }
            //트리 노드 계산
            for(int idx = val_vector.size() -1 ; idx > 0 ; idx--){
                temp_tree[idx] = temp_tree[idx * 2] + temp_tree[idx * 2 + 1];
            }
            return temp_tree;
        }


        /// used in public print function ///


    public:
        //segment tree instance 생성. argument는 기본 vector
        Segment_tree(vector<int> vec){
            val_vector = modify_to_2overN_nodes(vec); //그냥 method 안에서 직접 조작하고 함수자체는 void로 하자
            tree = making_tree();
        }

        vector<int> get_tree(){
            vector<int> output = tree; //vector는 =으로 딥카피됨
            output.erase(output.begin()); //맨 앞 안쓰는 인덱스 지우고 리턴하자
            return output;
        }
        vector<int> get_val_vector(){
            return val_vector;
        }

        void print_val_vector(){
            cout << "<vector (possibly some 0's added)>\n";
            for(int i=0; i<val_vector.size(); i++)
                cout << val_vector[i];
            cout << endl;
        }

        void print_tree(){
            cout << "<tree>\n";
            for(int i=1; i<tree.size(); i++){
                cout << tree[i] <<" ";
                if (!((i+1)&i)) { 
                    //다음 i가 2의 거듭제곱이면 줄바꿔서 출력하자
                    //(트리 형태로)
                    cout << "\n";
                }
            }
        }
        
        //(기본 vector의) from부터 to까지의 합을 돌려줌(index는 0부터 시작)
        int sum(int from, int to){
            from += val_vector.size();
            to += val_vector.size();
            int sum_result = 0;
            while(from <= to){
                if(from%2 == 1) {
                    sum_result += tree[from];
                    from++;
                }
                if(to%2 == 0){
                    sum_result += tree[to];
                    to--;
                }
                from /=2;
                to /=2;
            }
            return sum_result;
        }

        //기본 vector의 position index에 add_val을 더함
        void add_to_vector(int position, int val){
            //val_vector update
            val_vector[position] += val;
            
            //tree update
            position += val_vector.size();
            tree[position] += val; //먼저 해당 위치에 더하고 시작
            for(position = position/2; position>=1; position/=2){
                tree[position] = tree[2*position] + tree[2*position+1];
                //변경이 필요한 노드만 쭉 따라올라가며 변경하자
            }
        }
};


int main(){
    vector<int> ex_vector1 = {5,8,6,3,2,7,2,6}; //2^3
    Segment_tree ex_tree1(ex_vector1);
    
    cout << "<get test>\nvector : ";
    vector<int> ex_vector1_get = ex_tree1.get_val_vector();
    vector<int> ex_vector1_segment_tree = ex_tree1.get_tree();
    for(int i=0; i<ex_vector1_get.size(); i++){
        cout << ex_vector1_get[i] << " ";
    }
    cout << "\n  (true: 5 8 6 3 2 7 2 6\nsegtree: ";
    for(int i=0; i<ex_vector1_segment_tree.size(); i++){
        cout << ex_vector1_segment_tree[i] << " ";
    }
    cout << "\n  (true: 39 22 17 13 9 9 8 5 8 6 3 2 7 2 6)\n"
        << "<print test>\n";
    ex_tree1.print_val_vector();
    ex_tree1.print_tree();

    cout << "<sum test>\n"
        << "case1. sum(0,3): " << ex_tree1.sum(0,3) << " (true:22)\n"
        << "case2. sum(2,5): " << ex_tree1.sum(2,5) << " (true:18)\n"
        << "case2. sum(3,6): " << ex_tree1.sum(3,6) << " (true:14)\n";

    cout << "<add to val vector>\n"
        <<"case1: add 1 to [0]!\n";
    ex_tree1.add_to_vector(0,1);
    ex_tree1.print_tree();
    cout <<"case2: add -2 to [5]!\n";
    ex_tree1.add_to_vector(5,-2);
    ex_tree1.print_tree();
}