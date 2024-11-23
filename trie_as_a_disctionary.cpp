#include <string>
#include <iostream>

class TrieNode {
    public:
        TrieNode* childNode[26];
        bool isEnd;
        TrieNode() {
            isEnd = false;
            for(int i=0;i<26;i++){
                childNode[i] = nullptr;
            }
        }
};

class Trie {
    public:
        TrieNode* root;
        Trie() {
            root = new TrieNode();
        }
        void insert(std::string word) {
            TrieNode* currNode = root;
            for(int i=0;i<word.size();i++){
                if(currNode->childNode[word[i]-'a'] == nullptr){
                    currNode->childNode[word[i]-'a'] = new TrieNode();
                }
                currNode = currNode->childNode[word[i]-'a'];
            }
            currNode->isEnd = true;
        }

        bool search(std::string word) {
            TrieNode* currNode = root;
            for(int i=0;i<word.size();i++){
                if(currNode->childNode[word[i]-'a']==nullptr){
                    return false;
                }
                else{
                    currNode = currNode->childNode[word[i]-'a'];
                }
            }
            if(currNode->isEnd==true){
                return true;
            }
            return false;
        }

        bool startsWith(std::string prefix) {
            TrieNode* currNode = root;
            for(int i=0;i<prefix.size();i++){
                if(currNode->childNode[prefix[i]-'a']==nullptr){
                    return false;
                }
                else{
                    currNode = currNode->childNode[prefix[i]-'a'];
                }
            }
            return true;
        }
};

int main() {
    Trie* obj = new Trie();
    obj->insert("apple");
    bool param_2 = obj->search("apple");
    bool param_3 = obj->startsWith("app");
    std::cout<<param_2<<param_3;
    return 0;
}