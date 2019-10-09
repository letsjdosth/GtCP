#include <iostream>

using namespace std;

struct node{
    node *left, *right;
    int weight, size, value;
    node(int v){
        left = right = nullptr;
        weight = rand();
        size = 1;
        value = v;
    }
};

int size(node *treap){
    if (treap == nullptr) return 0;
    return treap->size;
}

void split(node *treap, node *&left, node *&right, int k){
    if(treap == nullptr){
        left = right = nullptr;
    } else {
        if(size(treap->left) < k){
            split(treap->right, treap->right, right, k - size(treap->left) - 1);
            left = treap;
        } else {
            split(treap->left, left, treap->left, k);
            right = treap;
        }
        treap->size = size(treap->left) + size(treap->right) + 1;
    }
}

void merge(node *&treap, node *left, node *right){
    if(left==nullptr) treap = right;
    else if(right==nullptr) treap = left;
    else {
        if(left->weight < right->weight) {
            merge(left->right, left->right, right);
            treap = left;
        } else {
            merge(right->left, left, right->left);
            treap = right;
        }
        treap->size = size(treap->left) + size(treap->right) + 1;

    }
}

int main(){
    node *treap = nullptr;
    merge(treap, treap, new node(1));
    merge(treap, treap, new node(2));
    merge(treap, treap, new node(3));
    merge(treap, treap, new node(4));
    node *left, *right;
    split(treap, left, right, 2);
    merge(treap, right, left);
}