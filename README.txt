PROJECT GOAL

The goal of this project was to implement a suffix tree structure to build a book quote word search program. (The idea being that a user could input a word and the program will return a list of quotes containing that word from a particular book.) I chose to use the suffix tree structure because it is meant to store sequence of values rather than individual values, and the suffix tree is an efficient method for retrieving such data in terms of time and space complexity (0(N) at best if one uses Ukonnen's algorithm). The invariants of a suffix tree include: 1) exactly 'n' number of leaves, 2) except for the root, every internal node has at least 2 children, 3) the tree has edges labelled with a non-empty substring of the input data, 4) no two edges coming from the same root can contain string labels beginning wit the same character, and 5) concatenating all the string labels on the path from root to leaf spells out that suffix.
        

APPROACH

My approach to accomplishing my goals for this assignment was to draft a plan, set up a testing environment, and test early and often. My plan involved building a very simple suffix tree with a single root, child node, and edge connecting the two and then build on from there. As I did this, I used cout statements to check what my tree was producing, and I checked those values against a suffix tree visual aid tool here: https://visualgo.net/en/suffixtree. I used my main.cpp file to run and test my functions my from SuffixTree.cpp file. I built my suffix tree using 3 different structs: a node struct, an edge struct, and a tree struct. The details for each can be found in my SuffixTree.h file, but I will also share them here below.


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


My program works by reading in a txt file (I have included chapter 1 of Pride and Prejudice for your convenience). It then parses each sentence of the text and feeds them into a BuildTree function, which appends each completed tree into a vector of suffix trees. I chose to do it this way because I really only had time figure out how to build a basic suffix tree (1 sentence long) that produced the correct outputs when compared against the output of the visualization tool I was checking my work against. I know suffix trees are often used in genomic sequencing where punctuation characers don't often enter in, but that wasn't the case for my text, so this was my solution to use the suffix tree and still accomplish the book quote search goal. In retrospect, I realize that an array might accomplish the same goal, but I really wanted to try the suffix tree. Also, I struggled to find any explanation or pseudocode explaining how to build a suffix tree, so I think I've ended up with something that is pretty inefficient in terms of time and space complexity, but it's the best I could do at this time to just have a program that runs.


RUNNING THE PROGRAM

You can run my program in JupyterHub on the command line using:

    g++ main.cpp -o main
    ./main

The program will print off a bunch of statements that list the edges of the suffix tree as well leaf value if the edge's end node is a leaf. I included these statements in my code's output to demonstrate how my program is creating suffix trees. Below all the cout statements, you will be prompted to enter a search query. Because I had to clean up the txt files (remove unusual characters and spacing), I only had time to do the first chapter of a book, so the words to be found are limited, but I suggest trying the words below. Once you've gotten some results with those words, you might have an idea of other types of words the text contains, so feel free to try your own.

    good
    girls
    Mister
    possession   



