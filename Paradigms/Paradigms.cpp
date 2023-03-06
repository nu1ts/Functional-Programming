#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <queue>
#include <fstream>
using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;

	Node(int data, Node* left, Node* right) :
		data(data), left(left), right(right) {}
};

void stub() { return; }

vector<int> readDataFromFile() {
	ifstream file("input.txt");
	vector<int> numbers;
	copy(istream_iterator<int>(file), istream_iterator<int>(), back_inserter(numbers));
	return numbers;
}

int getMidWithCeil(const double start, const double end) {
	return ceil((start + end) / 2);
}

Node* createNode(Node* root, Node* left, Node* right) {
	return new Node(root->data, left, right);
}

Node* createBalancedTree(const vector<int> inputVector, const int start, const int end) {
	return start > end ? nullptr : createNode(new Node(inputVector[getMidWithCeil(start, end)], nullptr, nullptr),
		createBalancedTree(inputVector, start, getMidWithCeil(start, end) - 1),
		createBalancedTree(inputVector, getMidWithCeil(start, end) + 1, end));
}

Node* getBalancedTree(const vector<int> inputVector) {
	return createBalancedTree(inputVector, 0, inputVector.size() - 1);
}

int getHeight(const Node* node) {
	return !node ? 0 : 1 + max(getHeight(node->left), getHeight(node->right));
}

void printNull() {
	cout << "null" << " ";
}

void printNodesAtLevel(const Node* node, int level, function<void(const Node*)> func) {
	!node ? printNull() :
		level == 1 ? func(node) :
		level > 1 ? (printNodesAtLevel(node->left, level - 1, func), printNodesAtLevel(node->right, level - 1, func)) :
		stub();
}

void printTreeByLevel(const int start, const int end, const Node* root) {
	start <= end ? (printNodesAtLevel(root, start, [](const Node* node) { cout << node->data << " "; }),
		printTreeByLevel(start + 1, end, root)) : stub();
}

void printTree(const Node* root) {
	printTreeByLevel(1, getHeight(root), root);
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	printTree(getBalancedTree(readDataFromFile()));
}