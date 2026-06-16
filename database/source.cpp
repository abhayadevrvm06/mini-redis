#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
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

        private:

        Node* head = nullptr;
        Node* tail = nullptr;
        unordered_map<string, Node*> data;

        public:

        void insert(const string& key, const string& value){
            if(data.find(key) != data.end()){
                data[key]->value = value;
                moveToHead(data[key]);
                return;
            }
            else{
            auto *temp = new Node(key, value);
                if(!head){
                    head = temp;
                    tail = temp;
                }else{
                    temp->next = head;
                    head->prev = temp;
                    head = temp;
                }
                if(data.size() >= MAX_SIZE){
                    DEL(tail->key);
                }
                data[key] = temp;
        }
    }
        void GET(string key){
            if(data.find(key) != data.end()){
                moveToHead(data[key]);
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
    void moveToHead(Node *node){
        if(node == head) return;
        if(node->prev) node->prev->next = node->next;
        if(node->next) node->next->prev = node->prev;
        if(node == tail) tail = node->prev;
        node->next = head;
        node->prev = nullptr;
        if(head) head->prev = node;
        head = node;
    }
    void saveToFile(const string& filename){
        ofstream file("file.txt");
        if(file.is_open()){
            Node* temp = head;
            while(temp){
                file << temp->key << ":" << temp->value << endl;
                temp = temp->next;
            }
            file.close();
        }
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
        if(ss >> key >> value){

            db.insert(key, value);
        }
    }
    else if(command=="GET"){
        if(ss >> key){
            db.GET(key);
        }else {
        cout << "Error: GET requires a key" << endl;
    }
    }
    else if(command=="DEL"){
        if(ss >> key){
            db.DEL(key);
        }
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