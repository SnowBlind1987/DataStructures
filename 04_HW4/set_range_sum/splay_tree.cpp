#include <cstdio>
#include<iostream>
#include<stack>

using std::stack;
using std::cout;
using std::endl;
struct Node{
	Node(): parent(NULL),left(NULL),right(NULL),key(-1),sum(-1){}

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
        if (curNode==NULL) return;

		Node* parent=curNode->parent;
		if (parent==NULL) {return;}
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
        if (curNode==NULL) return;
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
		if (grandParent!=NULL){
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
		}
		splay(curNode);
	}

	Node* find(Node* curNode,int key){
        if (curNode==NULL) return NULL;
		if (curNode->key==key){
			return curNode;
		}
		if (key<curNode->key){
			if (curNode->left==NULL){
				return curNode;
			}else{
				return find(curNode->left,key);
			}
		}
		if (key>curNode->key){
			if (curNode->right==NULL){
				return curNode;
			}else{
				return find(curNode->right,key);
			}
		}
	}

	Node* leftDesc(Node* curNode){
        if (curNode==NULL) return NULL;

		if (curNode->left==NULL){
			return curNode;
		}else{
			return leftDesc(curNode->left);
		}
	}
	Node* rightAnc(Node* curNode){
        if (curNode==NULL) return NULL;
		if (curNode==this->root){
			return NULL;//if you're here this is the largest node, no next
		}
		if (curNode->key<curNode->parent->key){
			return curNode->parent;
		}else{
			return rightAnc(curNode->parent);
		}
	}
	Node* next(Node* curNode){
        if (curNode==NULL) return NULL;
		if (curNode->right!=NULL){
			return leftDesc(curNode->right);
		}else{
			return rightAnc(curNode);
		}
	}

	//this* is always the left tree
	SplayTree* split(int key,SplayTree* leftTree){
		Node* foundNode=NULL;

		foundNode=find(leftTree->root,key);
		if (foundNode==NULL) return NULL;
		splay(foundNode);
		if (key<leftTree->root->key){
			if (leftTree->root->left==NULL){
				return NULL;
			}
			SplayTree* rightTree=new SplayTree;
			rightTree->root=foundNode;
			leftTree->setRoot(rightTree->root->left);
			rightTree->root->left=NULL;
            update(leftTree->root);
			update(rightTree->root);
            return rightTree;
		}else if(key>=leftTree->root->key){
			if (leftTree->root->right==NULL){
				return NULL;
			}
			SplayTree* rightTree=new SplayTree;
			rightTree->setRoot(leftTree->root->right);
			leftTree->root->right=NULL;
            update(rightTree->root);
            update(leftTree->root);
            return rightTree;
		}
	}

	void merge(SplayTree* leftTree, SplayTree* rightTree){
		if (rightTree==NULL){
			return;
		}
		int largest=2147483647;
		Node* foundNode=NULL;
		foundNode=leftTree->find(leftTree->root,largest);
		leftTree->splay(foundNode);
		leftTree->root->right=rightTree->root;
		update(leftTree->root);
		rightTree->root=NULL;
		delete rightTree;
		rightTree=NULL;
	}
    bool isRoot(Node* curNode){
        if (this->root==curNode){
            return true;
        }else{
            return false;
        }
    }
	void del(Node* curNode,int key){
	    if (curNode==NULL) return;	
		Node* foundNode=find(this->root,key);
		splay(foundNode);
        if (foundNode->key!=key) return;
        //if the tree consists of only root
        if (isRoot(foundNode)){
            Node* leftNode=this->root->left;
            Node* rightNode=this->root->right;
            if (leftNode==NULL and rightNode==NULL){
                delete this->root;
                this->root=NULL;
                return;
            }
		}
		Node* nextNode=next(foundNode);
		if (nextNode!=NULL){
			splay(nextNode);
			splay(foundNode);
            this->setRoot(nextNode);
            this->root->left=foundNode->left;
            update(this->root->left);
            update(this->root);
            delete foundNode;
			foundNode=NULL;	
			nextNode=NULL;
		}else {
            this->splay(foundNode);
            this->setRoot(foundNode->left);
            this->update(this->root);
            delete foundNode;
			foundNode=NULL;
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

	~SplayTree(){
		if (this->root==NULL) return;
		stack<Node*> need2del;
		need2del.push(this->root);
		Node* curNode;
		curNode=NULL;
		while(not need2del.empty()){
			curNode=need2del.top();

			if (curNode->right==NULL and curNode->left==NULL){
				need2del.pop();
				if (curNode->parent!=NULL){
					if (curNode==curNode->parent->right){
						curNode->parent->right=NULL;
					}else{
						curNode->parent->left=NULL;
					}
				} 
                //cout<<"Deleting: "<<curNode->key<<endl;
			    delete curNode;
                curNode=NULL;
				if (not need2del.empty()){
					curNode=need2del.top();	
				}
			}
			if (need2del.empty()) continue;

			if (curNode->left!=NULL){
				need2del.push(curNode->left);
			}
			if (curNode->right!=NULL){
				need2del.push(curNode->right);
			}
		}

	}

    Node* getRoot(){
        return this->root;
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
			if (this->root->right==NULL and this->root->key<key){
				if (this->root->key==key) return;
				newNode=new Node;
				newNode->key=key;
				newNode->sum=key;
				this->root->right=newNode;
				update(this->root);
			}else if(this->root->left==NULL and this->root->key>key){
				if (this->root->key==key) return;
				newNode=new Node;
				newNode->key=key;
				newNode->sum=key;
				this->root->left=newNode;
				update(this->root);
			}
			return;
		}
		if (this->root->right==NULL){
			if (this->root->key!=key){
				newNode=new Node;
				newNode->key=key;
				newNode->sum=key;
				this->root->right=newNode;
				update(this->root);
			}
			merge(this,rightTree);
		}else if(rightTree->root->left==NULL){
			if (rightTree->root->key!=key){
				newNode=new Node;
				newNode->key=key;
				newNode->sum=key;
				rightTree->root->left=newNode;
				update(rightTree->root);
			}
			merge(this,rightTree);
		}
				
	}
	
	bool find(int key){
		Node* foundNode=find(root,key);
        splay(foundNode);
        if (foundNode==NULL){
            return false;
        }
		if (foundNode->key==key){
			return true;
		}else{
			return false;
		}
	}
    SplayTree* split(int key){
        return split(key,this);
    }

    void merge(SplayTree* mergeTree){
        merge(this,mergeTree);
    }

	void del(int key){
		this->del(this->root,key);
	}
	long long range_sum(int l, int r){
        if (this->root==NULL) return 0;
		SplayTree* rightTree=NULL;
		rightTree=split(r,this);
		if (rightTree==NULL and r<this->root->key){
			return 0;
		}
		SplayTree* middleTree=NULL;
		middleTree=split(l,this);
		if (middleTree==NULL){
			if (l>this->root->key){
				this->merge(this,rightTree);
				return 0;
			}else if(l==this->root->key){
				long long sum=this->root->key;
				this->merge(this,rightTree);
				return sum;
			}else{ 
				long long sum =this->root->sum;
				this->merge(this,rightTree);
				return sum;
			}
		}
		long long sum= middleTree->root->sum;
		if (this->root->key==l){
			sum+=this->root->key;//if the key that is equal got cut away
		}
		merge(middleTree,rightTree);
		merge(this,middleTree);
		return sum;
	}

};

int main(){
    const int MODULO = 1000000001;
    SplayTree* tree=NULL;
    tree=new SplayTree;
    int n;
    scanf("%d", &n);
    int last_sum_result = 0;
    for (int i = 0; i < n; i++) {
      char buffer[10];
      scanf("%s", buffer);
      char type = buffer[0];
      switch (type) {
        case '+' : {
          int x;
          scanf("%d", &x);
		  int xx=(x + last_sum_result) % MODULO;
//		  cout<<"Inserting: "<<xx<<endl;
          tree->insert(xx);
        } break;
        case '-' : {
          int x;
          scanf("%d", &x);
		  int xx=(x + last_sum_result) % MODULO;
//		  cout<<"Deleting: "<<xx<<endl;
          tree->del(xx);
        } break;            
        case '?' : {
          int x;
          scanf("%d", &x);
		  int xx=(x + last_sum_result) % MODULO;
//		  cout<<"Searching for: "<<xx<<endl;
          printf(tree->find(xx) ? "Found\n" : "Not found\n");
        } break;
        case 's' : {
          int l, r;
          scanf("%d %d", &l, &r);
		  int ll=(l + last_sum_result) % MODULO;
		  int rr=(r + last_sum_result) % MODULO;
//		  cout<<"Summing: "<<ll<<"and "<<rr<<endl;
          long long res = tree->range_sum(ll,rr) ;
          printf("%lld\n", res);
          last_sum_result = int(res % MODULO);
        }break;
        case 'r' :{
            Node* root=tree->getRoot();
            int key=root->key;
            Node* left=root->left;
            Node* right=root->right;
            printf("%lld\n",key);
            if (left!=NULL){
                printf("%lld\n",tree->getRoot()->left->key);

            }else{
                cout<<"NULL\n";
            }
            if (right!=NULL){
                printf("%lld\n",tree->getRoot()->right->key);
            }else{
                cout<<"NULL\n";
            }
        }
      }
    }
	delete tree;
	tree=NULL;
    return 0;
}
