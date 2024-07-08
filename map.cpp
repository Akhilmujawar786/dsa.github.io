#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;


class PaymentSystem {
private:
    unordered_map<string, double> payments;

public:
    
    void processPayment(const string& staffID, double amount) {
        payments[staffID] += amount;
    }

    
    double getTotalPaymentForStaff(const string& staffID) {
        if (payments.find(staffID) != payments.end()) {
            return payments[staffID];
        } else {
            return 0.0;
        }
    }
};

int main() {
    PaymentSystem paymentSystem;

 
    paymentSystem.processPayment("staff001", 100.50);
    paymentSystem.processPayment("staff002", 200.75);
    paymentSystem.processPayment("staff001", 150.25);

    
    cout << "Total payment for staff001: $" << paymentSystem.getTotalPaymentForStaff("staff001") << endl;
    cout << "Total payment for staff002: $" << paymentSystem.getTotalPaymentForStaff("staff002") << endl;
    cout << "Total payment for staff003: $" << paymentSystem.getTotalPaymentForStaff("staff003") << endl;

    return 0;
}
