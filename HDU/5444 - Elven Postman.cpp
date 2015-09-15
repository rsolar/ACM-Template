#include <bits/stdc++.h>
using namespace std;

int n, q;

class TreeNode {
public:
	TreeNode(): v(0), lson(NULL), rson(NULL) {}
	int v;
	TreeNode *lson, *rson;
};

class BST {
private:
	TreeNode *root;
	void insertpri(TreeNode *&node, int x);
	TreeNode *findpri(TreeNode *node, int x);
public:
	BST(): root(NULL) {}
	void insert(int x);
	TreeNode *find(int x);
};

void BST::insertpri(TreeNode *&node, int x) {
	if (node == NULL) {
		node = new TreeNode();
		node->v = x;
		return;
	}
	if (node->v > x) {
		insertpri(node->lson, x);
	} else if (node->v < x) {
		insertpri(node->rson, x);
	}
}

void BST::insert(int x) {
	insertpri(root, x);
}

TreeNode *BST::findpri(TreeNode *node, int x) {
	if (node->v > x) {
		putchar('E');
		return findpri(node->lson, x);
	} else if (node->v < x) {
		putchar('W');
		return findpri(node->rson, x);
	}
}

TreeNode *BST::find(int x) {
	return findpri(root, x);
}

int main() {
	int u;
	int C = 0, T;
	scanf("%d", &T);
	while (++C <= T) {
		BST tree;
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &u);
			tree.insert(u);
		}
		scanf("%d", &q);
		while (q--) {
			scanf("%d", &u);
			tree.find(u);
			putchar('\n');
		}
	}
}
