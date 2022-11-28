#pragma once

#include <iostream>
#include <vector>

using namespace std;

struct Node {
  int key;  //value that the node holds
  int size; //total size of the node
  Node *left; //pointer to left subtree
  Node *right;  //pointer to right subtree
  Node (int k) { key = k; size = 1; left = right = nullptr; }
};

void fix_size(Node *T);
Node *insert(Node *T, int k);
vector<int> inorder_traversal(Node *T);
Node *find(Node *T, int k);
Node *select(Node *T, int r);
Node *join(Node *L, Node *R);
Node *remove(Node *T, int k);
void split(Node *T, int k, Node **L, Node **R);
Node *insert_random(Node *T, int k);
void printVector(vector<int> v);
void printBT(const std::string& prefix, const Node* node, bool isLeft);
void printBT(const Node* node);