#include<iostream>
using namespace std;

struct Node {
	int value;
	Node *left;
	Node *right;
};

class BST {
	Node *root;
	
	public:
	BST(){
		root = NULL;	
	}

	void insert(int val){
		Node *temp = new Node;
		Node *parent;
		temp->value = val;
		temp->left = NULL;
		temp->right = NULL;
		if (root == NULL){
			root = temp;
			return;
		}
		Node *ptr = root;
		while (ptr!=NULL){
			parent = ptr;
			if (val<ptr->value){
				ptr = ptr->left;
			}
			else if (val>ptr->value){
				ptr = ptr->right;
			}
			else{
				return;
			}
		}
		if (val < parent->value)
			parent->left = temp;
		else
			parent->right = temp;
		return;
	}

	Node* getRoot(){
		return root;
	}

	void preorder(Node *ptr){
		if (ptr == NULL)
			return;
		cout<<ptr->value<<endl;
		preorder(ptr->left);
		preorder(ptr->right);
	}

	void postorder(Node *ptr){
		if (ptr == NULL)
			return;
		postorder(ptr->left);
		postorder(ptr->right);
		cout<<ptr->value<<endl;
	}

	void inorder(Node *ptr){
		if (ptr == NULL)
			return;
		inorder(ptr->left);
		cout<<ptr->value<<endl;
		inorder(ptr->right);
	}

	int findDepth(Node *ptr){
		if (ptr == NULL)
			return 0;
		if (findDepth(ptr->left) > findDepth(ptr->right)){
			return (1 + findDepth(ptr->left));
		}
		else{
			return (1 + findDepth(ptr->right));
		}
	}

	void search(Node *ptr, int value){
		if (ptr == NULL)
		{
			cout<<"Value not found"<<endl;
			return;
		}
		if (ptr->value == value){
			cout<<"Value found"<<endl;
			return;
		}
		if(value < ptr->value){
			search(ptr->left, value);
		}
		else{
			search(ptr->right, value);
		}
	}	

	Node* findInorderPredecessor(Node *ptr){
		Node *maxNode;
		while (ptr->right != NULL){
			maxNode = ptr;
			ptr = ptr->right;
		}
		return maxNode;
	}

	void deleteNode(Node *ptr, int value, Node *parent){
		if (ptr == NULL)
			return;
		if (ptr->value == value){
			if (ptr->left == NULL && ptr-> right == NULL){
				if (ptr->value < parent->value)
					parent->left = NULL;
				else
					parent->right = NULL;
        			delete ptr;
        			return;
			}else if (ptr->right == NULL){
				if (ptr->value < parent->value)
                                        parent->left = ptr->left;
                                else
                                        parent->right = ptr->left;
        			delete ptr;
        			return;
			}else if (ptr->left == NULL){
        			if (ptr->value < parent->value)
                                        parent->left = ptr->right;
                                else
                                        parent->right = ptr->right;
                                delete ptr;
        			return;
			}else{
        			Node *predecessorParent = findInorderPredecessor(ptr->left);
				Node *predecessor = predecessorParent->right;
        			ptr->value = predecessor->value;
				if (predecessor->left!=NULL){
					predecessor = predecessor->left;
					predecessorParent->right = predecessor;
				}
				else{
					predecessorParent->right = NULL;
					delete predecessor;
				}
        			return;
			}

		}
		if (value < ptr->value){
			parent = ptr;
			deleteNode(ptr->left, value, parent);
		} else {
			parent = ptr;
			deleteNode(ptr->right, value, parent);
		}
	}
};

int main(void){
	BST bst;
	bst.insert(10);
	bst.insert(2);
	bst.insert(11);
	bst.insert(22);
	bst.insert(25);
	bst.insert(3);
	bst.insert(9);
	bst.insert(8);
	cout<<"Inorder"<<endl;
	bst.inorder(bst.getRoot());
	cout<<"Preorder"<<endl;
	bst.preorder(bst.getRoot());
	cout<<"Postorder"<<endl;
	bst.postorder(bst.getRoot());
	int height = bst.findDepth(bst.getRoot());
	cout<<"Height of this tree is "<<height<<endl;
	bst.search(bst.getRoot(), 22);
	bst.search(bst.getRoot(), 30);
	bst.deleteNode(bst.getRoot(), 3, NULL);
	bst.inorder(bst.getRoot());
}
