#include "../Final Project 2270/SuffixTree.cpp"


using namespace std;

int main() {
  
    vector<string> sentences = parse_sentences();
    vector<SuffixTree*> myTrees = {};
    
    for (int i = 0; i < sentences.size(); i++) {
        cout << sentences[i] << endl;
        sentences[i] = sentences[i] + '$';
        SuffixTree* new_tree = BuildTree(sentences[i]);
        myTrees.push_back(new_tree);
    }
    
    
    string search;
    
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << endl;
    cout << "search for: ";
    cin >> search;
    cout << endl;
    
    cout << "search results:" << endl;
    for (int i = 0; i < myTrees.size(); i++) {
        bool word_in_tree = SearchTree(myTrees[i], myTrees[i] -> parent_edges, search);
        if (word_in_tree == true) {
            cout << endl;
            sentences[i].pop_back();
            cout << sentences[i] << endl;
        }
    }
    cout << endl;


    return 0;
    
}
    