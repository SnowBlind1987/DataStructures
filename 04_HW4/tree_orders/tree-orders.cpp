#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;
using std::endl;
class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }


  void in_order(int i) {
	int l,r;
	int lind, rind;
	lind=this->left[i];
	rind=this->right[i];
    if (lind!=-1){	
	in_order(lind);}
	cout<<key[i]<<" ";
	if (rind!=-1){
	in_order(rind);}
	if (lind==-1 and rind==-1){
		return;	
	}
  }

  

  void pre_order(int i) {
   	int l,r;
	int lind, rind;
	cout<<key[i]<<" ";
	lind=this->left[i];
	rind=this->right[i];
	if (lind==-1 and rind==-1){
		return;	
	}
	if (lind!=-1){
	pre_order(lind);}
	if (rind!=-1){
	pre_order(rind);}
 
  }
  void post_order(int i) {
    vector<int> result;    
    int l,r;
	int lind, rind;
		lind=this->left[i];
	rind=this->right[i];
	
	if (lind!=-1){
	post_order(lind);}
	if (rind!=-1){
	post_order(rind);}
	cout<<key[i]<< " "; 
    if (lind==-1 and rind==-1){
		return;
	}
  }

};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  t.in_order(0);
	cout<<endl;
  t.pre_order(0);
  cout<<endl;
  t.post_order(0);
  //print(t.in_order(0));
  //print(t.pre_order());
  //print(t.post_order());
  return 0;
}
