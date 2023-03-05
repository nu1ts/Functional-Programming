#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <cmath>
#include <queue>
using namespace std;

struct Node {
	int data;
	Node* left;
	Node* right;

	Node(int data, Node* left, Node* right) :
		data(data), left(left), right(right) {}
};

void stub() { return; }

vector<int> readDataFromFile(const vector<int>& inputVector) {
	vector<int> copiedVector(inputVector);

	int value; cin >> value ? [&]() {
		copiedVector.push_back(value);
		copiedVector = readDataFromFile(copiedVector); }() : stub();

		return copiedVector;
}

int getMid(const int& start, const int& end) {
	return (start + end) / 2;
}

Node* merge(Node* root, Node* left, Node* right) {
	return new Node(root->data, left, right);
}

Node* createBalancedTree(const vector<int>& inputVector, const int& start, const int& end) { 
	if (start > end) return nullptr;
	Node* newNode = new Node(inputVector[getMid(start, end)], nullptr, nullptr);
	return merge(newNode, createBalancedTree(inputVector, start, getMid(start, end) - 1), createBalancedTree(inputVector, getMid(start, end) + 1, end));
}

Node* getBalancedTree(const vector<int>& inputVector) { //требуется дебаг
	return createBalancedTree(inputVector, 0, inputVector.size() - 1);
}

void BFS(Node* root) { //переписать
	queue<Node*> q;
	q.push(root);
	while (!q.empty()) {
		Node* cur = q.front();
		q.pop();
		cout << cur->data << " ";
		if (cur->left) {
			q.push(cur->left);
		}
		if (cur->right) {
			q.push(cur->right);
		}
	}
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	vector<int> nums = readDataFromFile(vector<int>());
	Node* root = getBalancedTree(nums);
	BFS(root);
}