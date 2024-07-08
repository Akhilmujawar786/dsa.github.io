#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct LaundryJob {
    string clientName;
    int urgency; 
    string jobType;

    LaundryJob(string name, int urgencyLevel, string type)
        : clientName(name), urgency(urgencyLevel), jobType(type) {}
};


struct CompareUrgency {
    bool operator()(LaundryJob const& job1, LaundryJob const& job2) {
        
        return job1.urgency < job2.urgency;
    }
};

int main() {
    
    priority_queue<LaundryJob, vector<LaundryJob>, CompareUrgency> laundryQueue;

   
    laundryQueue.push(LaundryJob("Client A", 5, "Dry Cleaning"));
    laundryQueue.push(LaundryJob("Client B", 10, "Washing"));
    laundryQueue.push(LaundryJob("Client C", 3, "Ironing"));
    laundryQueue.push(LaundryJob("Client D", 7, "Folding"));

    
    while (!laundryQueue.empty()) {
        LaundryJob currentJob = laundryQueue.top();
        laundryQueue.pop();
        cout << "Processing job for " << currentJob.clientName
             << " (" << currentJob.jobType << ") with urgency " << currentJob.urgency << endl;
    }

    return 0;
}
