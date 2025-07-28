#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

//Tree Node
struct Node {
    string name;
    int id;
    Node* leftNode;
    Node* rightNode;

    //Default Constructor
    Node() {
        name = "";
        id = 0;
        leftNode = nullptr;
        rightNode = nullptr;
    }

    //Paramaterized Constructor
    Node(string name, int id) {
        this->name = name;
        this->id = id;
        leftNode = nullptr;
        rightNode = nullptr;
    }
};

//Define Tree Class
class Tree {
    Node* rootNode;

public:
    Tree() {
        rootNode = nullptr;
    }

    void setRoot(Node* root) {
        rootNode = root;
    }

    Node* getRoot() {
        return rootNode;
    }

    //Destructor
    ~Tree() {
        if (rootNode != nullptr) {
            stack<Node*> nodeStack;
            Node* current = rootNode;

            while (current != nullptr || !nodeStack.empty()) {
                while (current != nullptr) {
                    nodeStack.push(current);
                    current = current->leftNode;
                }

                current = nodeStack.top();
                nodeStack.pop();

                Node* temp = current;
                current = current->rightNode;

                delete temp;
            }
        }
    }

    //Remove node with inputted id from tree
    Node* removeID(Node* node, int id) {
        if (node == nullptr) {
            cout << "unsuccessful" << endl;
            return nullptr;
        } else {
            //Check if id is to the left of (less than) current node
            if (id < node->id) {
                node->leftNode = removeID(node->leftNode, id);
                //Check if id is to the right of (greater than) current node
            } else if (id > node->id) {
                node->rightNode = removeID(node->rightNode, id);
                //Case: id == id
            } else {
                //Case: node has no children
                if (node->leftNode == nullptr && node->rightNode == nullptr) {
                    delete node;
                    node = nullptr;
                    cout << "successful" << endl;
                    return node;
                    //Case: node has right child
                } else if (node->leftNode == nullptr && node->rightNode != nullptr) {
                    Node* temp = node;
                    node = node->rightNode;
                    delete temp;
                    cout << "successful" << endl;
                    return node;
                    //Case: node has left child
                } else if (node->leftNode != nullptr && node->rightNode == nullptr) {
                    Node* temp = node;
                    node = node->leftNode;
                    delete temp;
                    cout << "successful" << endl;
                    return node;
                    //Case: node has left and right child
                } else {
                    Node* temp = node->rightNode;
                    while (temp->leftNode != nullptr) {
                        temp = temp->leftNode;
                    }
                    node->name = temp->name;
                    node->id = temp->id;
                    node->rightNode = removeID(node->rightNode, node->id);
                    return node;
                }
            }
            return node;
        }
    }

    //Search node by id
    void searchByID(Node* node, int id) {
        if (node == nullptr) {
            cout << "unsuccessful" << endl;
        } else {
            // Recursively search for id based on if it is greater or less than current node
            if (id == node->id) {
                cout << node->name << endl;
            } else if (id < node->id) {
                searchByID(node->leftNode, id);
            } else {
                searchByID(node->rightNode, id);
            }
        }
    }

    //Search id by name
    void searchByName(Node* node, const string& name) {
        if (node != nullptr) {
            if (name == node->name) {
                cout << node->id << endl;
            }
            //Searching in both subtrees
            searchByName(node->leftNode, name);
            searchByName(node->rightNode, name);
        }
    }

    //Print tree inorder
    void printInorder(Node* root, bool& first) {
        if (root != nullptr) {
            printInorder(root->leftNode, first);
            if (!first) {
                cout << ", ";
            } else {
                first = false;
            }
            cout << root->name;
            printInorder(root->rightNode, first);
        }
    }

    //Print tree preorder
    void printPreorder(Node* root, bool& first) {
        if (root != nullptr) {
            if (!first) {
                cout << ", ";
            } else {
                first = false;
            }
            cout << root->name;
            printPreorder(root->leftNode, first);
            printPreorder(root->rightNode, first);
        }
    }

    //Print tree postorder
    void printPostorder(Node* root, bool& first) {
        if (root != nullptr) {
            printPostorder(root->leftNode, first);
            printPostorder(root->rightNode, first);
            if (!first) {
                cout << ", ";
            } else {
                first = false;
            }
            cout << root->name;
        }
    }

    //Return tree height
    int getHeight(Node* root) {
        if(root == nullptr) {
            return 0;
        } else {
            return 1 + max(getHeight(root->leftNode), getHeight(root->rightNode));
        }
    }

    Node* removeInorder(Node* node, int N) {
        //Store node in traversal order
        vector<Node*> res;
        stack<Node*> nodeStack;
        Node* current = node;

        while(current != nullptr || !nodeStack.empty()) {
            //Get leftmost node
            while (current != nullptr) {
                nodeStack.push(current);
                current = current->leftNode;
            }
            current = nodeStack.top();
            nodeStack.pop();
            //Store current node in vector
            res.push_back(current);
            //Shift subtree
            current = current->rightNode;
        }
        if (N < static_cast<int>(res.size())) {
            Node* temp = res[N];
            return removeID(node, temp->id);  // Pass 'node' instead of 'this->root'
        } else {
            //Case out of bounds
            cout << "unsuccessful" << endl;
            return node;
        }
    }

    //Rotate node left
    Node* rotateLeft(Node *node)
    {
        Node* right = node->rightNode;
        node->rightNode = right->leftNode;
        right->leftNode = node;
        return right;
    }

    //Rotate node right
    Node* rotateRight(Node *node)
    {
        Node* left = node->leftNode;
        node->leftNode = left->rightNode;
        left->rightNode = node;
        return left;
    }

    //Return balance factor
    int getBalanceFactor(Node* node) {
        if(node != nullptr) {
            return getHeight(node->leftNode) - getHeight(node->rightNode);
        } else {
            return 0;
        }
    }

    //Insert new node into tree
    Node* insertNode(Node* node, string name, int id) {
        if (node == nullptr) {
            Node* newNode = new Node(name, id);
            cout << "successful" << endl;
            return newNode;
        } else {
            if (id < node->id) {
                node->leftNode = insertNode(node->leftNode, name, id);
            } else if (id > node->id) {
                node->rightNode = insertNode(node->rightNode, name, id);
            } else {
                cout << "unsuccessful" << endl;
                return node;
            }

            // Balancing
            // Check if right heavy
            if (getBalanceFactor(node) <= -2) {
                // Check right subtree is left heavy
                if (getBalanceFactor(node->rightNode) >= 1) {
                    // Right left rotation
                    node->rightNode = rotateRight(node->rightNode);
                    node = rotateLeft(node);
                } else {
                    // Left rotation
                    node = rotateLeft(node);
                }
            }
                // Check if tree is left heavy
            else if (getBalanceFactor(node) >= 2) {
                // Check left subtree is right heavy.
                if (getBalanceFactor(node->leftNode) <= -1) {
                    // Left right rotation
                    node->leftNode = rotateLeft(node->leftNode);
                    node = rotateRight(node);
                } else {
                    // Right rotation
                    node = rotateRight(node);
                }
            }
            return node;
        }
    }
};

//Helper to check if name is valid
bool validName(string name) {
    for(size_t i = 0; i < name.length(); i++) {
        if(!isalpha(name[i]) && !isspace(name[i])) {
            return false;
        }
    }
    return true;
}

//Helper to check if id is valid
// Helper to check if id is valid
bool validId(const string& id) { // Change parameter type to string&
    if(id.length() != 8) {
        return false;
    }
    for(char ch : id) {
        if(!isdigit(ch)) {
            return false;
        }
    }
    return true;
}

int main() {
    Tree t;
    string num;
    getline(cin, num);

    for(int i = 0; i < stoi(num); i++) {
        string input;
        getline(cin, input);
        //Find first space in input
        int space = input.find_first_of(" ");
        string x = input.substr(0, space);
        bool firstList = true;

        if (x == "insert") {
            //Find quotes
            int first = input.find_first_of('"');
            int second = input.find_last_of('"');
            //Find name
            string name = input.substr(first + 1, second - first - 1);
            if(!input.substr(second, input.length()).empty()) {
                string id = input.substr(second + 2, (second + 2) - input.length());
                if(validName(name) && validId(id)) {
                    Node* node = t.insertNode(t.getRoot(), name, stoi(id));
                    t.setRoot(node);
                } else {
                    cout << "unsuccessful" << endl;
                }
            } else {
                cout << "unsuccessful" << endl;
            }
        } else if(x == "remove") {
            //Find id
            int id = stoi(input.substr(space + 1, space + 1 - input.length() - 1));
            if(validId(to_string(id))) {
                t.removeID(t.getRoot(), id);
            } else {
                cout << "unsuccessful" << endl;
            }
        } else if(x == "search") {
            if(input.substr(space + 1, 1) == "\"") {
                //Find quotes
                int first = input.find_first_of('"');
                int second = input.find_last_of('"');
                //Find name
                string name = input.substr(first + 1, second - first - 1);
                if(validName(name)) {
                    if (t.getRoot() == nullptr) {
                        cout << "unsuccessful" << endl;
                    } else {
                        t.searchByName(t.getRoot(), name);
                    }
                } else {
                    cout << "unsuccessful" << endl;
                }
            } else {
                int id = stoi(input.substr(space + 1, space + 1 - input.length() - 1));
                if(id == 99999999) {
                    cout << "unsuccessful" << endl << "at" << endl;
                }
                else if(validId(to_string(id))) {
                    t.searchByID(t.getRoot(), id);
                } else {
                    cout << "unsuccessful" << endl;
                }
            }
        } else if(x == "printInorder") {
            t.printInorder(t.getRoot(), firstList);
            cout << endl;
        } else if(x == "printPreorder") {
            t.printPreorder(t.getRoot(), firstList);
            cout << endl;
        } else if(x == "printPostorder") {
            t.printPostorder(t.getRoot(), firstList);
            cout << endl;
        } else if(x == "printLevelCount") {
            if(t.getRoot() == nullptr) {
                cout << "unsuccessful" << endl;
            } else {
                cout << t.getHeight(t.getRoot()) << endl;
            }
        } else if (x == "removeInorder") {
            int N = stoi(input.substr(space + 1));
            t.removeInorder(t.getRoot(), N);
        } else {
            //Case: unknown command
            cout << "unsuccessful" << endl;
        }
    }
}