#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
const int MAX_SIZE = 5;//testing 
using namespace std;
//Doubly Linked List Node
class node{
    public:
    string key, value;
    
    node* next;
    node* prev;
    node(string key, string value){this->key = key; this->value = value; next = nullptr; prev = nullptr;}
};
class database{
    private:
        node* head;
        node* tail;
        unordered_map<string, vector<string>> data;
        public:
        
        bool insert(const string& key, const string& value){

        }


};
int main(){
    
    
    database db;
    string key, value,x;
    cin>>x>>key>>value;
    if(x=="SET"){
        node n(key,value);
        cout<<n.key;
    }
    return 0;
}