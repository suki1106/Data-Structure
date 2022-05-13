#include <iostream>
using namespace std;
struct node {
	bool visited;
	int x, y, moves;
	node(int x, int y, int moves) :x(x), y(y), moves(moves) {}
	node() :visited(false) {}
};
class queue {
public:
	queue() {
		q = (node*) new node[10000];
		last = -1;
	}
	void push(node val) {
		last++;
		q[last] = val;
	}
	node pop() {
		node t = q[0];
		for (int i = 0; i < last; i++) {
			q[i] = q[i + 1];
		}
		last--;
		return t;
	}
	bool empty() {
		if (last == -1) return true;
		return false;
	}
	~queue() { delete q; }
private:
	node* q;
	int last;
};
node** nodes;
int n, m;
char** map;
bool valid(node p) {
	return p.x >= 0 && p.x < m&& p.y >= 0 && p.y < n && (map[p.y][p.x] == '*' || map[p.y][p.x] == '.' || map[p.y][p.x] == '@');
}
bool vis(node p) {
	return nodes[p.y][p.x].visited == true;
}
void free() {
	for (int i = 0; i < n; i++) {
		delete map[i];
		delete nodes[i];
	}
	delete map;
	delete nodes;
}
int main() {
	node str, end;
	while (cin >> n >> m) {
		map = (char**) new char* [n];
		nodes = (node**) new node * [n];
		for (int i = 0; i < n; i++) {
			map[i] = (char*) new char[m];
			nodes[i] = (node*) new node[m];
		}
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) {
				cin >> map[i][j];
				if (map[i][j] == '.') {
					str.x = j;
					str.y = i;
				}
				else if (map[i][j] == '@') {
					end.x = j;
					end.y = i;
				}
			}
		}
		queue q;
		str.moves = 0;
		nodes[str.y][str.x].moves = 0;
		q.push(str);
		while (!q.empty()) {
			node c = q.pop();
			if (!valid(c) || vis(c))
				continue;
			nodes[c.y][c.x].visited = true;
			nodes[c.y][c.x].moves = c.moves;
			q.push(node(c.x + 1, c.y, c.moves + 1));
			q.push(node(c.x - 1, c.y, c.moves + 1));
			q.push(node(c.x, c.y + 1, c.moves + 1));
			q.push(node(c.x, c.y - 1, c.moves + 1));
		}
		cout << nodes[end.y][end.x].moves << endl;
		free();
	}
	return 0;
}