#include <iostream>

using namespace std;

bool rt = false;

struct node {
	int val;
	int bf;
	int height;
	node* left = NULL;
	node* right = NULL;
};
void preorder(node* root) {
	cout << root->val;
	if (root->left) {
		cout << "(";
		preorder(root->left);
		cout << ")";
	}
	else {
		cout << "()";
	}
	if (root->right) {
		cout << "(";
		preorder(root->right);
		cout << ")";
	}
	else {
		cout << "()";
	}

}
void inorder(node* root) {
	if (root->left) {
		cout << "(";
		inorder(root->left);
		cout << ")";
	}
	else {
		cout << "()";
	}
	cout << root->val;
	if (root->right) {
		cout << "(";
		inorder(root->right);
		cout << ")";
	}
	else {
		cout << "()";
	}

}
void postorder(node* root) {
	if (root->left) {
		cout << "(";
		postorder(root->left);
		cout << ")";
	}
	else {
		cout << "()";
	}
	if (root->right) {
		cout << "(";
		postorder(root->right);
		cout << ")";
	}
	else {
		cout << "()";
	}
	cout << root->val;
}

node* FindMax(node* root) {
	if (root->right)
		return FindMax(root->right);
	else
		return root;
}

int m(int a, int b) {
	if (a > b)return a;
	return b;
}
int Height(node*& r) {
	if (!r)return 0;
	int lh = Height(r->left);
	int rh = Height(r->right);
	r->height = m(lh, rh) + 1;
	return r->height;
}
int d(node*& r) {
	int lh = 0, rh = 0;
	if (r->left) lh = r->left->height;
	if (r->right) rh = r->right->height;
	return m(lh, rh)+1;
}
void rr(node*&r) {
	node* b = r->right;
	node* t = b->left;
	b->left = r;
	r->right = t;
	r->height = d(r);
	b->height = d(b);
	r = b;
}
void ll(node*& r) { // update height
	node* b = r->left;
	node* t = b->right;
	b->right = r;
	r->left = t;
	r->height = d(r);
	b->height = d(b);
	r = b;
}

void lr(node*& r) {
	node* c = r->left->right;
	node* b = r->left;
	node* t1 = c->left;
	node* t2 = c->right;
	c->right = r;
	c->left = b;
	b->right = t1;
	r->left = t2;

	// update height
	r->height = d(r);
	b->height = d(b);
	c->height = d(c);

	r = c;
}
void rl(node*& r) {
	node* b = r->right;
	node* c = r->right->left;
	node* t1 = c->left;
	node* t2 = c->right;
	c->left = r;
	c->right = b;
	r->right = t1;
	b->left = t2;


	r->height = d(r);
	b->height = d(b);
	c->height = d(c);
	

	r = c;
}
int calbf(node*& r) {
	int lh = 0, rh = 0;
	if (r->left)lh = r->left->height;
	if (r->right)rh = r->right->height;
	return lh - rh;
}
void insertion(node*& r, int val) {
	if (!r) {
		r = new node;
		r->val = val;
		r->height = 1;
		return;
	}
	else if (r->val >= val) {
		insertion(r->left, val);
	}
	else {
		insertion(r->right, val);
	}
	r->height = d(r);
	if (rt) return;
	r->bf = calbf(r);
	if (r->bf == 2) {
		rt = true;
		r->left->bf = calbf(r->left);
		if (r->left->bf == 1) { // ll
			ll(r);
		}
		else { // lr
			lr(r);
		}
	}
	else if (r->bf == -2) {
		rt = true;
		r->right->bf = calbf(r->right);
		if (r->right->bf == 1) { // rl
			rl(r);
		}
		else { // rr
			rr(r);
		}
	}
}
void deletion(node* &r, int val) {
	if (r->val == val) {
		if (r->left && r->right) {
			node* max = FindMax(r->left);
			r->val = max->val;
			deletion(r->left, max->val);
			int lh = Height(r->left);
			r->height = d(r);
			r->bf = calbf(r);
		}
		else {
			node* t = r;
			if (r->left) {
				r = r->left;
			}
			else if (r->right) {
				r = r->right;
			}
			else {
				r = NULL;
			}
			delete t;
		}
		if (!r)return;
	}
	else if (r->val > val) {	
		deletion(r->left, val);
	}
	else {
		deletion(r->right, val);
	}
	r->height = d(r);
	r->bf = calbf(r);
	if (r->bf == 2) {
		r->left->bf = calbf(r->left);
		if (r->left->bf == 1 || r->left->bf == 0) {
			ll(r);
		}
		else if (r->left->bf == -1) {
			lr(r);
		}
	}
	else if (r->bf == -2) {
		r->right->bf = calbf(r->right);
		if (r->right->bf == 0 || r->right->bf == -1) {
			rr(r);
		}
		else if (r->right->bf == 1) {
			rl(r);
		}
	}
}
int main() {
	int n, value;
	char cmd;
	cin >> n >> value;
	node* root = new node;
	root->val = value;
	for (int i = 1; i < n; i++) {
		cin >> value;
		insertion(root, value);
		rt = false;
	}
	while (cin >> cmd) {
		cin >> value;
		if (cmd == 'I') {	
			insertion(root, value);
			rt = false;
		}
		else if (cmd == 'P') {
			if (value == 1) {
				preorder(root);
				cout << endl;
			}
			else if (value == 2) {
				inorder(root);
				cout << endl;
			}
			else {
				postorder(root);
				cout << endl;
			}
		}
		else if (cmd == 'D') {
			deletion(root, value);
		}
	}
	return 0;
}