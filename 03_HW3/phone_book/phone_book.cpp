#include <iostream>
#include <vector>
#include <string>
#include<unordered_map>
using std::string;
using std::vector;
using std::cin;
using std::endl;
using std::cout;
using std::unordered_map;

struct Query {
    string type, name;
    int number;
};

class PhoneBook{
	private:
	vector<Query> queries;
	int  n_queries;
	unordered_map<int,string> htable;	

	void insertNumber(int number, string name){
		auto it=htable.find(number);
		if (it==htable.end()){
			this->htable.insert(make_pair(number,name));
		}else{
			this->htable.erase(it);
			this->htable.insert(make_pair(number,name));
		}
	}

	void delNumber(int number){
		auto it=htable.find(number);
		if (it==htable.end()){
			return;
		}else{
			htable.erase(it);
		}
	}

	string findNumber(int number){
		auto it=htable.find(number);
		if (it==htable.end()){
			string strOut="not found";
			return strOut;
		}else{
			return it->second;
		}
	}
	public:
	void readQueries() {
    	cin >> n_queries;
    	queries.resize(n_queries);
    	for (int i = 0; i < n_queries; ++i) {
    	    cin >> queries[i].type;
    	    if (queries[i].type == "add")
    	        cin >> queries[i].number >> queries[i].name;
    	    else
    	        cin >> queries[i].number;
    	}
	}

	void processQueries(){
		for (int i=0;i<n_queries;i++){
			if (queries[i].type=="add"){
				this->insertNumber(queries[i].number,queries[i].name);
			}
			if(queries[i].type=="del"){
				this->delNumber(queries[i].number);
			}
			if(queries[i].type=="find"){
				string strOut=this->findNumber(queries[i].number);
				cout<<strOut<<endl;
			}
		}
	}
};


/*
void write_responses(const vector<string>& result) {
    for (size_t i = 0; i < result.size(); ++i)
        std::cout << result[i] << "\n";
}




vector<string> process_queries(const vector<Query>& queries) {
    vector<string> result;
    // Keep list of all existing (i.e. not deleted yet) contacts.
    vector<Query> contacts;
    for (size_t i = 0; i < queries.size(); ++i)
        if (queries[i].type == "add") {
            bool was_founded = false;
            // if we already have contact with such number,
            // we should rewrite contact's name
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts[j].name = queries[i].name;
                    was_founded = true;
                    break;
                }
            // otherwise, just add it
            if (!was_founded)
                contacts.push_back(queries[i]);
        } else if (queries[i].type == "del") {
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    contacts.erase(contacts.begin() + j);
                    break;
                }
        } else {
            string response = "not found";
            for (size_t j = 0; j < contacts.size(); ++j)
                if (contacts[j].number == queries[i].number) {
                    response = contacts[j].name;
                    break;
                }
            result.push_back(response);
        }
    return result;
}
*/
int main() {
	PhoneBook pbook;
	pbook.readQueries();
	pbook.processQueries();
    return 0;
}
