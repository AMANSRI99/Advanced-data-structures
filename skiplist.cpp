#include <vector>
#include <string>
#include <iostream>

using namespace std;
template<typename K,typename V>
class SkipList {
private:
    struct Node {
        K Key;
        V Value;
        vector<Node*>forward;
        bool isSentinel;

        Node(K k, V v, int level) {
            Key = k;
            Value = v;
            forward = vector<Node*>(level, nullptr);
            isSentinel = false;
        }
        
        Node(int level) {
            forward = vector<Node*>(level,nullptr);
            isSentinel = true;
        }

        bool lessThan(const K& otherKey) const {//const K& because we don't want Key to be copied when passing between functions.
            if(isSentinel) {
                return true;
            }
            return Key<otherKey;
        }
    };

    Node* head;
    int maxLevel;
    float probability;
    int currentLevel;
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<> dis;

    int randomLevel() {//method to generate random level for a node.
        int level =1;
        while(dis(gen)<probability && level < maxLevel) {
            level++;
        }
        return level;
    }

public:
    SkipList(int maxLvl =16, float p =0.5) {
        maxLevel = maxLvl;
        probability = p;
        currentLevel =1;//highest level in the node.
        // Initializing random generator
        gen = std::mt19937(rd());
        dis = std::uniform_real_distribution<>(0.0, 1.0);

        head = new Node(maxLvl);
    }

    ~SkipList() {
        Node* current = head;
        while(current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
    }

    Node* search(const K& key) {
        Node* current = head;
        for(int level = currentLevel -1; level >= 0; level--) {
            while(current->forward[level] != nullptr && current->forward[level]->lessThan(key)) {
                current = current->forward[level];
            }
        }
        //moving to next node at level 0 since it's a potential match.
        current = current->forward[0];

        //checking if we found the key.
        if(current != nullptr && current->isSentinel == false && current->Key==key) {
            return current;
        }
        return nullptr;
    }

    /*the general intuition is that we start at top left and move right untile we find a value that is greater that the the key we want to insert.
    When we do find it,we store(in update array) the last node that was less than our key and we move down to a lesser level and we repeat the same.
    when we have found where to insert our new node, we update the forward pointers of the new node and the last node that was less than our key(to new node).*/
    Node* insert(const K& key, const V& value) {
        vector<Node*>update(maxLevel,nullptr);

        Node* currNode = head;

        for(int level=currentLevel-1;level>=0;level--) {
            while(currNode->forward[level]!=nullptr && currNode->forward[level]->lessThan(key)) {
                currNode = currNode->forward[level];
            }
            update[level] = currNode;
        }

        currNode = currNode->forward[0];

        if(currNode!=nullptr && currNode->isSentinel==false && currNode->Key==key) {
            currNode->Value = value;
            return currNode;
        }

        int newLevel = randomLevel();
        if(newLevel>currentLevel) {
            for(int level = currentLevel;level<newLevel;level++) {
                update[level] = head; //it should be the head node which should pe pointing to all the newer levels.
            }
            currentLevel = newLevel;
        }

        Node* newNode = new Node(key,value,newLevel);
        for(int level = 0;level<newLevel;level++) {
            newNode->forward[level] = update[level]->forward[level];
            update[level]->forward[level] = newNode;
        }
        return newNode;
    }
};
