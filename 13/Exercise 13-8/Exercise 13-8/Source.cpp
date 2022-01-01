#include <iostream>
#include <string>
using namespace std;

struct Tnode { 
	string word; 
	int count; 
	Tnode* left;
	Tnode* right;

	Tnode(string w, int c = 0, Tnode* l = nullptr, Tnode* r = nullptr)
		:word{ w }, count{ c }, left{ l }, right{ r } { }
};

Tnode* insert(Tnode* tree, Tnode* new_word)
{
	Tnode* before = nullptr;
	Tnode* next = nullptr;

	Tnode* p = tree;
	while (p) {
		if (p->word < new_word->word) {
			if (p->right->word > new_word->word) {
				before = p;
				next = p->right;
				break;
			}
			p = p->right;
		}
		else if (p->word > new_word->word) {
			if (p->left->word < new_word->word) {
				before = p->left;
				next = p;
				break;
			}
			p = p->left;
		}
		else {
			p->count += new_word->count;
			return p;
		}
	}

	before->right = new_word;
	next->left = new_word;
	new_word->left = before;
	new_word->right = next;

	return new_word;
}

void print(Tnode* tree)
{
	while (tree->left)
		tree = tree->left;
	while (tree) {
		cout << tree->word << ": " << tree->count << '\n';
		tree = tree->right;
	}
}

int main()
{
	Tnode* tree = new Tnode{ "a" };
	Tnode* tree_next = new Tnode{ "c", 0, tree };
	tree->right = tree_next;

	Tnode* tree_new = new Tnode{ "b" };
	insert(tree, tree_new);

	print(tree);
}