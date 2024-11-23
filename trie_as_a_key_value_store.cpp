#include <string>
#include <iostream>
#include <optional>

template<typename T>
class TrieNode {
    public: 
        TrieNode* childNode[26];
        bool isEnd;
        std::optional<T>value;

        TrieNode() {
            isEnd = false;
            for(int i=0;i<26;i++){
                childNode[i] = nullptr;
            }
            value = std::nullopt;
        }
};

template<typename T>
class TrieMap {
    public:

        TrieNode<T>* root;
        TrieMap() {
            root = new TrieNode<T>();
        }

        void insert(const std::string& key, const T& val) {// const keyword is to allow read-only access.
            TrieNode<T>* currNode = root;
            for(int i=0;i<key.size();i++) {
                if(currNode -> childNode[key[i]-'a'] == nullptr){
                    currNode->childNode[key[i]-'a'] = new TrieNode<T>();
                }
                currNode = currNode->childNode[key[i]-'a'];
            }
            currNode->isEnd = true;
            currNode->value = val;
        }

        std::optional<T> get(const std::string& key) {
            TrieNode<T>* currNode = root;
            for(int i=0;i<key.size();i++) {
                if(currNode->childNode[key[i]-'a'] == nullptr) {
                    return std::nullopt;
                }
                currNode = currNode->childNode[key[i]-'a'];
            }
            if(currNode->isEnd) {
                return currNode->value;
            }
            return std::nullopt;
        }

        bool contains(const std::string& key) {
            TrieNode<T>* currNode = root;
            for(int i=0;i<key.size();i++) {
                if(currNode->childNode[key[i]-'a'] == nullptr) {
                return false;
                }
                currNode = currNode->childNode[key[i]-'a'];
            }
            return currNode->isEnd;
        }
        
        bool startsWith(const std::string& prefix) {
            TrieNode<T>* currNode = root;
            for(int i = 0; i < prefix.size(); i++) {
                if(currNode->childNode[prefix[i]-'a'] == nullptr) {
                    return false;
                }
                currNode = currNode->childNode[prefix[i]-'a'];
            }
            return true;
        }
};

int main() {
    TrieMap<std::string>* phoneBook = new TrieMap<std::string>();
    
    phoneBook->insert("Aman", "123-456-7890");
    phoneBook->insert("Silvanus", "098-765-4321");
    
    auto amansNumber = phoneBook->get("Aman");
    if(amansNumber) {
        std::cout << "Aman's number: " << *amansNumber << std::endl;
    }
    
    TrieMap<int>* scores = new TrieMap<int>();
    
    scores->insert("aman", 95);
    scores->insert("kshitij", 87);
    
    if(scores->contains("aman")) {
        auto amanScore = scores->get("aman");
        if(amanScore) {
            std::cout << "Aman's score: " << *amanScore << std::endl;
        }
    }
    return 0;
}