#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct node {
    bool is_leaf; //indicates if node is a leaf or an internal node connected child edges to root
    int leaf_val; //if node is a leaf, then it holds a leaf value that increments according to string index
};

struct edge {
    node* parent; //node pointer to interal node at the start of an edge
    node* child; //node pointer to an internal or a leaf node at the end of an edge
    string data; //the substring of the input string found along an edge
    vector<edge*> child_edges; //vector or edges to hold edges a tier below current edge that follow the same path (ex. edge substring "l" of "hello" might have child edges: "lo$" leaf_val 2; "o$" leaf_val 3)
    vector<edge*> send_down_edges; //vector meant to help in creating a new tier within a suffix tree pathway

};

struct SuffixTree {
    node* root; //tree's starting point
    node* leaf; //initial child node
    vector<edge*> parent_edges; //vector to hold top tier edges coming directly from root
    string output; //string that is concatenated during word search
};


    


    
    

    

    
        