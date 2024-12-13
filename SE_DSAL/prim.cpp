#include <iostream>
#include <climits>

const int INF = INT_MAX;

int findMinkey(int key[], bool mst[], int V) {
    int min = INF, minIndex = 0;

    for (int v = 0; v < V; v++) {
        if (!mst[v] && key[v] < min) {
            min = key[v];
            minIndex = v;
        }
    }
    return minIndex;
}

void displayMST(int parent[], int graph[100][100], int V) {
    std::cout << "Edges\tWeight\n";
    for (int i = 1; i < V; i++) {
        std::cout << parent[i] << "-" << i << "\t" << graph[i][parent[i]] << std::endl;
    }
}

void PRIMsAlgo(int graph[100][100], int V) {
    int key[100];
    int parent[100];
    bool mst[100];

    for (int i = 0; i < V; i++) {
        key[i] = INF;
        mst[i] = false;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++) {
        int u = findMinkey(key, mst, V);
        mst[u] = true;

        for (int v = 0; v < V; v++) {
            if (graph[u][v] && !mst[v] && graph[u][v] < key[v]) {
                key[v] = graph[u][v];
                parent[v] = u;
            }
        }
    }

    displayMST(parent, graph, V);
}

int main() {
    int V;
    std::cout << "Enter number of Nodes: ";
    std::cin >> V;

    int graph[V][100];

    for (int i = 0; i < V; i++) {
        std::cout << "For i=" << i << ": ";
        for (int j = 0; j < V; j++) {
            std::cin >> graph[i][j];
            if (graph[i][j] == 0 && i != j) {
                graph[i][j] = INF;
            }
        }
    }

    std::cout << "Minimum Spanning Tree using Prim's Algorithm:\n";
    PRIMsAlgo(graph, V);

    return 0;
}
