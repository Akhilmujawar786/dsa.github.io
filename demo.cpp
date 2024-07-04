struct RadixTreeNode {
    unordered_map<char, RadixTreeNode*> children;
    unordered_set<string> clientIDs;
    bool isEndOfName = false;
};

// Function to insert a client's name and ID into the radix tree
void insertClientName(RadixTreeNode* root, const string& clientName, const string& clientID) {
    RadixTreeNode* node = root;
    for (char c : clientName) {
        if (node->children.find(c) == node->children.end()) {
            node->children[c] = new RadixTreeNode();
        }
        node = node->children[c];
    }
    node->clientIDs.insert(clientID);
    node->isEndOfName = true;
}

// Function to search for client IDs based on the client's name in the radix tree
unordered_set<string> searchClientIDs(RadixTreeNode* root, const string& clientName) {
    RadixTreeNode* node = root;
    for (char c : clientName) {
        if (node->children.find(c) == node->children.end()) {
            return {};  // Client name not found
        }
        node = node->children[c];
    }
    return node->isEndOfName ? node->clientIDs : unordered_set<string>();
}

// Function to insert linens for a client
void insertLinen(unordered_map<string, vector<string>>& linenMap, const string& clientID, const string& linen) {
    linenMap[clientID].push_back(linen);
}

// Function to retrieve linens for a client
vector<string> retrieveLinens(const unordered_map<string, vector<string>>& linenMap, const string& clientID) {
    if (linenMap.find(clientID) != linenMap.end()) {
        return linenMap.at(clientID);
    }
    return {};
}

int main() {
    // Create the root of the radix tree
    RadixTreeNode* root = new RadixTreeNode();
    
    // Hash map to store linens for each client ID
    unordered_map<string, vector<string>> linenMap;

    // Example data insertion
    insertClientName(root, "ClientA", "ID1");
    insertLinen(linenMap, "ID1", "Linen1");
    insertLinen(linenMap, "ID1", "Linen2");

    insertClientName(root, "ClientA", "ID2");
    insertLinen(linenMap, "ID2", "Linen3");

    insertClientName(root, "ClientB", "ID3");
    insertLinen(linenMap, "ID3", "Linen4");

    // Example retrieval
    string clientName = "ClientA";
    unordered_set<string> clientIDs = searchClientIDs(root, clientName);
    cout << "Linens for " << clientName << ":" << endl;
    for (const string& clientID : clientIDs) {
        vector<string> linens = retrieveLinens(linenMap, clientID);
        cout << "  Client ID " << clientID << ": ";
        for (const string& linen : linens) {
            cout << linen << " ";
        }
        cout << endl;
    }

    // Clean up dynamically allocated memory
    // Recursive function to delete all nodes
    function<void(RadixTreeNode*)> deleteTree = [&](RadixTreeNode* node) {
        for (auto& child : node->children) {
            deleteTree(child.second);
        }
        delete node;
    };
    deleteTree(root);

    return 0;
}
