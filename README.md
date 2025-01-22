# celebto_assignment

Overview
This program helps users plan a trip through cities to maximize rewards within a given budget of available points (time or resources). It uses Depth-First Search (DFS) with memoization to find the optimal path between an origin and destination city.

#Features
City Costs and Rewards: Each city has a visit cost and reward.
Graph Representation: Cities are connected by paths with specific travel costs.
Optimized Calculations: Memoization avoids redundant computations.
Cycle Prevention: Ensures cities are not revisited in the same path.

#Assumptions
Bidirectional Connections: All paths are bidirectional.
Cost Includes Travel: Total cost includes visit and travel costs.
Valid Inputs: Origin and destination cities exist in the dataset.
Non-Negative Values: Costs, rewards, and available points are non-negative.

#Workflow
Parse inputs: cities, connections, origin, destination, and available points.
Build a graph with cities as nodes and connections as edges.
Use DFS with memoization to explore paths and track rewards.
Output the maximum reward and corresponding path or only the origin city's reward if no path exists.

#Example
Input:
Cities:
  CITY_A: Cost = 300, Reward = 1000
  CITY_B: Cost = 500, Reward = 900
Connections:
  CITY_A <-> CITY_B: Travel Cost = 250
Origin: CITY_A
Destination: CITY_B
Available Points: 1000


Output:
Max Reward: 1900
Best Path: CITY_A -> CITY_B

#How to Run
Update cities, connections, and inputs in the code.
Compile and run:
g++ -o solution solution.cpp
./solution
