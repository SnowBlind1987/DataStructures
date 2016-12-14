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

	void update(Node* curNode){
		if (curNode==NULL){
			return;
		}
		curNode->sum = curNode->key + (curNode->left != NULL ?
					 	curNode->left->sum : 0ll) + (curNode->right != NULL ? 
						curNode->right->sum : 0ll);
		if (curNode->left!=NULL){
			curNode->left->parent=curNode;
		}
		if (curNode->right!=NULL){
			curNode->right->parent=curNode;
		}
	}	
	void rotate(Node* curNode){
		Node* parent=curNode->parent;
		if (parent==NULL) {return};
		Node* grandParent=parent->parent;
		Node* tmp=NULL;
		//Right rotation case
		if (parent->right==curNode){
			tmp=curNode->left;
			curNode->left=parent;
			parent->right=tmp;
			tmp==NULL;
		}else{
			tmp=curNode->right;
			curNode->right=parent;
			parent->left=tmp;
			tmp=NULL;
		}
		update(parent);
		update(curNode);
		curNode->parent=grandParent;
		if (grandParent!=NULL){
			if (grandParent->right==parent){
				grandParent->right=curNode;
			}else{
				grandParent->left=curNode;
			}
		}	
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
			rotate(curNode);
		}
		//zig zig case
		//if curNode is parent's left child,
		//the parent has to be Grandparent's left child
		//Vise verse with right child case 
		if (grandParent->left==parent and parent->left==curNode){
			rotate(curNode->parent);
			rotate(curNode);
		}else if(grandParent->right ==parent and parent->right==curNode){
			rotate(curNode->parent);
			rotate(curNode);
		}

		//zig zag case
	 	if (grandParent->left==parent and parent->right==curNode){
			rotate(curNode);
			rotate(curNode);
		}else if(grandParent->right==parent and parent->left==curNode){
			rotate(curNode);
			rotate(curNode);
		}		
		splay(curNode);
	}

	Node* find(Node* curNode,int key){
		if (curNode->key==key){
			return curNode;
		}
		if (key<curNode->key){
			if (curNode->left==NULL){
				return curNode;
			}else{
				find(curNode->left,key);
			}
		}
		if (key>curNode->key){
			if (curNode->right==NULL){
				return curNode;
			}else{
				find(curNode->right,key);
			}
		}
	}

	Node* leftDesc(Node* curNode){
		if (curNode->left==NULL){
			return curNode;
		}else{
			leftDesc(curNode->left);
		}
	}
	Node* rightAnc(Node* curNode){
		if (curNode==this->root){
			return NULL;//if you're here this is the largest node, no next
		}
		if (curNode->key<curNode->parent->key){
			return curNode;
		}else{
			rightAnc(curNode->parent);
		}
	}
	Node* next(Node* curNode){
		if (curNode->right!=NULL){
			return leftDesc(curNode->right);
		}else{
			return rightAnc(curNode);
		}
	}
	//this* is always the left tree
	SplayTree* split(int key,SplayTree* leftTree){
		Node* foudNode=find(leftTree->root,key);
		splay(foundNode);
		if (key<leftTree->root->key){
			if (leftTree->root->left==NULL){
				return;
			}
			SplayTree* rightTree=new SplayTree;
			rightTree->root=foundNode;
			leftTree->root=rightTree->root->left;
			leftTree->root->parent=NULL;
			rightTree->root->left==NULL;
			update(rightTree->root);
            return rightTree;
		}else{
			if (this->root->right==NULL){
				return;
			}
			SplayTree* rightTree=new SplayTree;
			rightTree->root=leftTree->root->right;
			rightTree->root->prant=NULL;
			leftTree->root->right=NULL;
			update(leftTree->root);
            return rightTree;
		}
	}

	void merge(SplayTree*& leftTree, SplayTree* & rightTree){
		int largest=2147483647;
		Node* foundNode=NULL;
		foundNode=leftTree->find(leftTree->root,largest);
		leftTree->splay(foundNode);
		leftTree->root->right=rightTree->root;
		update(left->root);
		right->root=NULL;
		delete rightTree;
		rightTree=NULL;
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
		Node* newNode=NULL;
		if (this->root==NULL){
			newNode=new Node;
			newNode->key=key;
			newNode->sum=key;
			this->setRoot(newNode);
			newNode=NULL;
			return;	
		}
		SplayTree* rightTree=NULL;
		rightTree=split(key,this);
		
		if (rightTree==NULL){
			if (this->root->right==NULL and this->root->key!=key){
				newNode=new Node;
				newNode->key=key;
				newNode->sum=key;
				this->root->right=newNode;
				update(this->root);
			}else if(this->root->left==NULL and this->root->key!=key){
				newNode=new Node;
				newNode->key=key;
				newNode->sum=key;
				this->root->left=newNode;
				update(this->root);
			}
			return;
		}
		if (this->root->right==NULL and this->root->key!=key){
			newNode=new Node;
			newNode->key=key;
			newNode->sum=key;
			this->root->right=newNode;
			update(this->root);
			merge(this,rightTree);
		}else if(rightTree->root->left==NULL and rightTree->root->key!=key){
			newNode=new Node;
			newNode->key=key;
			newNode->sum=key;
			rightTree->root->left=newNode;
			update(rightTree->root);
			merge(this,rightTree);
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
    SplayTree* split(int key){
        return split(key,this);
    }

    void merge(splayTree* mergeTree){
        merge(this,mergeTree);
    }
	int range_sum(int l, int r){
		SplayTree* rightTree=NULL;
		rightTree=split(r,this);
		SplayTree* middleTree=NULL;
		middleTree=split(l,this);
		int sum= middleTree->root->sum;
		if (this->root->key==l){
			sum+=this->root->key;//if the key that is equal got cut away
		}
		merge(middleTree,rightTree);
		merge(this,middleTree);
		return sum;
	}

};
