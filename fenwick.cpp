#include <iostream>
#include <vector>

using namespace std;

class FenwickTree {
private:
    vector<int> tree;
    int size;

public:
    FenwickTree(int n) {
        size = n + 1;
        tree.assign(size, 0);
    }

    
    void update(int index, int delta) {
        while (index < size) {
            tree[index] += delta;
            index += index & -index; 
        }
    }

    int query(int index) {
        int sum = 0;
        while (index > 0) {
            sum += tree[index];
            index -= index & -index; 
        }
        return sum;
    }

  
    int rangeQuery(int l, int r) {
        return query(r) - query(l - 1);
    }
};

class WashingMachineManager {
private:
    int numMachines;
    vector<int> loads;
    vector<int> capacities;
    FenwickTree fenwickTree;

public:
    WashingMachineManager(int n) : numMachines(n), fenwickTree(n) {
        loads.assign(n + 1, 0);
        capacities.assign(n + 1, 0);
    }

    
    void addLoad(int machineIdx, int load) {
        if (loads[machineIdx] + load <= capacities[machineIdx]) {
            fenwickTree.update(machineIdx, load);
            loads[machineIdx] += load;
            cout << "Load " << load << " added to Machine " << machineIdx << endl;
        } else {
            cout << "Machine " << machineIdx << " has reached capacity." << endl;
        }
    }

   
    bool canAccommodateLoad(int machineIdx, int load) {
        return loads[machineIdx] + load <= capacities[machineIdx];
    }
};

int main() {
    int numMachines = 5;
    WashingMachineManager manager(numMachines);

  
    manager.capacities = {0, 10, 15, 12, 20, 8}; 

    
    manager.addLoad(1, 5);
    manager.addLoad(2, 8); 

 
    cout << "Machine 3 can accommodate load of 10? " << (manager.canAccommodateLoad(3, 10) ? "Yes" : "No") << endl;

    return 0;
}
