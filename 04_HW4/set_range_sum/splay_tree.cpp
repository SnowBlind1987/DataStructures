#include<iostream>
struct Node{
	Node: parent(NULL),left(NULL),right(NULL),key(0);{}
	int key;
	Node* parent;
	Node* left;
	Node* right;
};


class SplayTree{
	private:
	Node* root;

	Node* find(Node* curNode, int key){
		if (curNode->key==key){
			return curNode;
		}
		}
		if (key<curNode->key){
			if (curNode->left==NULL){
				return curNode;
			}else{
				Node* left=find(curNode->left,key);
			}
		}
		if (key>curNOde->key){
			if(curNode->right==NULL){
				return curNode;
			}else{
				Node* right=find(curNode->right,key);
			}
		}
	}

	void rotateRight(Node* curNode){
		Node* parent=curNode->parent;
		Node* grandParent=parent->parent;
		Node* tmp=NULL;
		if (grandParent->left==parent){
			grandParent->left=curNode;
			curNode->parent=grandParent;
			tmp=curNode->right;
			curNode->right=parent;
			parent->parent=curNode;
			parent->left=tmp;
			tmp=NULL;
		}
		else if (grandParent->right==parent){
			grandParent->right=curNode;
			curNode->parent=grandParent;
			tmp=curNode->right;
			curNode->right=parent;
			parent->parent=curNode;
			parent->left=tmp;
			tmp=NULL;
		}else{
			std::cout<<"Broken Tree! GTFO\n";
			return;
		}
	}

	void splay(Node* curNode){
		Node* parent=curNode->parent;
		if (parent==NULL) {
			return;
		}
		Node* grandParent=parent->parent;
		//zig zig case
		//if curNode is parent's left child,
		//the parent has to be Grandparent's left child
		//Vise verse with right child case 
				

	}

}
