#define _USE_MATH_DEFINES
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
public:
	int data, iL, iR;
	Node* left;
	Node* right;

	Node(int iL, int iR): iL(iL), iR(iR) {}
};


Node* constructTree(vector<int> arr, int start, int end) {
	if (start == end) {
		Node* leaf = new Node(start, end);
		leaf->data = arr[start];
		return leaf;
	}
	Node* node = new Node(start, end);
	int mid = (start + end) / 2;
	node->left = constructTree(arr, start, mid);
	node->right = constructTree(arr, mid + 1, end);
	node->data = node->left->data + node->right->data;
	return node;
}

void display(Node* node) {
	if (node->iL == node->iR) {
		cout << node->data << " ";
		return;
	}
	display(node->left);
	display(node->right);
}

int query(Node* node, int indL, int indR) {
	if (node->iL >= indL && node->iR <= indR) {
		return node->data;
	}
	else if (node->iL > indR || node->iR < indL)
		return 0;
	else {
		return (query(node->left, indL, indR) + query(node->right, indL, indR));
	}
}

int updateVal(Node* root, int index, int val) {
	if (index >= root->iL && index <= root->iR) {
		if (index == root->iL && index == root->iR) {
			root->data = val;
		}
		else {
			int leftSum = updateVal(root->left, index, val);
			int rightSum = updateVal(root->right, index, val);
			root->data = leftSum + rightSum;
		}
	}
	return root->data;
}

int main()
{
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	vector<int> v = {3, 8, 6, 7, -2, -8, 4, 9};
	Node* root1 = constructTree(v, 0, v.size() - 1);
	cout << query(root1, 1, 6);
	return 0;
}
