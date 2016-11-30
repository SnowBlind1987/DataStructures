#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
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
			return false;
		}

		return searchString(pN->pNext,str);
	}
	void deleteString(node* pN,string const& str){
		node* next=pN->pNext;
        if (next==NULL){
			return;
		}else{
			if (next->myString==str){
				node* theOneAfter=next->pNext;
				pN->pNext=theOneAfter;
				delete next;
				next = NULL;
				theOneAfter=NULL;
				return;
			}else{
				next==NULL;
				deleteString(pN->pNext,str);
			}
		}
	}
    void writeAll(node* pN){
        std::cout<<pN->myString<<" ";
        if (pN->pNext!=NULL){
			writeAll(pN->pNext);
		}else{
			cout<<endl;
			return;
		}
    }
	public:
	LinkedList(){
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
			myHead->pNext->myString=s;
			myHead->pNext->pNext=oldPoint;
			oldPoint=NULL;
		}
	}

	void deleteString(string const & str){
		if (myHead->pNext==NULL){
			return;
		}else if(myHead->pNext->myString==str){
			node* currNode=myHead->pNext;
			node* oneAfter=myHead->pNext->pNext;
			myHead->pNext=oneAfter;
			delete currNode;
			currNode=NULL;
			oneAfter==NULL;
			return;
		}else{
			deleteString(myHead->pNext,str);
		}
	}
    void writeAll(){
        if (myHead->pNext==NULL){
            std::cout<<"\n";
			return;
        }else{
            writeAll(myHead->pNext);
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
            hash = ((hash * multiplier + s[i]) % prime) ;
        return hash%bucket_count;
    }

public:
    QueryProcessor(int bc){
		this->bucket_count=bc;
		this->buckets.resize(bc);
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
	
	void processQuery(Query q){
		if (q.type=="add"){
			int hashVal=hash_func(q.s);
			buckets[hashVal].insertString(q.s);
		}
		if (q.type=="del"){
			int hashVal=hash_func(q.s);
			buckets[hashVal].deleteString(q.s);
		}
		if (q.type=="find"){
			int hashVal=hash_func(q.s);
			if (buckets[hashVal].searchString(q.s)){
				cout<<"yes\n";
			}else{
				cout<<"no\n";
			}
		}
		if (q.type=="check"){
			buckets[q.ind].writeAll();
		}
	}
	
	void processQueries() {
        int n;
        cin >> n;
        for (int i = 0; i < n; ++i)
            processQuery(readQuery());
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
