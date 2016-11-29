#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;

struct Query {
    string type, s;
    size_t ind;
};

struct node{
	node():pNext(NULL){}
	string myString;
	node* pNext;
};

struct HEAD{
	HEAD():pNext(NULL){}
	node* pNext;
};

class LinkedList{
	private:
	HEAD* myHead;
	bool searchString(node* pN, string const &str){
		if (pN->myString==str){
			return true;
		}
		if (pN->pNext==NULL){
			return false
		}

		return searchString(pN->pNext,str);
	}

	public:
	LinkedList(){
		cout<<"Inside the constructor\n"
		myHead=new HEAD;
		myHead->pNext=NULL;
	}
	~LinkedList(){
		node* currNode=myHead->pNext;
		while(currNode!=NULL){
			node* tmp=currNode->pNext;
			delete currNode;
			currNode=tmp;
		}
		delete myHead;
	}
	bool searchString(string const & s){
		if (myHead->pNext==NULL){
			return false;
		}else{
			return searchString(myHead->pNext,s);
		}
	}

	void insertString(string const & s){
		if (this->searchString(s)){
			return;
		}else{
			node* oldPoint=myHead->pNext;
			myHead->pNext=new node;
			myHead->pNext.myString=s;
			myHead->pNext->pNext=oldPoint;
			oldPoint=NULL;
		}
	}
	

};

class QueryProcessor {
    int bucket_count;
    // store all strings in one vector
    vector<LinkedList> buckets;
    size_t hash_func(const string& s) const {
        static const size_t multiplier = 263;
        static const size_t prime = 1000000007;
        unsigned long long hash = 0;
        for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
            hash = ((hash * multiplier + s[i]) % prime) % bucket_count;
        return hash;
    }

public:
    QueryProcessor(int bucket_count){
		this->bucket_count=bucket_count;
		this->buckets.resize(bucket_count);
		for (int i=0;i<bucket_count;i++){
			buckets[i]
		}
	}

    Query readQuery() const {
        Query query;
        cin >> query.type;
        if (query.type != "check")
            cin >> query.s;
        else
            cin >> query.ind;
        return query;
    }

    
};

int main() {
    std::ios_base::sync_with_stdio(false);
    int bucket_count;
    cin >> bucket_count;
    QueryProcessor proc(bucket_count);
    proc.processQueries();
    return 0;
}
