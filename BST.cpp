#include<iostream>
#include<stack>
#include<queue>
using namespace std;

struct Node{
    int data;
    int count;
    Node* left;
    Node* right;

    Node(int value): data(value),count(1),left(nullptr),right(nullptr){}
};

// =========================================================================	

Node* insert(Node* root, int value){
    Node* newnode = new Node(value);

    if(root == nullptr)
       return newnode;
    else{
        Node* temp = root;
        Node* parent;

        while(temp != nullptr){

            parent = temp;
            if(value < temp->data)
                temp = temp->left;
            else if(value > temp->data)
                temp = temp->right;
            else{
                temp->count++;
                delete newnode;
                return root;
            }

        }

        if(parent->data > value)
           parent->left = newnode;
        else
           parent->right = newnode;
        
        return root;
    }

}

// =========================================================================	

void inorderDisplay(Node* root){
    if(root != nullptr){
        inorderDisplay(root->left);
        cout<<root->data<<" ";
        inorderDisplay(root->right);
    }
}

// =========================================================================	

int duplicate(Node* root, int key){
    Node* temp = root;
    while(temp != nullptr && temp->data != key){
        if(key < temp->data)
            temp = temp->left;
        else
          temp = temp->right;
    }
    return temp->count;
}

// =========================================================================	

void displaylevel(Node* root){
    if(root == nullptr){ 
	cout<<"Empty\n"; 
	return;
    }

    stack<Node*> st1, st2;
    Node*temp;
    st1.push(root);

   while(!st1.empty()){

    while(!st1.empty()){
         cout<<st1.top()->data<<" ";
         st2.push(st1.top()); 
	    st1.pop();      
    }

	cout<<endl;

    while(!st2.empty()){
         if(st2.top()->right != nullptr){st1.push(st2.top()->right);}
         if(st2.top()->left != nullptr){st1.push(st2.top()->left);}
         st2.pop();
    }
  }

}



void levelWise(Node* root){
	queue<Node*> q;
	q.push(root);

	while(!q.empty()){
		Node* temp = q.front();
		q.pop();
		
		cout<<temp->data<<" ";

		if(temp->left != nullptr){
			q.push(temp->left);
		}
		if(temp->right != nullptr){
			q.push(temp->right);
           }
     }
}
	
// =========================================================================	

bool Search(Node* root, int key){
	if(root == nullptr){
		 return false;
	}
	if(root->data == key){
		return true;
	}
	
	if(key < root->data){
		return Search(root->left,key);		
	}
	else if(key > root->data){
		return Search(root->right, key);
	}
} 

// =========================================================================	

Node* findMin(Node* root){
	while(root->left != nullptr){
		root = root->left;
	}
	return root;
}


Node* Delete(Node* root, int key){

	if(key < root->data){
		root->left = Delete(root->left, key);
	}

	else if(key > root->data){
		root->right = Delete(root->right,key);
	}

	else{  // Node Found

		if(root->left == nullptr && root->right==nullptr){      // leaf node
			return nullptr;
		}

		else if(root->left == nullptr||root->right == nullptr){  // one child

			if(root->left==nullptr){ 
				Node* temp = root->right;
				delete root;
				return temp ;
			}
			if(root->right==nullptr){ 
				Node* temp = root->left;
				delete root;
				return temp;
			}
		} 

		else{
			Node* temp = findMin(root->right);
			root->data = temp->data;
			root->right = Delete(root->right,temp->data);	
		}
	}
	cout<<"\nDeleted Successfully!\n";
	return root;
}

// =========================================================================	

int calcDepth(Node* root, int d=0){
   	if(root == nullptr){
		return d;
	}
	int Ldepth = calcDepth(root->left, d+1);
	int Rdepth = calcDepth(root->right, d+1);

	return max(Ldepth,Rdepth);
}

// =========================================================================	

void DisplayLeaf(Node* root){
	if(root==nullptr){return;}
    if(root->left == nullptr && root->right==nullptr){
       cout<<root->data<<" ";
	}
	DisplayLeaf(root->left);
	DisplayLeaf(root->right);
} 

// =========================================================================	

Node* CopyTree(Node* root){
	if(root==nullptr){
 		return nullptr;
	}
	Node* copyroot = new Node(root->data);
	copyroot->left = CopyTree(root->left);
	copyroot->left = CopyTree(root->right);

	return copyroot;
}
// =========================================================================	




int main(){
    Node* root = nullptr;
    int ch,value,key;

    root = insert(root,34);
    root = insert(root,46);
    root = insert(root,23);
    root = insert(root,42);
    root = insert(root,11);
    root = insert(root,31);

    do{
        cout<<"\n=================\nBinary Search Tree\n===================\n";
        cout<<"\n1.Insert \n2.Inorder \n3.Duplicate \n4.LevelWise \n5.Search \n6.Delete \n7.Depth of Tree \n8.Leaf Nodes \n9.Parent Nodes \n10.Mirror Image \n11.Copy Tree \n0.Exit \n";
        cout<<"\nEnter Choice :";
        cin>>ch;
        switch(ch){
            case 1:
                 cout<<"\nEnter Value to Insert :";
                 cin>>value;
                 root = insert(root,value);
                 break;

            case 2:
                 cout<<"\nInorder Traversal :";
                 inorderDisplay(root);
                 break;

            case 3: cout<<"Enter key :";
                    cin>>key;
                    cout<<"No. of Duplicates of "<<key<<" = "<<duplicate(root,key);
                    break;

		case 4: cout<<"\nLevelWise : \n";
			displaylevel(root);
			//levelWise(root);
			break;

		case 5: int key;
			 cout<<"Enter data to Search :";
			 cin>>key;

			if(Search(root,key)){cout<<"\nData is Present in tree\n";}
			else{cout<<"\nData not Found\n";}
			break;

		case 6: int data;
			 cout<<"Enter data to Delete :";
			 cin>>data;

			root = Delete(root,data);
			break;

		case 7: cout<<"Depth of Tree : "<<calcDepth(root);
				cout<<endl;
				break;

		case 8: cout<<"Leaf Nodes :\n";
				DisplayLeaf(root);
				break;

		case 11: //Node* copyRoot = CopyTree(root);
				//inorderDisplay(copyRoot);
                 	break;
		
                
            case 0 : cout<<"\nExiting....";
                     break;

            default :
                cout<<"\nPlease Enter valid Choice....";

        }
    }while(ch != 0);

}
