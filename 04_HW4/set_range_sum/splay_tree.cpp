#include<iostream>
#include<string>

using std::cout;

using std::string;
struct Node{
	Node: parent(NULL),left(NULL),right(NULL),key(0),sum(0);{}
	Node* parent;
	Node* left;
	Node* right;
	int key;
	long long sum;

};


class SplayTree{
	private:
	Node* root;

	void setRoot(Node* curNode){
		this->root=curNode;
		this->root->parent=NULL;
	}
	void updateSum(Node* curNode, string dir){
		if (dir=="right"){
			curNode->sum=curNode->parent->sum;
			if (curNode->left!=NULL){
				curNode->parent->sum=curNode->sum-(curNode->key+curNode->left->sum);
			}else{
				curNode->parent->sum=curNode->sum-curNode->key;
			}
			return;

		}else if(dir=="left"){
			curNode->sum=curNode->parent->sum;
			if (curNode->right!=NULL){
				curNode->parent->sum=curNode->sum-(curNode->key+curNode->right->sum);
			}else{
				curNode->parent->sum=curNode->sum-curNode->key;
			}
			return;
		}else{
			cout<<"Wrong string value\n";
			return;			
		}
	}
	void rotateLeft(Node* curNode){
		Node* parent=curNode->parent;
		Node* grandParent=parent->parent;
		Node* tmp=NULL;
		updateSum(curNode,"left");
		tmp=curNode->left;
		curNode->left=parent;
		parent->parent=curNode;
		parent->right=tmp;
		tmp=NULL;
		curNode->parent=grandParent;

		if (grandParent!=NULL){
			if (grandParent->left==parent){
				grandParent->left=curNode;
			}else if(grandParent->right==parent){
				grandParent->right=curNode;
			}else{
				cout<<"Broken Tree! GTFO\n";
				
			}
		}	
		return;
	}

	void rotateRight(Node* curNode){
		Node* parent=curNode->parent;
		Node* grandParent=parent->parent;
		Node* tmp=NULL;
		updateSum(curNode,"right");
		tmp=curNode->left;
		curNode->right=parent;
		parent->parent=curNode;
		parent->right=tmp;
		tmp=NULL;
		curNode->parent=grandParent;

		if (grandParent!=NULL){
			if (grandParent->left==parent){
				grandParent->left=curNode;
			}else if(grandParent->right==parent){
				grandParent->right=parent;
			}else{
				cout<<"Broken Tree! GTFO\n";
			}
		}
		return;	
	}

	void splay(Node* curNode){
		Node* parent=curNode->parent;
		if (parent==NULL) {
			root=curNode;
			return;
		}
		Node* grandParent=parent->parent;
		//zig case
		if (grandParent==NULL){
			if (parent->left==curNode){
				rotateRight(curNode);
			}
			if (parent->right==curNode){
				rotateLeft(curNode);
			}
		}
		//zig zig case
		//if curNode is parent's left child,
		//the parent has to be Grandparent's left child
		//Vise verse with right child case 
		if (grandParent->left==parent and parent->left==curNode){
			rotateRight(curNode->parent);
			rotateRight(curNode);
		}else if(grandParent->right ==parent and parent->right==curNode){
			rotateLeft(curNode->parent);
			rotateLeft(curNode);
		}

		//zig zag case
	 	if (grandParent->left==parent and parent->right==curNode){
			rotateRight(curNode);
			rotateLeft(curNode);
		}else if(grandParent->right==parent and parent->left==curNode){
			rotateLeft(curNode);
			rotateRight(curNode);
		}		
		splay(curNode);
	}
	Node* find(Node* curNode,int key){
		if (curNode->key==key){
			splay(curNode);
			return root;
		}
		if (key<curNode->key){
			if (curNode->left==NULL){
				splay(curNode);
			}else{
				find(curNode->left,key);
			}
		}
		if (key>curNode->key){
			if (curNode->right==NULL){
				splay(curNode);
			}else{
				find(curNode->right,key);
			}
		}
	}
	Node* next(Node* curNode){
		if (curNode->right!=NULL){
			int key2find=curNode->key+1;
			return this->find(curNode->right,key);
		}
	}
	void split(int key,SplayTree*& newTree){
		if (this->root->key>key){
			newTree=new SplayTree;
			Node* tmp=this->root->left;
			this->root->left=NULL;
			newTree->root=NULL;
			tmp=NULL;
		}
		if (this->root->key<key){
			newTree=new SplayTree;
			Node* tmp=this->root->right;
			this->root->right=NULL;
			newTree->root=tmp;
			tmp=NULL;
		}
	}

	void merge(SplayTree* & newTree){
		int largest=2147483647;
		Node* foundNode=NULL;
		if (this->root->left==NULL){
			foundNode=newTree->find(newTree->root,largest);
			newTree->splay(foundNode);
			this->root->left=newTree->root;
			this->root->left->parent=this->root;
			newTree->root=NULL;
			delete newTree;
		}else if(this->root->right==NULL){
			foundNode=this->find(this->root,largest);
			this->splay(foundNode);
			this->root->parent=newTree->root;
			newTree->root->right=this->root->parent;
			newTree->root=NULL;
			delete newTree;
		}
	}
	void insert(Node* curNode,int key){
		Node* foundNode=find(curNode,key);
		if (foundNode->key==key){
			return;//node already exist, do nothing
			this->splay(foundNode);
		}
		SplayTree* newTree=NULL;
		Node* tmp=NULL;
		if (key<this->root->key){
			this->split(key,newTree);
			tmp=new Node;
			tmp->parent=root;
			tmp->left=NULL;
			tmp->right=NULL;
			tmp->key=key;
			tmp->sum=key;
			root->left=tmp;
			root->sum+=key;
			tmp=NULL:
			splay(root->left);
			merge(newTree);
		}
		if (key>foundNode->key){
			this->split(key,newTree)
			tmp=newNode;
			tmp->parent=root;
			tmp->left=NULL;
			tmp->right=NULL;
			tmp->key=key;
			tmp->sum=sum;
			root->right=tmp;
			root->sum+=key;
			tmp=NULL;
			this->splay(root->right);
			merge(NewTree);
		}
	}
	public:
	SplayTree(){
		root=NULL;
	}
	SplayTree(Node* curNode){
		root=curNode;
		root->parent=NULL;
	}
	void insert(int key){
		if (root==NULL){
			root=new Node;
			root->key=key;
			root->sum=key;
		}
	}
	bool find(int key){
		Node* foundNode=find(root,key);
		if (foundNode->key==key){
			return true;
		}else{
			return false;
		}
	}

};
