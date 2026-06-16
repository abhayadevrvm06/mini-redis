#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <mutex>

namespace lru_cache {
class Node{
    public:
    std::string key, value;
    
    Node* next;
    Node* prev;
    Node(std::string key, std::string value){this->key = key; this->value = value; next = nullptr; prev = nullptr;}
};
class database{

        private:
        mutable std::mutex mtx;
        mutable Node* head = nullptr;
        mutable Node* tail = nullptr;
        std::unordered_map<std::string, Node*> data;

        public:
        //function declaration
        void insert(const std::string& key, const std::string& value);
        void GET(std::string key) const;
        void DEL(std::string key);
        void PRINT() const;
        void moveToHead(Node *node) const ;
        void saveToFile(const std::string& filename);
        void loadFromFile(const std::string& filename);
        void CLEAR();
        ~database() {
        Node* curr = head;
        while (curr) {
            Node* next = curr->next;
            delete curr;
            curr = next;
    }
}
};
}

#endif