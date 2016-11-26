#
nclude <iostream>
#include <vector>
#include <algorithm>
#include<queue>
using std::vector;
using std::queue;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;
using std::endl;
class Heap{
	private:
	int size;
	vector<int> Hvect;
	queue<pair<int,int>> swaps;
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
		while (i>=0 and Hvect[this->getParent(i)]>Hvect[i]){
			swap(Hvect[getParent(i)],Hvect[i]);
			i=Hvect[getParent(i)];
		}
	}
	void siftDown(int i){
		int minInd=i;
		int l=getLeftChild(i);
		if(l<this->size and Hvect[l]<Hvect[minInd]){
			minInd=l;
		}
		int r=getRightChild(i);
		if(r<this->size and Hvect[r]<Hvect[minInd]){
			minInd=r;
		}
		if (i!=minInd){
			swaps.push(make_pair(i,minInd));
			swap(Hvect[i],Hvect[minInd]);
			siftDown(minInd);
		}
	}
	
	void buildHeap(){
		for (int i=(this->size-1)/2;i>=0;i--){
			this->siftDown(i);
		}
	}
	void showSwap(){
		int n=swaps.size();
		cout<<n<<endl;
		while(not swaps.empty()){
			cout<<swaps.front().first<<" "<<swaps.front().second<<endl;
            swaps.pop();
		}
	}
	
	public:
	void readData() {
    int n;
    cin >> n;
	this->size=n;
    this->Hvect.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> Hvect[i];
  	}
	void solve(){
		this->readData();
		this->buildHeap();
		this->showSwap();
	}


};

int main() {
  std::ios_base::sync_with_stdio(false);
  Heap minHeap;
  minHeap.solve();
  return 0;
}
