#include <iostream>
#include <stack>
#include <string>

using namespace std;


struct LaundryLoad {
    string clientName;
    string loadType; 
    int loadID;      
};


void processLoad(LaundryLoad& load, stack<string>& processSteps) {
    cout << "Processing load for " << load.clientName << " (" << load.loadType << ") with ID " << load.loadID << endl;

    
    processSteps.push("Washing");
    processSteps.push("Drying");
    processSteps.push("Folding");
}


void correctStep(stack<string>& processSteps) {
    if (!processSteps.empty()) {
        cout << "Correcting step: " << processSteps.top() << endl;
        processSteps.pop();
    } else {
        cout << "No steps to correct." << endl;
    }
}

int main() {
    
    LaundryLoad load1 = {"Client A", "Whites", 1};

    
    stack<string> processSteps;

  
    processLoad(load1, processSteps);

    
    correctStep(processSteps);

   
    cout << "Load processing completed." << endl;

    return 0;
}
