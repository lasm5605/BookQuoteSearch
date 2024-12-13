PROJECT GOAL

The goal of this project was to implement a suffix tree structure to build a book quote word search program. (The idea being that a user could input a word and the program will return a list of quotes containing that word from a particular book.) I chose to use the suffix tree structure because it is meant to store sequence of values rather than individual values, and the suffix tree is an efficient method for retrieving such data in terms of time and space complexity (0(N) at best if one uses Ukonnen's algorithm). The invariants of a suffix tree include: 1) exactly 'n' number of leaves, 2) except for the root, every internal node has at least 2 children, 3) the tree has edges labelled with a non-empty substring of the input data, 4) no two edges coming from the same root can contain string labels beginning wit the same character, and 5) concatenating all the string labels on the path from root to leaf spells out that suffix.
        

APPROACH/WALKTHROUGH

My approach to accomplishing my goals for this assignment was to draft a plan, set up a testing environment, and test early and often. My plan involved building a very simple suffix tree with a single root, child node, and edge connecting the two and then build on from there. As I did this, I used cout statements to check what my tree was producing, and I checked those values against a suffix tree visual aid tool here: https://visualgo.net/en/suffixtree. I used my main.cpp file to run and test my functions my from SuffixTree.cpp file. I built my suffix tree using 3 different structs: a node struct, an edge struct, and a tree struct. The details for each can be found in my SuffixTree.h file, but I will also share them here below.


    struct node {
        bool is_leaf; //indicates if node is a leaf or an internal node connected child edges to root
        int leaf_val; //if node is a leaf, then it holds a leaf value that increments according to string index
    };

    struct edge {
        node* parent; //node pointer to interal node at the start of an edge
        node* child; //node pointer for node attached to parent via edge
        string data; //the substring of the input string found along a particular edge
        vector<edge*> child_edges; //vector of edges to hold edges a tier below current edge that follow the same path (ex. edge substring "l" of "hello" might have child edges: "lo$" leaf_val 2; "o$" leaf_val 3)
        vector<edge*> send_down_edges; //vector meant to help in creating a new tier within a suffix tree pathway
    };

    struct SuffixTree {
        node* root; // pointer to tree's starting node
        node* leaf; // pointer to initial child node
        vector<edge*> parent_edges; //vector to hold top tier edges coming directly from root (each parent edge holds a vector of child edges, which is how I traverse the tree)
        string output; //string that is concatenated during the word search
    };


My program works by first reading in a .txt file (I have included chapter 1 of Pride and Prejudice). It then parses each sentence of the text using the parse_sentences function and saves each sentence to a vector. Each sentence is then fed into a BuildTree function, which creates in memory the starting node and first child node of the tree and passes this information along with the starting child leaf_val of 0 along to an init_SuffixTree function. The init_SuffixTree function is where the tree's root, first child, and first edge are initialized with the value of the input string. Then this function calls the insert_SuffixTree if the text size is bigger than 1 character. The insert_SuffixTree function is the meat of the code and actually does the heavy lifting of creating the tree (and it's pretty well commented in my code, I think). After the insert_function runs within the init_SuffixTree function, then the code calls a clean_up function meant to find any edges connected to leaf nodes whose data has matching first characters. It saves the location of those matching edges in a vector and then two more clean_up functions run. The first creates a new internal node and edge to hold the first character of the edges whose first characters match. The second creates two new leaf nodes and reassigns the parent node of those formerly matching edges to be the new internal node created in the previous function. Finally, the init_SuffixTree functions returns a suffix tree that the BuildTree function then passes along to the main.cpp file to be saved in a vector of trees. Once that vector is created, then the main function calls the SearchTree function, which uses a helper function as well, to traverse each tree in the vector of trees, appending any matching suffixes to the string output. If at the end of the search function, the output matches the original query, then the corresponding sentence is returned from the vector of sentences. It all sounds a bit all over the place and rather unhinged when I write it out. I ended up doing it this way because I really only had time figure out how to build a basic suffix tree that can't really handle a depth more than 2 and still produce the correct outputs when compared against the output of the visualization tool I was checking my work against. I know suffix trees are often used in genomic sequencing where punctuation characters don't often enter in, but that wasn't the case for my text, so this was my solution to use a suffix tree structure and still accomplish the book quote search goal. In retrospect, I realize that I maybe ended up appending to and traversing through a lot of vectors, which probably defeats the purpose of a tree structure, but I really wanted to try the suffix tree. Also, I struggled to find any explanation or pseudocode explaining how to build a suffix tree, so while I made something that outputs what appears to be the correct edge data and corresponding leaf node values of a suffix tree of a particular string, I'm sure my solution is pretty inefficient in terms of time and space complexity. If I had time to redo it, I would make better use of my node pointers. As it stands, I traverse my tree via the arrays of various edge pointers, whereas I feel like most trees are supposed to be traversed via node pointers. All that being said, I'm still proud of what I produced since I started with no knowledge of how I was going to accomplish any of this and ended up with a program that runs and does what I wanted it to do. 


RUNNING THE PROGRAM

You can run my program in JupyterHub on the command line using:

    g++ main.cpp -o main
    ./main

The program will print off a bunch of statements that list the edges of the suffix tree as well leaf value if the edge's end node is a leaf. I included these statements in my code's output to demonstrate how my program is creating suffix trees. Below all the cout statements, you will be prompted to enter a search query. Because I had to clean up the txt files (remove unusual characters and spacing), I only had time to do the first chapter of a book, so the words to be found are limited, but I suggest trying the words below. Once you've gotten some results with those words, you might have an idea of other types of words the text contains, so feel free to try your own.

    good
    girls
    Mister
    possession   



