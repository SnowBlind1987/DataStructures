#include <iostream>
#include <vector>
#include <algorithm>
#include<limits>
#include<queue>
using namespace std;
class PriorityQueue{
	private:
	int size;//pair<time, thread>
    int max_size;
	vector<pair<long, int> > Hvect;//pair<time, thread>
	int getParent(int i){
		int div=(i-1)/2;
		if (i==0) {
			return -1;
		}else{
			return div;
		}
	}
	int getLeftChild(int i){
		return 2*i+1;
	}
	int getRightChild(int i){
		return 2*i+2;
	}

	void siftUp(int i){
		if (this->size==0)return;
		while (i>=0 and Hvect[getParent(i)].first>=Hvect[i].first 
    				and Hvect[getParent(i)].second>Hvect[i].second) {

			if ( Hvect[getParent(i)].first>Hvect[i].first){
				swap(Hvect[getParent(i)],Hvect[i]);
				i=getParent(i);
			}else if(Hvect[getParent(i)].second>Hvect[i].second ){
				swap(Hvect[getParent(i)],Hvect[i]);
				i=getParent(i);
			}
		}
	}
	void siftDown(int i){
		int minInd=i;
		int l=getLeftChild(i);
		//*****Left Child*****************
		if(l<this->size and Hvect[l].first<Hvect[minInd].first){
			minInd=l;
		}
		if (l<this->size and Hvect[l].first==Hvect[minInd].first){
			if (Hvect[l].second<Hvect[minInd].second){
				minInd=l;
			}
		}
		//******End Left Child**************
		//******Right Child*****************
		int r=getRightChild(i);
		if(r<this->size and Hvect[r]<Hvect[minInd]){
			minInd=r;
		}
		if (r<this->size and Hvect[r].first==Hvect[minInd].first){
			if(Hvect[r].second<Hvect[minInd].second){
				minInd=r;
			}
		}
		//******End Right Child*************
		if (i!=minInd){
			swap(Hvect[i],Hvect[minInd]);
			siftDown(minInd);
		}
	}
	public:
    PriorityQueue(){}
    PriorityQueue(int max){
        this->max_size=max;
        this->Hvect.resize(max);
		for (int i=0;i<max;i++){
			Hvect[i]=make_pair(0,-1);
		}
    }
	void setMaxSize(int n){
		this->max_size=n;
		this->size=0;
		Hvect.resize(n);
	}
	int getSize(){
		return this->size;
	}

    void insert(long priority,int thread){
        if (this->size==this->max_size){
            return;
        }else{
            this->Hvect[size]=make_pair(priority,thread);
            this->siftUp(size);
            this->size++;
        }

    }

    pair<long,int> extractMin(){
	pair<long,int> max=Hvect[0];
        swap(Hvect[0],Hvect[size-1]);
        this-size--;
        this->siftDown(0);
        return max;
    }

	pair<long,int> getMin(){
		return Hvect[0];
	}
    
    void remove(int i){
        Hvect[i].first=std::numeric_limits<long >::max();
        this->siftUp(i);
        pair<long,int> trash;
		trash=this->extractMin();
    }
    
    void changePriority(long prior,int i){
        long old_prior=Hvect[i].first;
        Hvect[i].first=prior;
		if (old_prior==prior) return;
        if (prior>old_prior){
            this->siftDown(i);
        }else{
            this->siftUp(i);
        }
    }
	void showAll(){
		cout<<"The tree looks like this:\n";
		for (int i=0;i<this->size;i++){
			cout<<Hvect[i].first<<" "<<Hvect[i].second<<endl;
		}
	}
};

class JobQueue{
	private:
	int n_jobs;
	int n_threads;
	PriorityQueue time;
	queue<long> jobs;
	void initTree(){
		time.setMaxSize(n_threads);
		for (int i=0;i<n_threads;i++){
			time.insert(0,i);
		}
	}
	public:
	//intiialize the JobQue with max values for the heap
	JobQueue(){}
	 
	void readData() {
		int m;
		cin >> n_threads >> n_jobs;
		for(int i = 0; i <n_jobs; ++i){
			int currJob;
			cin >> currJob;
			jobs.push(currJob);
		}
		this->initTree();
	}
	
	void schedule(){
		pair<long,int> currNode;
		while(not jobs.empty()){
			currNode=time.getMin();
			long currTime=currNode.first;
			int currThread=currNode.second;
			long duration=jobs.front();
			jobs.pop();
			cout<<currThread<<" "<<currTime<<endl;
			time.changePriority(currTime+duration,0);
			//time.showAll();
		}	
	}
};

int main(){
	JobQueue queue;
	queue.readData();
	queue.schedule();
	return 0;
}
