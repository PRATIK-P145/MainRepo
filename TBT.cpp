# include<iostream>
using namespace std;

struct Node{
	int data;
	Node* left;
	Node* right;
	bool isThr;

	Node(int d){
		data = d;
		left = right = nullptr;
		isThr = false;
	}
};

Node* insert(Node* root, int value){
	Node* newnode = new Node(value);
	if(root == nullptr){
		root = newnode;
		return root;
	}

	Node* current = root;
	Node* parent = nullptr;

	while(current != nullptr){
		parent = current;
		if(value < root->data){
			if(current->left == nullptr){
				break;
			}
			current = current->left;
		}
		else{
			if(current->isThr)
				break;
			current = current->right;
		}
	}

	if(value<parent->data){
		parent->left = newnode;
		newnode->right = parent;
		newnode->isThr = true;
	}
	else{
		newnode->right = parent->right;
		parent->right = newnode;
		parent->isThr = false;
		newnode->isThr = true;
	}

	return root;
}

//=============================================================================

Node* LeftMost(Node* root){
	Node* temp = root;
	while(temp && temp->left){
		temp = temp->left;
	}
	return temp;
}

void inorder(Node* root){
	Node* current = LeftMost(root);
	while(current != nullptr){

		cout<<current->data<<" ";

		if(current->isThr){
			current = current->right;
		}

		else{
			current = LeftMost(current->right);
		}
	}

}

void preorder(Node* root){
	Node* current = root;
	while(current){
		cout<<current->data<<" ";
		if(current->left){ current = current->left;}
		else if(!current->isThr){
			current = current->right;
		}
		else{
			current = current->right;
		}
	}
}

int main(){
    Node* root = nullptr;
    root = insert(root,20);
    root =insert(root,10);
    root =insert(root,30);
    root =insert(root,5);
    root =insert(root,15);
    root =insert(root,25);
    root =insert(root,35);

    cout << "InOrder Traversal: ";
    inorder(root);

    cout << "PreOrder Traversal: ";
    preorder(root);

    return 0;


}
