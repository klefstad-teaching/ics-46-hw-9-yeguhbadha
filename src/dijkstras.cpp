#include "dijkstras.h"


pair<int, int> extractVertexWithMinimumWeight(priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>& minHeap) {
    if (minHeap.empty()) {
        return {-1, numeric_limits<int>::max()};
    }

    pair<int, int> minPair = minHeap.top();
    minHeap.pop();
    return minPair;
}


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);

    distances[source] = 0;
    previous[source] = -1;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap;
    minHeap.push({source, 0});
    while (!minHeap.empty())
    {
        int u = extractVertexWithMinimumWeight(minHeap).first;

        if (visited[u]) { continue; }

        visited[u] = true;
        for (Edge edge : G[u])
        {
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({v, distances[v]});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination)
{
    vector<int> path;
    int current = destination;

    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total)
{
    for (int i = 0; i < total; ++i)
    {
        cout << v[i] << " ";
    }
}
