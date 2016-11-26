#include <iostream>
#include <vector>
#include<unordered_map>
#include <algorithm>
#include <stack>
using namespace std;
struct Node{
	int n_children;
	int id;
	std::vector<Node*> children;
	Node():n_children(0),
		 id(0){}
};

class Tree{
	private:
	Node* root;
	int height;
	std::unordered_map<int,Node*> node_list;
	

	Node* getNode(int nd){
		auto it=this->node_list.find(nd);
		if (it==node_list.end()){
			return NULL;
		}else{
			return it->second;
		}
	}
	void addNode(Node* pNd,int nd){
		this->node_list.insert(make_pair(nd,pNd));
	}

	int computeHeight(Node* nd){
		vector<int> heights;
		if (nd->n_children==0){
			return 1;
		}else{
			int nc=nd->n_children;
			heights.resize(nc);
			for (int i=0;i<nc;i++){
				heights[i]=computeHeight(nd->children[i]);
			}
			
			return 1+*max_element(heights.begin(),heights.end());	
		}
	}
	public:
	Tree(){
		root=NULL;
		height=0;
	}

	

	void Insert(int id, int parent){
		Node* pNode=NULL;
		Node* pChild=NULL;
		int nc;
		//special case if the node is root
		if (parent==-1){
			root=getNode(id);
			if (root==NULL){
				root=new Node;
				root->id=id;
				this->addNode(root,id);
				//cout<<"Creating Root..."<<id<<endl;
				return;
			}else{
				//cout<<"Root already exists: " <<id<<endl;
				return;
			}
		}
		pNode=getNode(parent);
		if (pNode==NULL){
			pNode=new Node;
			pNode->id=parent;
			this->addNode(pNode,parent);
			pNode->n_children++;
			//now see if the child is already in the tree
			pChild=getNode(id);
			if (pChild==NULL){
				nc=pNode->n_children;
				pChild=new Node;
				pChild->id=id;
				this->addNode(pChild,id);
				pNode->children.push_back(pChild);
				//cout<<"Creating parent: "<<parent<<" and child: "<<id<<endl;
			}else{
				pNode->children.push_back(pChild);
				//cout<<"Creating parent: "<<parent<<" but child exists: "<<id<<endl;
			}	
		
		}
    	else{
				
			pNode->n_children++;
			pChild=getNode(id);
			if (pChild==NULL){
				nc=pNode->n_children;
				pChild=new Node;
				pChild->id=id;
				this->addNode(pChild,id);
				pNode->children.push_back(pChild);
				pNode->children[nc-1]->id=id;
				//cout<<"Parent exists: "<<parent<<" but child doesn't: "<<id<<endl;
			}else{
				pNode->children.push_back(pChild);
				//cout<<"Parent exists: "<<parent<<" and child: "<<id<<endl;
			}
		}
		pNode=NULL;
		pChild=NULL;//for safety	
	}

	int ComputeHeight(){
		if (this->root==NULL){
			cout<<"Error, no root"<<endl;
			return -1;
		}
		return this->computeHeight(root);
		
	}
	void Read(){
		int n;
		int parent;
		int id;
		std::vector<Node> nodes;
		
		std::cin>>n;
		for (int i=0;i<n;i++){
			std::cin>>parent;
			this->Insert(i,parent);	
		}	
			
	}

		
};


int main() {
  std::ios_base::sync_with_stdio(0);
  Tree tree;
  tree.Read();
  std::cout << tree.ComputeHeight() << std::endl;
}
