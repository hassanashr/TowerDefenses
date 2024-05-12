#include "cell.h"
#include "graph.h"
#include <bits/stdc++.h>
#include <cmath>
Graph::Graph() {}

void Graph::addCell(Cell *cell)
{
    AdjacencyList[cell] = vector<pair<Cell *, int>>();
}
int Graph::euclideanDistance(Cell *source, Cell *destination)
{
    // Calculate the Euclidean distance between two cells
    int dx = source->getX() - destination->getX();
    int dy = source->getY() - destination->getY();
    return sqrt(dx * dx + dy * dy);
}

int Graph::getCost(Cell *source, Cell *destination)
{
    return euclideanDistance(source, destination) * (source->getCost() + destination->getCost());
}

void Graph::connectCells(Cell *source, Cell *destination)
{
    // Connect two cells with an edge
    int cost = getCost(source, destination);
    AdjacencyList[source].push_back(make_pair(destination, cost));
    AdjacencyList[destination].push_back(make_pair(source, cost));
}

void Graph::removeCell(Cell *cell)
{
    // Remove a cell and its connections from the graph
    AdjacencyList.erase(cell);
    // Remove connections to the removed cell
    for (auto &pair : AdjacencyList) {
        auto &edges = pair.second;
        auto it = edges.begin();
        while (it != edges.end()) {
            if (it->first == cell) {
                it = edges.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void Graph::editConnection(Cell *source, Cell *destination)
{
    // Edit the connection between two cells
    int cost = getCost(source, destination);
    for (auto &edge : AdjacencyList[source]) {
        if (edge.first == destination) {
            edge.second = cost;
            break;
        }
    }
}

Cell *Graph::findCell(int x, int y)
{
    for (auto &pair : AdjacencyList) {
        if (pair.first->getX() == x && pair.first->getY() == y) {
            return pair.first;
        }
    }
    return nullptr; // Cell not found
}

vector<Cell *> Graph::AStar(Cell *source, Cell *destination)
{
    priority_queue<pair<int, Cell *>, vector<pair<int, Cell *>>, greater<pair<int, Cell *>>> openSet;
    unordered_map<Cell *, int> g_cost;
    unordered_map<Cell *, Cell *> parent;

    g_cost[source] = 0;
    int h_cost = getCost(source, destination);
    int f_cost = h_cost;
    openSet.push({f_cost, source});

    while (!openSet.empty()) {
        Cell *currentCell = openSet.top().second;
        openSet.pop();

        if (currentCell == destination) {
            vector<Cell *> path;
            while (currentCell != nullptr) {
                path.push_back(currentCell);
                currentCell = parent[currentCell];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        for (auto &neighbor : AdjacencyList[currentCell]) {
            Cell *neighborCell = neighbor.first;
            int tentative_g_cost = g_cost[currentCell] + getCost(neighborCell, currentCell);

            if (!g_cost.count(neighborCell) || tentative_g_cost < g_cost[neighborCell]) {
                g_cost[neighborCell] = tentative_g_cost;
                int h_cost_neighbor = getCost(neighborCell, destination);
                int f_cost_neighbor = tentative_g_cost + h_cost_neighbor;

                openSet.push({f_cost_neighbor, neighborCell});
                parent[neighborCell] = currentCell;
            }
        }
    }

    return vector<Cell *>();
}

void Graph::connectNeighbours(int row, int col)
{
    for (int dRow = -1; dRow <= 1; dRow++) {
        for (int dCol = -1; dCol <= 1; dCol++) {
            if (dRow == 0 && dCol == 0)
                continue;
            int newRow = row + dRow;
            int newCol = col + dCol;
            if (newRow >= 0 && newRow < 16 && newCol >= 0 && newCol < 12) {
                connectCells(findCell(row, col), findCell(newRow, newCol));
            }
        }
    }
}
