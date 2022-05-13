#include <iostream>

using namespace std;

struct node {
	int val;
	node* left = NULL;
	node* right = NULL;
	int lsubnode = 0;
	int lsubsum = 0;
	int rsubsum = 0;
	int rsubnode = 0;
};
node* FindMax(node*root) {
	if (root->right)
		return FindMax(root->right);
	else
		return root;
}
int least_node(node* root, int target,int total) { 
	if (total - root->lsubsum - root->rsubsum - root->val > target) return 0x7fffffff;
	int t = total - root->rsubsum;
	int ans = root->rsubnode, ans2;
	if (t <= target) { 
		ans2 = least_node(root->right, target, total);
		if (ans2 != 0x7fffffff)return ans2;
		else return ans;
	}
	else { 
		t -= root->val;
		++ans;
		if (t <= target) {
			return ans;
		}
		else {
			return ans + least_node(root->left, target, t);
		}
	}
}
int most_node(node* root, int target,int total) {
	int f = total - root->lsubsum;
	int ans = 0,c2;
	if (!root) return-1;
	if (f >= target) {
		f -= root->val;
		ans += root->lsubnode;
		if (f >= target) {
			++ans;
			if (f - root->rsubsum >= target) {
				ans += root->rsubnode;
			}
			else {
				c2 = most_node(root->right, target, f);
				if (c2 != -1)ans += c2;
			}
		}

		return ans;
	}
	else { // go left subtree deeper
		return most_node(root->left, target, total);
	}

}
void deletion(node*& root, int val) {
	if (root->val == val) {
		if (root->left && root->right) {
			node* max = FindMax(root->left);
			root->val = max->val;
			deletion(root->left, max->val);
		}
		else {
			node* temp = root;
			if (root->left) {
				root = root->left;
			}
			else if (root->right) {
				root = root->right;
			}
			else {
				root = NULL;
			}
			delete temp;
		}
	}
	else if (root->val > val) {
		root->lsubnode--;
		root->lsubsum -= val;
		deletion(root->left, val);
	}
	else{
		root->rsubnode--;
		root->rsubsum -= val;
		deletion(root->right, val);
	}
}
void insertion(node* root, int val) {
	if (root->val >= val) { //
		root->lsubnode++;
		root->lsubsum += val;
		if (root->left) {
			insertion(root->left, val);
		}
		else {
			node* n = new node;
			n->val = val;
			root->left = n;

		}
	}
	else {
		root->rsubnode++;
		root->rsubsum += val;
		if (root->right) {
			insertion(root->right, val);
		}
		else {
			node* n = new node;
			n->val = val;
	
			root->right = n;
		}
	}
}
void print(node* root) {
	cout << root->val;
	if (root->left) {
		cout << "(";
		print(root->left);
		cout << ")";
	}
	else {
		cout << "()";
	}
	if (root->right) {
		cout << "(";
		print(root->right);
		cout << ")";
	}
	else {
		cout << "()";
	}
}
int main() {
	int n,value;
	char cmd;
	node* root;
	cin >> n >> value;
	root = new node;
	root->val = value;
	for (int i = 1; i < n; i++) {
		cin >> value;
		insertion(root, value);
	}
	while (cin >> cmd) {
		if (cmd == 'P') {
			print(root);
			cout << endl;
		}
		else if (cmd == 'I') {
			cin >> value;
			insertion(root, value);
		}
		else if (cmd == 'D') {
			cin >> value;
			deletion(root, value);
		}
		else if (cmd == 'L') { // <=
			cin >> value;
			if (value == root->lsubsum + root->rsubsum + root->val)
				cout << 0 << endl;
			else
				cout << least_node(root, value, root->lsubsum + root->rsubsum + root->val) << endl;
			
		}
		else if (cmd == 'M') { //>=
			cin >> value;
			cout << most_node(root, value, root->lsubsum + root->rsubsum + root->val) << endl;
		}
	}
	return 0;
}