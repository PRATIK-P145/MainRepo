#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

#define MAX_CITIES 20

struct Node {
    int reducedMatrix[MAX_CITIES][MAX_CITIES];
    int cost;
    int vertex;
    int level;
    int path[MAX_CITIES];
    int pathLength;
};

struct Compare {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return lhs->cost > rhs->cost;
    }
};

// Function to copy matrix from source to destination
void copyMatrix(int dest[MAX_CITIES][MAX_CITIES], int src[MAX_CITIES][MAX_CITIES], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

// Function to copy path from source to destination
void copyPath(int dest[MAX_CITIES], int& destLength, int src[MAX_CITIES], int srcLength) {
    destLength = srcLength;
    for (int i = 0; i < srcLength; i++) {
        dest[i] = src[i];
    }
}

// Function to reduce matrix and calculate cost
int reduceMatrix(int matrix[MAX_CITIES][MAX_CITIES], int n) {
    int cost = 0;
    
    // Reduce rows
    for (int i = 0; i < n; i++) {
        int minVal = INT_MAX;
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
            }
        }
        if (minVal != INT_MAX && minVal != 0) {
            cost += minVal;
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= minVal;
                }
            }
        }
    }
    
    // Reduce columns
    for (int j = 0; j < n; j++) {
        int minVal = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (matrix[i][j] < minVal) {
                minVal = matrix[i][j];
            }
        }
        if (minVal != INT_MAX && minVal != 0) {
            cost += minVal;
            for (int i = 0; i < n; i++) {
                if (matrix[i][j] != INT_MAX) {
                    matrix[i][j] -= minVal;
                }
            }
        }
    }
    
    return cost;
}

// Function to solve TSP using LC Branch and Bound
void solveTSP(int originalMatrix[MAX_CITIES][MAX_CITIES], int n) {
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    // Create root node
    Node* root = new Node();
    copyMatrix(root->reducedMatrix, originalMatrix, n);
    root->path[0] = 0;
    root->pathLength = 1;
    root->level = 0;
    root->vertex = 0;
    
    int tempMatrix[MAX_CITIES][MAX_CITIES];
    copyMatrix(tempMatrix, root->reducedMatrix, n);
    root->cost = reduceMatrix(tempMatrix, n);
    copyMatrix(root->reducedMatrix, tempMatrix, n);
    
    pq.push(root);
    
    int minCost = INT_MAX;
    int finalPath[MAX_CITIES];
    int finalPathLength = 0;
    
    while (!pq.empty()) {
        Node* minNode = pq.top();
        pq.pop();
        
        int i = minNode->vertex;
        
        // If all cities are visited
        if (minNode->level == n - 1) {
            // Add cost to return to starting city
            int returnCost = originalMatrix[i][0];
            if (returnCost != INT_MAX) {
                int totalCost = minNode->cost + returnCost;
                if (totalCost < minCost) {
                    minCost = totalCost;
                    copyPath(finalPath, finalPathLength, minNode->path, minNode->pathLength);
                    finalPath[finalPathLength++] = 0;
                }
            }
            delete minNode;
            continue;
        }
        
        // For each unvisited city
        for (int j = 0; j < n; j++) {
            if (minNode->reducedMatrix[i][j] != INT_MAX && minNode->reducedMatrix[i][j] != 0) {
                // Create child node
                Node* child = new Node();
                copyMatrix(child->reducedMatrix, minNode->reducedMatrix, n);
                
                // Set row i and column j to infinity
                for (int k = 0; k < n; k++) {
                    child->reducedMatrix[i][k] = INT_MAX;
                    child->reducedMatrix[k][j] = INT_MAX;
                }
                child->reducedMatrix[j][0] = INT_MAX; // Prevent premature cycle
                
                // Copy and extend path
                copyPath(child->path, child->pathLength, minNode->path, minNode->pathLength);
                child->path[child->pathLength++] = j;
                
                child->level = minNode->level + 1;
                child->vertex = j;
                
                // Calculate cost for child node
                int tempChildMatrix[MAX_CITIES][MAX_CITIES];
                copyMatrix(tempChildMatrix, child->reducedMatrix, n);
                int reductionCost = reduceMatrix(tempChildMatrix, n);
                child->cost = minNode->cost + minNode->reducedMatrix[i][j] + reductionCost;
                copyMatrix(child->reducedMatrix, tempChildMatrix, n);
                
                // Only add if cost is promising
                if (child->cost < minCost) {
                    pq.push(child);
                } else {
                    delete child;
                }
            }
        }
        
        delete minNode;
    }
    
    // Print results
    if (minCost != INT_MAX) {
        cout << "\nMinimum Cost: " << minCost << endl;
        cout << "Optimal Path: ";
        for (int i = 0; i < finalPathLength; i++) {
            cout << finalPath[i];
            if (i < finalPathLength - 1) cout << " -> ";
        }
        cout << endl;
    } else {
        cout << "\nNo feasible solution found!" << endl;
    }
    
    // Clean up remaining nodes
    while (!pq.empty()) {
        Node* node = pq.top();
        pq.pop();
        delete node;
    }
}

// Utility function to print matrix
void printMatrix(int matrix[MAX_CITIES][MAX_CITIES], int n) {
    cout << "\nCost Matrix:" << endl;
    cout << "    ";
    for (int j = 0; j < n; j++) {
        cout << "C" << j << "  ";
    }
    cout << endl;
    
    for (int i = 0; i < n; i++) {
        cout << "C" << i << "  ";
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                printf("%3d ", matrix[i][j]);
            }
        }
        cout << endl;
    }
}

// Function to initialize matrix with INF values
void initializeMatrix(int matrix[MAX_CITIES][MAX_CITIES], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = INT_MAX;
        }
    }
}

int main() {
    int n;
    int costMatrix[MAX_CITIES][MAX_CITIES];
    
    cout << "=== Traveling Salesman Problem using LC Branch and Bound ===" << endl;
    cout << "Enter number of cities (max " << MAX_CITIES << "): ";
    cin >> n;
    
    if (n > MAX_CITIES || n <= 0) {
        cout << "Invalid number of cities!" << endl;
        return 1;
    }
    
    initializeMatrix(costMatrix, n);
    
    cout << "\nEnter the cost matrix:" << endl;
    cout << "Enter " << INT_MAX << " for INF (no direct path)" << endl;
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                costMatrix[i][j] = INT_MAX; // No self-loop
                continue;
            }
            cout << "Cost from city " << i << " to city " << j << ": ";
            cin >> costMatrix[i][j];
        }
    }
    
    printMatrix(costMatrix, n);
    solveTSP(costMatrix, n);
    
    return 0;
}
