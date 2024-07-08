#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Location {
    int id;
    double x, y;

    Location(int i, double _x, double _y) : id(i), x(_x), y(_y) {}
};

struct Vehicle {
    int capacity;

    Vehicle(int cap) : capacity(cap) {}
};

struct Route {
    vector<int> nodes;
    int totalDemand;

    Route() : totalDemand(0) {}

    void printRoute() const {
        cout << "Route: ";
        for (int node : nodes) {
            cout << node << " ";
        }
        cout << " Total Demand: " << totalDemand << endl;
    }
};

double distance(const Location& loc1, const Location& loc2) {
    return sqrt(pow(loc1.x - loc2.x, 2) + pow(loc1.y - loc2.y, 2));
}

vector<Route> clarkeWrightSavings(const vector<Location>& locations, const vector<Vehicle>& vehicles) {
    int numLocations = locations.size();
    int numVehicles = vehicles.size();

    vector<pair<double, pair<int, int>>> savings;
    for (int i = 0; i < numLocations; ++i) {
        for (int j = i + 1; j < numLocations; ++j) {
            double savingsValue = distance(locations[i], locations[0]) + distance(locations[j], locations[0]) - distance(locations[i], locations[j]);
            savings.push_back({savingsValue, {i, j}});
        }
    }

    sort(savings.begin(), savings.end(), greater<pair<double, pair<int, int>>>());

    vector<Route> routes(numVehicles);
    vector<int> remainingDemand(numLocations, 0);
    for (int i = 0; i < numLocations; ++i) {
        remainingDemand[i] = i == 0 ? 0 : 10;
    }

    for (auto& save : savings) {
        int node1 = save.second.first;
        int node2 = save.second.second;

        int minIncrement = INT_MAX;
        int selectedVehicle = -1;

        for (int v = 0; v < numVehicles; ++v) {
            int capacityLeft = vehicles[v].capacity - routes[v].totalDemand;
            if (capacityLeft >= remainingDemand[node1] && capacityLeft >= remainingDemand[node2]) {
                int currentIncrement = distance(locations[node1], locations[0]) + distance(locations[node2], locations[0]) - distance(locations[node1], locations[node2]);
                if (currentIncrement < minIncrement) {
                    minIncrement = currentIncrement;
                    selectedVehicle = v;
                }
            }
        }

        if (selectedVehicle != -1) {
            routes[selectedVehicle].nodes.push_back(node1);
            routes[selectedVehicle].nodes.push_back(node2);
            routes[selectedVehicle].totalDemand += remainingDemand[node1] + remainingDemand[node2];
            remainingDemand[node1] = remainingDemand[node2] = 0;
        }
    }

    for (int i = 1; i < numLocations; ++i) {
        if (remainingDemand[i] > 0) {
            int minIncrement = INT_MAX;
            int selectedVehicle = -1;

            for (int v = 0; v < numVehicles; ++v) {
                int capacityLeft = vehicles[v].capacity - routes[v].totalDemand;
                if (capacityLeft >= remainingDemand[i]) {
                    double currentIncrement = distance(locations[i], locations[0]);
                    if (currentIncrement < minIncrement) {
                        minIncrement = currentIncrement;
                        selectedVehicle = v;
                    }
                }
            }

            if (selectedVehicle != -1) {
                routes[selectedVehicle].nodes.push_back(i);
                routes[selectedVehicle].totalDemand += remainingDemand[i];
                remainingDemand[i] = 0;
            }
        }
    }

    return routes;
}

void printRoutes(const vector<Route>& routes) {
    for (const auto& route : routes) {
        route.printRoute();
    }
}

int main() {
    vector<Location> locations = {
        {0, 0.0, 0.0},   // Depot (laundry facility)
        {1, 5.0, 5.0},   // Client 1 location
        {2, 10.0, 10.0}, // Client 2 location
        {3, 3.0, 8.0}    // Client 3 location
    };

    vector<Vehicle> vehicles = {
        {20}, // Vehicle 1 with capacity 20
        {15}  // Vehicle 2 with capacity 15
    };

    vector<Route> routes = clarkeWrightSavings(locations, vehicles);

    cout << "Optimal Routes:" << endl;
    printRoutes(routes);

    return 0;
}
