#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include "database.hpp"
using namespace std;
using namespace lru_cache;
const int MAX_SIZE = 5; // For testing

void lru_cache::database::insert(const string& key, const string& value){
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
        void lru_cache::database::GET(std::string key) const {
        auto it = data.find(key);
        if (it != data.end()) {

            moveToHead(it->second); 
            std::cout << it->second->value << std::endl;
        } else {
            std::cout << "Key not found" << std::endl;
        }
}
        void lru_cache::database::DEL(string key){
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
        void lru_cache::database::PRINT() const {
            Node* temp = head;
        while(temp) {
            cout << temp->key << ":" << temp->value << " <-> ";
            temp = temp->next;
            }
        cout << "nullptr" << endl;
}
    void lru_cache::database::moveToHead(Node *node) const {
        if(node == head) return;
        if(node->prev) node->prev->next = node->next;
        if(node->next) node->next->prev = node->prev;
        if(node == tail) tail = node->prev;
        node->next = head;
        node->prev = nullptr;
        if(head) head->prev = node;
        head = node;
    }
    void lru_cache::database::saveToFile(const string& filename){
        ofstream file(filename);
        if(file.is_open()){
            Node* temp = tail;
            while(temp){
                file << temp->key << ":" << temp->value << endl;
                temp = temp->prev;
            }
            file.close();
        }
        else{
            cout << "Error: Unable to open file for writing" << endl;
        }
    }
    void lru_cache::database::loadFromFile(const string& filename){
        ifstream file(filename);
        if(file.is_open()){
            string line;
            while(getline(file, line)){
                stringstream ss(line);
                string key, value;
                if(getline(ss, key, ':') && getline(ss, value)){ //delimiter ':'
                    insert(key, value);
                }
            }
            file.close();
        }
        else{
            cout << "Error: Unable to open file for reading" << endl;
        }
    }
    void lru_cache::database::CLEAR(){
        while(head){
            DEL(head->key);
        }
        saveToFile("file.txt");
    }
int main(){
    lru_cache::database db;
    while(true){
    string line,command,key,value;
    getline(cin,line);
    stringstream ss(line);
    ss >> command;
    
    if(command=="SET"){        
        if(ss >> key >> value){

            db.insert(key, value);
        }
        else{
            cout << "Error: SET requires a key and a value" << endl;
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
        else{
            cout << "Error: DEL requires a key" << endl;
        }
    }
    else if(command == "SAVE"){
        db.saveToFile("file.txt");
    }
        else if(command == "LOAD"){
            db.loadFromFile("file.txt");
        }
    else if(command == "PRINT"){
        db.PRINT();
    }
    
    else if(command == "EXIT"){
        break;
    }
    else if(command == "CLEAR"){
        db.CLEAR();
    }
    
}
    return 0;
}