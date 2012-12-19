#include<iostream>
using namespace std;

struct Node{
	int value;
	Node *left;
	Node *right;
	Node *parent;
	int balance;
};

class AVL{
	Node *root;

	public:
	AVL(){
		root = NULL;
	}

	Node* getRoot(){
		return root;
	}

	int calculateBalance(Node *ptr){
		if (ptr == NULL){
			return 0;
		}
		int left = calculateBalance(ptr->left);
		int right = calculateBalance(ptr->right);
		
		ptr->balance = right - left;
		
		if (left > right){
			return (1 + calculateBalance(ptr->left));
		}else
			return (1 + calculateBalance(ptr->right));
	}

	Node* singleRightRotation(Node *ptr){
		Node *rightChild = ptr->right;
		Node *tempLeftChild = NULL;
		if (rightChild->left)
			tempLeftChild = rightChild->left;
		rightChild->left = ptr;
		rightChild->parent = ptr->parent;
		ptr->parent = rightChild;
		rightChild->parent!=NULL?((rightChild->value > rightChild->parent->value)?rightChild->parent->right=rightChild:rightChild->parent->left=rightChild):NULL;

		if (tempLeftChild){
			ptr->right = tempLeftChild;
			tempLeftChild->parent = ptr;
		}
		else
			ptr->right = NULL;
		if (ptr == root)
			root = rightChild;
		return rightChild;
	}

	Node* singleLeftRotation(Node *ptr){
		Node *leftChild = ptr->left;
		Node *tempRightChild = NULL;
		if (leftChild->right)
			tempRightChild = leftChild->right;
		leftChild->right = ptr;
		leftChild->parent = (ptr->parent==NULL)?NULL:ptr->parent;
		ptr->parent = leftChild;
		leftChild->parent!=NULL?((leftChild->value > leftChild->parent->value)?leftChild->parent->right=leftChild:leftChild->parent->left=leftChild):NULL;
		if (tempRightChild){
			ptr->left = tempRightChild;
			tempRightChild->parent = ptr;
		}
		else 
			ptr->left = NULL;
		if (ptr == root)
			root = leftChild;
		return leftChild;
	}

	Node* doubleLRRotation(Node *ptr){
		Node *rightChild = ptr->right;
		singleLeftRotation(rightChild);
		calculateBalance(root);
		Node *newCurrent = singleRightRotation(ptr);
		return newCurrent;
	}

	Node* doubleRLRotation(Node *ptr){
		Node *leftChild = ptr->left;
		singleRightRotation(leftChild);
		calculateBalance(root);
		Node *newCurrent = singleLeftRotation(ptr);
		return newCurrent;
	}

	void balanceTree(Node *newNode, Node *oldNode=NULL){
		Node *current = newNode;
		while (current && current->parent!=NULL){
			if ((current->balance <=1 && current->balance >= -1 && current->parent!=NULL) || oldNode == NULL){
				oldNode = current;
				current = current->parent;
			}
			if (current->balance ==-2 && (current->balance + oldNode->balance) <= -2){
				cout<<"Left single rotation around "<<current->value<<endl;
				current = singleLeftRotation(current);
				calculateBalance(root);
				inorder(root);
				current = current->parent;
				oldNode = current;
			} else if (current->balance == 2 && (current->balance + oldNode->balance) >= 2){
				cout<<"Right single rotation around "<<current->value<<endl;
				cout<<"Current Node balance"<<current->balance<<endl;
                		oldNode?cout<<"Old Node balance"<<oldNode->value<<endl:cout<<"None"<<endl;
				current = singleRightRotation(current);
                                calculateBalance(root);
                                inorder(root);
                                current = current->parent;
                                oldNode = current;
			} else if (current->balance == 2 && (current->balance + oldNode->balance) == 1){
				cout<<"Double LR rotation"<<endl;
				current = doubleLRRotation(current);
                                calculateBalance(root);
                                inorder(root);
                                current = current->parent;
				cout<<"New Root"<<root->value<<endl;
                                oldNode = current;
			} else if (current->balance == -2 && (current->balance + oldNode->balance) == -1){
				cout<<"Double RL rotation"<<endl;
				current = doubleRLRotation(current);
                                calculateBalance(root);
                                inorder(root);
                                current = current->parent;
                                cout<<"New Root"<<root->value<<endl;
                                oldNode = current;
			}
		}
	}

	void insert(int val){
		Node *ptr = root;
		Node *temp = new Node;
		Node *parent;
		Node *newNode;
		temp->value = val;
		temp->left = NULL;
		temp->right = NULL;
		temp->balance = 0;
		temp->parent = NULL;
		if (ptr == NULL){
			root = temp;
			return;
		}
		while (ptr!=NULL){
                        parent = ptr;
                        if (val<ptr->value){
                                ptr = ptr->left;
                        }
                        else if (val>ptr->value){
                                ptr = ptr->right;
                        }
                }
		temp->parent = parent;
                if (val < parent->value){
                        parent->left = temp;
			newNode = parent->left;
		}
                else{
                        parent->right = temp;
			newNode = parent->right;
		}
		calculateBalance(root);
		cout<<"New node"<<newNode->value<<endl;
		balanceTree(newNode);
		return;
	}

	void inorder(Node *ptr){
		if (ptr == NULL)
			return;
		inorder(ptr->left);
		cout<<ptr->value<<"->"<<ptr->balance<<endl;
		inorder(ptr->right);
	}
};

int main(void){
	AVL avl;
	avl.insert(10);
	avl.insert(5);
	avl.insert(20);
	avl.insert(3);
	avl.insert(15);
	avl.insert(8);
	avl.insert(25);
	avl.insert(7);
	avl.insert(2);
	avl.insert(9);
	avl.insert(6);
}

