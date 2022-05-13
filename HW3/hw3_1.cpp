#include <iostream>

using namespace std;

struct node {
	int val;
	node* left = NULL;
	node* right = NULL;
	bool isblack;
};
void lr(node*& r) {
	node* b = r->left;
	node* c = b->right;
	node* t1 = c->left;
	node* t2 = c->right;
	c->left = b;
	c->right = r;
	b->right = t1;
	r->left = t2;
	r->isblack = b->isblack = false;
	c->isblack = true;
	r = c;
}
void rr(node*& r) {
	node* b = r->right;
	node* c = b->right;
	node* t1 = b->left;
	b->left = r;
	r->right = t1;
	r->isblack = c->isblack = false;
	b->isblack = true;
	r = b;
}
void rl(node*& r) {
	node* b = r->right;
	node* c = b->left;
	node* t1 = c->left;
	node* t2 = c->right;
	c->left = r;
	c->right = b;
	r->right = t1;
	b->left = t2;
	r->isblack = b->isblack = false;
	c->isblack = true;
	r = c;
}
void ll(node*& r) {
	node* b = r->left;
	node* c = b->left;
	node* t1 = b->right;
	b->right = r;
	r->left = t1;
	r->isblack = c->isblack = false;
	b->isblack = true;
	r = b;
}
void cr(node*& r,int num) {
	if (r->right && !r->right->isblack) {
		node* c = r->right;
		if (c->val < num && c->right && !c->right->isblack) {
			rr(r);
		}
		else if (c->val >= num && c->left && !c->left->isblack) {
			rl(r);
		}
	}
}
void cl(node*& r,int num) {
	if (r->left && !r->left->isblack) {
		node* c = r->left;
		if (c->val < num && c->right && !c->right->isblack) {
			lr(r);
		}
		else if (c->val >= num && c->left && !c->left->isblack) {
			ll(r);
		}
	}
}
node* insert(node*r, int num) { // color change => two consecutive red => insert => check two consecutive red ==> check root
	if (!r) {
		r = new node;
		r->val = num;
		r->isblack = false;
	}
	else {
		if (r->left && !r->left->isblack && r->right && !r->right->isblack) {
			r->isblack = false;
			r->left->isblack = r->right->isblack = true;
		}
		if (r->val < num) { // r
			cr(r, num);
			r->right = insert(r->right, num);
			// after insertion check whether there are two consequtive red node
			cr(r, num);
		}
		else {
			cl(r, num);
			r->left = insert(r->left, num);
			// after insertion 
			cl(r, num);
		}
	}
	return r;
}
void print(node*r) {
	cout << r->val;
	cout << (r->isblack ? "_b" : "_r");
	if (r->left) {
		cout << "(";
		print(r->left);
		cout << ")";
	}
	else {
		cout << "()";
	}
	if (r->right) {
		cout << "(";
		print(r->right);
		cout << ")";
	}
	else {
		cout << "()";
	}
}
int main() {
	char cmd;
	int num;
	node* root = NULL;
	while (cin >> cmd) {
		if (cmd == 'I') {
			cin >> num;
			root = insert(root, num);
			root->isblack = true;
		}
		else {
			print(root);
			cout << endl;
		}
	}
	return 0;
}