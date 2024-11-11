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
        currentLevel =1;
        // Initializing random generator
        gen = std::mt19937(rd());
        dis = std::uniform_real_distribution<>(0.0, 1.0);

        head = new Node(maxLvl)
    }

    ~SkipList() {
        Node* current = head;
        while(current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
    }
};
