#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <climits>
#include <algorithm> // For std::find
using namespace std;

struct City {
    string name;
    int cost;
    int reward;
};

struct Connection {
    string from;
    string to;
    int travel_cost;
};

// Modified DFS to track the path of maximum reward
int maxRewardDFS(
    const string& current,
    const string& destination,
    int remaining_points,
    unordered_map<string, City>& city_info,
    unordered_map<string, vector<pair<string, int>>>& graph,
    unordered_map<string, unordered_map<int, int>>& memo,
    vector<string>& current_path,
    vector<string>& best_path
) {
    if (remaining_points < 0) return INT_MIN; // Invalid path
    if (current == destination) {
        // Update the best path and return the reward for the destination city
        best_path = current_path;
        return 0;
    }

    // Check memoization
    if (memo[current].count(remaining_points)) return memo[current][remaining_points];

    int max_reward = INT_MIN;

    for (auto& neighbor : graph[current]) {
        string next_city = neighbor.first;
        int travel_cost = neighbor.second;

        if (std::find(current_path.begin(), current_path.end(), next_city) == current_path.end()) { // Avoid cycles
            current_path.push_back(next_city); // Add city to the current path
            int reward = maxRewardDFS(
                next_city,
                destination,
                remaining_points - travel_cost - city_info[next_city].cost,
                city_info,
                graph,
                memo,
                current_path,
                best_path
            );
            current_path.pop_back(); // Backtrack

            if (reward != INT_MIN) { // Only consider valid paths
                int total_reward = reward + city_info[next_city].reward;
                max_reward = max(max_reward, total_reward);
            }
        }
    }

    // Cache the result
    return memo[current][remaining_points] = max_reward;
}


int main() {
    // Input: Cities
    vector<City> cities = {
        {"CITY_A", 300, 1000},
        {"CITY_B", 500, 900},
        {"CITY_C", 250, 1500},
        {"CITY_D", 100, 600}
    };

    // Input: Connections
    vector<Connection> connections = {
        {"CITY_A", "CITY_B", 250},
        {"CITY_A", "CITY_D", 300},
        {"CITY_B", "CITY_C", 500}
    };

    string origin = "CITY_A";
    string destination = "CITY_B";
    int available_points = 100;


    unordered_map<string, City> city_info;
    for (auto& city : cities) {
        city_info[city.name] = city;
    }


    unordered_map<string, vector<pair<string, int>>> graph;
    for (auto& connection : connections) {
        graph[connection.from].emplace_back(connection.to, connection.travel_cost);
        graph[connection.to].emplace_back(connection.from, connection.travel_cost); // Bidirectional
    }

    unordered_map<string, unordered_map<int, int>> memo;

    // Path tracking
    vector<string> current_path = {origin};
    vector<string> best_path;

    // Find maximum reward using DFS with memoization
    int max_reward = maxRewardDFS(
        origin,
        destination,
        available_points - city_info[origin].cost,
        city_info,
        graph,
        memo,
        current_path,
        best_path
    );

    // Output the result
    if (max_reward == INT_MIN){
        cout << "Max Reward: " << city_info[origin].reward << endl;
        cout << "Best Path: "<< city_info[origin].name;

    }
    else{
        max_reward+=city_info[origin].reward;
        cout << "Max Reward: " << max_reward << endl;
        cout << "Best Path: ";
        for (size_t i = 0; i < best_path.size(); ++i) {
            cout << best_path[i];
            if (i < best_path.size() - 1) cout << " -> ";
        }
    }
    cout << endl;

    return 0;
}
