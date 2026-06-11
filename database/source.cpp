#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
using namespace std;
const int MAX_SIZE = 5;//testing 
//Doubly Linked List Node
class Node{
    public:
    string key, value;
    
    Node* next;
    Node* prev;
    Node(string key, string value){this->key = key; this->value = value; next = nullptr; prev = nullptr;}
};
class database{
    
        
        public:
        Node* head = nullptr;
        Node* tail = nullptr;
        unordered_map<string, Node*> data;
        void insert(const string& key, const string& value){
            auto *temp = new Node(key, value);
                if(!head){
                    head = temp;
                    tail = temp;
                }else{
                    temp->next = head;
                    head->prev = temp;
                    head = temp;
                }
                data[key] = temp;
                
        }
        void GET(string key){
            if(data.find(key) != data.end()){
                cout<<data[key]->value<<endl;
            }else{
                cout<<"Key not found"<<endl;
            }
        }
        void DEL(string key){
            if(data.find(key) != data.end()){
                Node* temp = data[key];
                if(temp->prev) temp->prev->next = temp->next;
                if(temp->next) temp->next->prev = temp->prev;
                if(temp == head) head = temp->next;
                if(temp == tail) tail = temp->prev;
                data.erase(key);
                delete temp;
            }
        }
        void PRINT(){
            Node* temp = head;
        while(temp) {
            cout << temp->key << ":" << temp->value << " <-> ";
            temp = temp->next;
            }
        cout << "nullptr" << endl;
}
};
int main(){
    database db;
    while(true){
    string line,command,key,value;
    getline(cin,line);
    stringstream ss(line);
    ss >> command;

    if(command=="SET"){        
        ss >> key >> value;
        db.insert(key, value);
    }
    else if(command=="GET"){
        ss >> key;
        db.GET(key);
    }
    else if(command=="DEL"){
        ss >> key;
        db.DEL(key);
    }
    else if(command == "PRINT"){
        db.PRINT();
    }
    
    else if(command == "EXIT"){
        break;
    }
    }
    return 0;
}