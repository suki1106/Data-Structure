#include <iostream>
using namespace std;

struct node {
    int visWither = 0x7fffffff;
    int index;
    bool isOasis;
    node(int v, int i, bool iso) :visWither(v), index(i), isOasis(iso) {};
    node(int v, int i) :visWither(v), index(i) {};
    node() {};
};

struct Link {
    node data;
    Link* next;
};

class queue {
public:
    Link* head;
    Link* tail;
    node pop();
    void push(node data);
    bool empty() { return head == NULL; }
    queue();
};


queue::queue() {
    head = NULL;
    tail = NULL;
}

node queue::pop() {
    node data = head->data;
    Link* p = head;
    head = head->next;
    delete p;
    return data;
}

void queue::push(node data) {
    if (head == NULL) {
        head = new Link;
        head->data = data;
        head->next = NULL;
        tail = head;
    }
    else {
        tail->next = new Link;
        tail = tail->next;
        tail->next = NULL;
        tail->data = data;
    }
}

bool** adj;
node* nodes;

int main() {
    int n, edges;
    cin >> n >> edges;
    nodes = new node[n];
    for (int i = 0, t; i < n; i++) {
        cin >> t;
        (t == 1) ? (nodes[i].isOasis = true) : (nodes[i].isOasis = false);
        nodes[i].index = i;
    }
    adj = new bool* [n]; //adjacency matrix
    for (int i = 0; i < n; i++) {
        adj[i] = new bool[n];
        for (int j = 0; j < n; j++) {
            adj[i][j] = false;
        }
    }
    for (int i = 1, a, b; i <= edges; i++) {
        cin >> a >> b;
        adj[a][b] = true;
        adj[b][a] = true;
    }
    int s, d;

    while (cin >> s >> d) { //bfs
        queue q;
        q.push(node(0, s));
        if (nodes[s].isOasis)nodes[s].visWither = 0;
        else nodes[s].visWither = 1;
        bool find = false;
        while (!q.empty()) {
            node current = q.pop();
            if (nodes[current.index].isOasis)current.visWither = 0;
            else current.visWither++;

            if (current.visWither == 3)continue;

            if (current.index == d) {
                find = true;
                cout << "Yes" << endl;
                break;
            }

            for (int i = 0; i < n; i++) {
                if (adj[current.index][i] && current.visWither < nodes[i].visWither) {
           
                    nodes[i].visWither = current.visWither;
                    q.push(node(current.visWither, i));
                }
            }

        }
        if (!find)
            cout << "No" << endl;
        //reset
        for (int i = 0; i < n; i++)nodes[i].visWither = 0x7fffffff;
        while (!q.empty())q.pop();
    }

    for (int i = 0; i < n; i++)delete adj[i];
    delete adj;
    delete nodes;
    return 0;
}