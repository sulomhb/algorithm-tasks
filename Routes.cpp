/*
Problem: Simulate Router Routing Table (SRRT)

A routing table contains the information necessary to forward a packet along the best path toward its destination. Each packet contains information about its origin and destination. When a packet is received, a network device examines the packet and matches it to the routing table entry providing the best match for its destination. The table then provides the device with instructions for sending the packet to the next hop on its route across the network.

999999.png

Suppose the above figure shows a network with all the routes. The network contains 6 nodes (0, 1, 2, 3, 4, 5), that shows the routers. Nodes are connected by edges. The edges have weight that shows the cost of the link.

Write C++ program for creating this type of network with undirected routes. Also create the routing table for each node that shows the route for sending the packet from source to destination. When sending the packet, calculate the shortest path based on the weight of the edges between source and destination.

Example:

Suppose the router 0 want to send a packet to router 5. The router 0 contain all the routs from itself to other routers. The router maintains the shortest path from itself to the destination.  

Destination

Next Hop

Cost

1

3

8

2

-

1

3

-

3

4

2

2

5

2

4

Assessment and Grading: 10 Marks

The program gets the information from the user.

Enter number of nodes:

6

Enter Destination Source Weight-of-link in order of (D S W):

2 0 1

3 0 3

1 3 5

………

Get only direct path from the user.

After getting the above information, create the graph, adjacency matrix, routing table. Show the graph, adjacency matrix and routing table to the user. Ask the user from where he/she wants to send the data to the destination and find the shorted route from source to the destination.
*/

#include <bits/stdc++.h>
// group 6: Andreas Stiansen, Odd-Harald Lillestø Myhren, Suleyman Selcuk, Shaheen 
Thayalan
using namespace std;
class Graph {
public:
    int amount;
    vector<vector<int>> adjacency_matrix;
    Graph(int amount) {
        this->amount = amount;
        for (int i = 0; i < amount; i++) {
            vector<int> row;
            for (int j = 0; j < amount; j++)
                row.push_back(0);
            this->adjacency_matrix.push_back(row);
        }
    }
    void add_edge(int destination, int source, int weight) {
        this->adjacency_matrix[destination][source] = weight;
        this->adjacency_matrix[source][destination] = weight;
    }
    void print_graph() {
        cout << "Graph:" << endl;
        for (int i = 0; i < this->amount; i++) {
            for (int j = 0; j < this->amount; j++) {
                if (this->adjacency_matrix[i][j] > 0) {
                    cout << i << " -> " << j << " (" << this->adjacency_matrix[i]
[j]
                         << ")" << endl;
                }
            }
        }
    }
    void print_matrix() {
        cout << "Adjacency Matrix:" << endl << "  ";
        for (int i = 0; i < this->amount; i++)
            cout << i << " ";
        cout << endl;
        for (int i = 0; i < this->amount; i++) {
            cout << i << " ";
            for (auto column: this->adjacency_matrix[i])
                cout << column << " ";
            cout << endl;
        }
    }
    void print_table(vector<int> distance, map<int, vector<int>> paths) {
        cout << "Routing table for source:" << endl;
        cout << "Destination\tNext Hop\tDistance from source" << endl;
        for (int i = 0; i < this->amount; i++)
            if (distance[i] > 0) {
                if (paths[i].empty()) {
                    cout << i << "\t" << "-" << "\t" << distance[i] << endl;
                } else {
                    cout << i << "\t" << paths[i][0] << "\t" << distance[i] << 
endl;
                }
            }
    }
    int min_distance(vector<int> distance, vector<bool> set) {
        int minimum = INT_MAX, index;
        for (int i = 0; i < this->amount; i++) {
            if (!set[i] && distance[i] <= minimum) {
                minimum = distance[i];
                index = i;
            }
        }
        return index;
    }
    vector<int> shortest_path(int source, int destination) {
        map<int, vector<int>> paths;
        vector<int> distance;
        vector<bool> set;
        for (int i = 0; i < this->amount; i++) {
            distance.push_back(INT_MAX);
            set.push_back(false);
        }
        distance[source] = 0;
        for (int count = 0; count < this->amount - 1; count++) {
            int u = min_distance(distance, set);
            set[u] = true;
            for (int v = 0; v < this->amount; v++) {
                if (!set[v] &&
                    this->adjacency_matrix[u][v] &&
                    distance[u] != INT_MAX &&
                    distance[u] + this->adjacency_matrix[u][v] < distance[v]) {
                    distance[v] = distance[u] + this->adjacency_matrix[u][v];
                    if (u != source)
                        paths[v].push_back(u);
                }
            }
        }
        print_table(distance, paths);
        return paths[destination];
    }
};
int main() {
    int amount;
    cout << "Amount: ";
    cin >> amount;
    Graph graph = Graph(amount);
    // Get graph inputs
    cout << "Enter Destination Source Weight in order of (D S W), -1 to stop"
         << endl;
    while (1) {
        int destination, source, weight;
        cin >> destination;
        if (destination < 0)
            break;
        cin >> source >> weight;
        cout << endl;
        graph.add_edge(destination, source, weight);
    }
    // Print graph
    graph.print_graph();
    graph.print_matrix();
    // Ask user where to send data, and find shortest path from source to
    // destination
    while (true) {
        cout << "Enter source and destination, -1 to exit: " << endl;
        int source, destination;
        cin >> source;
        if (source < 0)
            break;
        cin >> destination;
        if (source == destination) {
            cout << "Source and destination can't be the same" << endl;
            continue;
        }
        vector<int> nodes = graph.shortest_path(source, destination);
        cout << "Shortest path: " << source << " -> ";
        for (int i: nodes) {
            cout << i << " -> ";
        }
        cout << destination << endl;
    }
    return 0;
}