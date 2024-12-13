#include "../Final Project 2270/SuffixTree.h"
#include <fstream>

node* init_node() {
    node* ret(new node);
    ret -> is_leaf = true;
    if (ret -> is_leaf == true) {
        ret -> leaf_val = 0;
    }
    
    return ret;
}

edge* init_edge(node* start, node* end) {
    edge* e(new edge);
    e -> parent = start;
    e -> child = end;
    e -> data = "";
    
    return e;
}


void insert_SuffixTree(SuffixTree* tree, string str, string held_text, edge* current_edge, int leaf_count) {
    //create a cursor to keep up with edges
    edge* cursor = current_edge;
    
    //create a counter to keep up with leaf_count
    int value = leaf_count;
    
    //create vector to hold all edges
    vector<edge*> edges; //holds just the parent edges coming directly from root
    vector<edge*> all_edges; //holds all edges created
    
    //if vector is empty, add starting edge to vector
    if (edges.size() == 0) {
        edges.push_back(current_edge);
        //update text to reflect that first letter and all following characters are already in vector
        str = str.erase(0,1);
    }
    
    //create for loop to go through characters in the updated text
    for (int i = 1; i < held_text.size(); i++) {
        //iterate through vector
        int e = 0;
        while (e < edges.size()) {
            //check to see if first letter of edge in vector matches current character
            if (held_text[i] == edges[e] -> data[0]) {
                if (edges[e] -> child -> is_leaf == true) {
                    string current_text = edges[e] -> data; //temporary text variable to build a new internal node with 2 children and edges
                    
                    //create new internal edge with children nodes and edges
                    cursor = edges[e];
                
                    cursor -> data = cursor -> data[0];
                    all_edges.push_back(cursor);
                    current_text = current_text.erase(0,1); //updating temporary text variable for child edge data
                    
                    node* first_child = new node;
                    first_child -> is_leaf = true;
                    first_child -> leaf_val = cursor -> child -> leaf_val; //upating first child leaf_val with parent node's value -- parent node will now hold no value
                
                    edge* first_child_edge = init_edge(cursor -> child, first_child);
                    first_child_edge -> data = current_text;
                    all_edges.push_back(first_child_edge);
                    edges[e] -> child_edges.push_back(first_child_edge);
                    
                    current_text.erase(0,i); //updating temporary text variable for next child edge data
                    value = value + 1; //updating leaf_val counter
                
                    node* second_child = new node;
                    second_child -> is_leaf = true;
                    second_child -> leaf_val = value; //updating second child leaf_val with next iteration value
  
                
                    edge* second_child_edge = init_edge(cursor -> child, second_child);
                    string hold_text = str.erase(0,1);
                    second_child_edge -> data = hold_text;
                    all_edges.push_back(second_child_edge);
                    edges[e] -> child_edges.push_back(second_child_edge);

                
                    cursor -> child -> is_leaf = false;
                    break;
                }
                else if (edges[e] -> child -> is_leaf == false) {
                    //condition to check if children added after suffix already has two children have matching first letters
                    //if so, create new parent edge and two new child edges
                    cursor = edges[e];
                    value = value + 1;
       
                    node* another_child = new node;
                    another_child -> is_leaf = true;
                    another_child -> leaf_val = value;
                
                    edge* another_child_edge = init_edge(cursor -> child, another_child);
                    another_child_edge -> data = str.erase(0,1);
                    all_edges.push_back(another_child_edge);
                    edges[e] -> child_edges.push_back(another_child_edge);
                    
                
                    break;
                }
            }
            
            else {
                if (e == edges.size() - 1) {
                    //insert new node and edge to suffix tree using new character as starting point
                    node* new_leaf = new node;
                    new_leaf -> is_leaf = true;
                    value = value + 1;
                    new_leaf -> leaf_val = value;
                
                    edge* new_edge_to_leaf = init_edge(current_edge -> parent, new_leaf);
                    new_edge_to_leaf -> data = str;
                    str = str.erase(0,1);
        
                
                    edges.push_back(new_edge_to_leaf);
                    all_edges.push_back(new_edge_to_leaf);
                    break;
                }
                else {
                    e++;
                }
            }
        }
    } 
    
    //cout << "root edges are: ";
    for (int i = 0; i < edges.size(); i++) {
        //cout << edges[i] -> child -> leaf_val << ". " << edges[i] -> data << "  ";
        tree -> parent_edges.push_back(edges[i]);
    }
    //cout << endl;

}

edge* find_for_cleanup(SuffixTree* tree, int parent_index) { 
    //this function looks through the child edges of each edge coming from the tree's root node and determines if any of them have matching first characters, if so it returns the parent edge so functions that follow know where to start from
    
    
    vector <edge*> matches = {}; //vector of edges to hold any child edges that need to be pushed down a tier
    //vector <edge*> nonmatches = {}; //vector to hold any child edges that need to stay where they are (coming from the current parent edge)
    edge* insert_point; //the edge pointer that will be returned
   
    //need to look through each parent edge's children
    for (int p = 0; p < tree -> parent_edges[parent_index] -> child_edges.size(); p++) {
        //cout << tree -> parent_edges[parent_index] -> data << ": " << tree -> parent_edges[parent_index] -> child_edges[p] -> data << endl;
        int k = 0;
        while (k < tree -> parent_edges[parent_index] -> child_edges.size()) {
            // if any of the children have mathcing first characters: 
            if (tree -> parent_edges[parent_index] -> child_edges[p] -> data[0] == tree -> parent_edges[parent_index] -> child_edges[k] -> data[0] && k != p) {
                
                //match has been found
                matches.push_back(tree -> parent_edges[parent_index] -> child_edges[p]);
                matches.push_back(tree -> parent_edges[parent_index] -> child_edges[k]);
                insert_point = tree -> parent_edges[parent_index];
                
                insert_point -> send_down_edges = matches;
                
                //cout << "matches currently include: ";
                //for (int m = 0; m < matches.size(); m++) {
                    //cout << matches[m] -> data << " ";
                //}
                //cout << endl;
                
                return insert_point;
            }
            else {
                //match has not been found
                k++;
            }
        }
    }
        
    return nullptr;

}

void clean_up_parent_edges(edge* found, SuffixTree* tree) { 
    //this function takes edge pointer returned from "find_for_clean_up function as input and creates a new child node and edge

    //create new internal node and edge that holds first character
    node* new_parent_node = new node;
    //add new internal edge to the parent edge's vector
    edge* new_parent_edge = init_edge(found -> child, new_parent_node);
    new_parent_edge -> data = found -> send_down_edges[0] -> data[0];
    new_parent_edge -> child -> is_leaf = false;
    found -> child_edges.push_back(new_parent_edge);
    //create children nodes and edges that hold the same strings minus the first character
    for (int i = 0; i < found -> send_down_edges.size(); i++) {
        cout << "new child of parent edge " << new_parent_edge -> data << " : " << found -> send_down_edges[i] -> data << " " << found -> send_down_edges[i] -> child -> leaf_val << endl;
        //set the new internal node as the children's parent node
        new_parent_edge -> child_edges.push_back(found -> send_down_edges[i]);
        found -> send_down_edges[i] -> parent = new_parent_node;
    }
}

void clean_up_child_edges (edge* found, SuffixTree* tree) {
    vector <edge*> nonmatching = {}; //this vector already exists in another function, I need to determine where it actualy belongs
    for (int q = 0; q < found -> child_edges.size(); q++) {
        int p = 0;
        while (p < found -> send_down_edges.size()) {
            if (found -> child_edges[q] -> data[0] == found -> send_down_edges[p] -> data[0] && found -> child_edges[q] -> child -> is_leaf) { 
                p++;
            }
            else {
                nonmatching.push_back(found -> child_edges[q]);
            }
            break;
        }
    } 
    found -> child_edges = nonmatching;
    
    for (int i = 0; i < found -> send_down_edges.size(); i++) {
        found -> send_down_edges[i] -> data = found -> send_down_edges[i] -> data.erase(0,1);
    }
}
    
    
SuffixTree* init_SuffixTree(string text, node* parent, node* child, int leaf_count) {
    
    SuffixTree* build_tree = new SuffixTree;
    
    build_tree -> root = parent;
    build_tree -> leaf = child;
    child -> is_leaf = true;
    child -> leaf_val = leaf_count;
    
    string str = text;
    
    edge* e = init_edge(build_tree -> root, build_tree -> leaf);
    e -> data = str;
    
    string text_hold = text;
    
    if (text.size() > 1) {
        insert_SuffixTree(build_tree, str, text_hold, e, leaf_count);
        //for (int i = 0; i < build_tree -> parent_edges.size(); i++) {
            //cout << build_tree -> parent_edges[i] -> data << " ";
            //cout << build_tree -> parent_edges[i] -> child -> is_leaf << " ";
        //}
        cout << endl;
        
        cout << "entering final build_Tree for loop" << endl;
        for (int i = 0; i < build_tree -> parent_edges.size() - 1; i++) { //not checking last element in parent_edges vector because it will always be terminating character '$'
            edge* to_clean_up = find_for_cleanup(build_tree, i);
            if (to_clean_up == nullptr) {
                break;
            }
            else {
                clean_up_parent_edges(to_clean_up, build_tree);
                clean_up_child_edges(to_clean_up, build_tree);
            }
        }
    }
    return build_tree;
}

void PrintSuffixTree_levels (SuffixTree* tree, edge* start) {
    //look through each parent edge in tree
    cout << endl;
    cout << "starting edge: " << start -> data;
    if (start -> child -> is_leaf) {
        cout << " " << start -> child -> leaf_val << endl;
    }
    else {
        cout << endl;
    }
    cout << "child edges: ";
    for (auto edges : start -> child_edges) {
        if (edges -> child -> is_leaf) {
            cout << edges -> data << "-" << edges -> child -> leaf_val << "  ";
        }
        else {
            cout << edges -> data << " ";
            PrintSuffixTree_levels(tree, edges);
        } 
    }
    cout << endl;

}

vector<string> parse_sentences() {
    ifstream input("Pride&Prejudice(Chapter 1).txt");
    string line, sentence;
    vector<string> sentences;
    
    if (!input.is_open()) {
        cout << "Error opening file!" << endl;
    }
    
    if (input.is_open()) {
        while (getline(input, line)) {
            for (char c : line) {
                sentence += c;
                if (c == '.' || c == '!' || c == '?') {
                    if (sentence[0] == ' ') {
                        sentence.erase(0,1);
                    }
                    else if (sentence[0] == '"' && sentence[1] == ' ' && sentence[2] == '"') {
                        sentence.erase(0,1);
                        sentence.erase(0,1);
                    }
                    sentences.push_back(sentence);
                    sentence = "";
                }
            }
        }
        input.close();
    }
    
    return sentences;
}
    
SuffixTree* BuildTree(string sentence) {
    node* start = new node;
    node* end = new node;
    int num_leaf = 0;
    
    SuffixTree* myTree = init_SuffixTree(sentence, start, end, num_leaf);
    
    for (int i = 0; i < myTree -> parent_edges.size(); i++) {
         PrintSuffixTree_levels(myTree, myTree -> parent_edges[i]);
    }
    
    return myTree;
}

int SearchTreeHelperHelper(string edge, string search) {
    //no match = -1;
    //partial = 0;
    //full = 1;
    
    int k = 0;
    while (k < search.size()) {
        
        if (k == edge.size()) {
            return 0;
        }
    
        if (edge[k] == search[k]) {
            k++;
        }
    
        else if (edge[k] != search[k]) {
            return -1;
        }
    }
    
    return 1;

}


string SearchTreeHelper(vector<edge*> start, string search_input) {
    //need to look through each first characer of each edge and see if it matches the first character of the input
    string ret = "";
    
    int i = 0;
    while (i < start.size()) {
        int check = SearchTreeHelperHelper(start[i] -> data, search_input);
        if (check == 1) {
            ret = ret + search_input; 
            return ret;
        }
        else if (check == 0) {
            ret = ret + start[i] -> data;
            start = start[i] -> child_edges;
            i = 0;
            search_input = search_input.erase(0,1);
        }
        i++;
    }
    
    return ret;
             
}


bool SearchTree(SuffixTree* tree, vector<edge*> start, string search_input) {
    
    tree -> output = SearchTreeHelper(start, search_input);
    
    
    //if output == search input, then the tree contains the word
    if (tree -> output == search_input) {
        return true;
    }
    //else return false
    return false;
}
   
        

