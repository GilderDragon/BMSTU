#ifndef BMSTU_GRAPH_H
#define BMSTU_GRAPH_H
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <map>
#include <algorithm>
#include <functional>
#include <limits>
#include <stdexcept>
#include <utility>
#include <sstream>
#include <iomanip>

class Graph {
private:
    bool directed; // true - ориентированный, false - неориентированный
    bool weighted; // true - взвешенный, false - невзвешенный

    // Матрица смежности
    std::vector<std::vector<int>> adjacencyMatrix;

    // Списки смежности (для взвешенного графа храним пары: вершина-вес)
    std::vector<std::list<std::pair<int, int>>> adjacencyList;

    // Имена вершин (если нужны)
    std::map<int, std::string> vertexNames;

    int vertexCount;
    int edgeCount;

public:
    // Конструкторы
    Graph(bool isDirected = false, bool isWeighted = false)
        : directed(isDirected), weighted(isWeighted), vertexCount(0), edgeCount(0) {}

    Graph(int numVertices, bool isDirected = false, bool isWeighted = false)
        : directed(isDirected), weighted(isWeighted), vertexCount(numVertices), edgeCount(0) {

        adjacencyMatrix.resize(numVertices, std::vector<int>(numVertices, 0));
        adjacencyList.resize(numVertices);
    }

    // Добавление вершины
    int addVertex() {
        int newVertexId = vertexCount++;

        // Увеличиваем матрицу смежности
        for (auto& row : adjacencyMatrix) {
            row.push_back(0);
        }
        adjacencyMatrix.push_back(std::vector<int>(vertexCount, 0));

        // Увеличиваем список смежности
        adjacencyList.push_back(std::list<std::pair<int, int>>());

        return newVertexId;
    }

    int addVertex(const std::string& name) {
        int id = addVertex();
        vertexNames[id] = name;
        return id;
    }

    // Добавление ребра
    void addEdge(int from, int to) {
        if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
            throw std::out_of_range("Неверный индекс вершины");
        }

        adjacencyMatrix[from][to] = 1;
        adjacencyList[from].push_back({to, 1});
        edgeCount++;

        if (!directed) {
            adjacencyMatrix[to][from] = 1;
            adjacencyList[to].push_back({from, 1});
        }
    }

    void addEdge(int from, int to, int weight) {
        if (!weighted) {
            throw std::runtime_error("Граф не взвешенный");
        }

        if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
            throw std::out_of_range("Неверный индекс вершины");
        }

        adjacencyMatrix[from][to] = weight;
        adjacencyList[from].push_back({to, weight});
        edgeCount++;

        if (!directed) {
            adjacencyMatrix[to][from] = weight;
            adjacencyList[to].push_back({from, weight});
        }
    }

    void addEdge(const std::string& from, const std::string& to, int weight = 1) {
        int fromId = findVertexIdByName(from);
        int toId = findVertexIdByName(to);

        if (fromId == -1 || toId == -1) {
            throw std::runtime_error("Вершина не найдена");
        }

        if (weighted) {
            addEdge(fromId, toId, weight);
        } else {
            addEdge(fromId, toId);
        }
    }

    // Удаление ребра
    void removeEdge(int from, int to) {
        if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
            throw std::out_of_range("Неверный индекс вершины");
        }

        adjacencyMatrix[from][to] = 0;

        // Удаляем из списка смежности
        adjacencyList[from].remove_if([to](const std::pair<int, int>& p) {
            return p.first == to;
        });

        edgeCount--;

        if (!directed) {
            adjacencyMatrix[to][from] = 0;
            adjacencyList[to].remove_if([from](const std::pair<int, int>& p) {
                return p.first == from;
            });
        }
    }

    // Проверка существования ребра
    bool hasEdge(int from, int to) const {
        if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
            return false;
        }
        return adjacencyMatrix[from][to] != 0;
    }

    // Получение веса ребра
    int getEdgeWeight(int from, int to) const {
        if (!weighted) {
            throw std::runtime_error("Граф не взвешенный");
        }

        if (from < 0 || from >= vertexCount || to < 0 || to >= vertexCount) {
            throw std::out_of_range("Неверный индекс вершины");
        }

        return adjacencyMatrix[from][to];
    }

    // Получение соседей вершины
    std::vector<int> getNeighbors(int vertex) const {
        if (vertex < 0 || vertex >= vertexCount) {
            throw std::out_of_range("Неверный индекс вершины");
        }

        std::vector<int> neighbors;
        for (const auto& neighbor : adjacencyList[vertex]) {
            neighbors.push_back(neighbor.first);
        }
        return neighbors;
    }

    // Получение соседей с весами
    std::vector<std::pair<int, int>> getNeighborsWithWeights(int vertex) const {
        if (vertex < 0 || vertex >= vertexCount) {
            throw std::out_of_range("Неверный индекс вершины");
        }

        return std::vector<std::pair<int, int>>(
            adjacencyList[vertex].begin(),
            adjacencyList[vertex].end()
        );
    }

    // Степень вершины
    int getDegree(int vertex) const {
        if (vertex < 0 || vertex >= vertexCount) {
            throw std::out_of_range("Неверный индекс вершины");
        }

        return adjacencyList[vertex].size();
    }

    // Поиск ID вершины по имени
    int findVertexIdByName(const std::string& name) const {
        for (const auto& pair : vertexNames) {
            if (pair.second == name) {
                return pair.first;
            }
        }
        return -1;
    }

    // Получение имени вершины
    std::string getVertexName(int vertex) const {
        auto it = vertexNames.find(vertex);
        if (it != vertexNames.end()) {
            return it->second;
        }
        return "V" + std::to_string(vertex);
    }

    // Обход в глубину (DFS) - рекурсивный
    void dfsRecursive(int start, std::function<void(int)> visit) const {
        if (start < 0 || start >= vertexCount) {
            throw std::out_of_range("Неверный индекс вершины");
        }

        std::vector<bool> visited(vertexCount, false);
        dfsHelper(start, visited, visit);
    }

    // Обход в глубину (DFS) - итеративный
    std::vector<int> dfsIterative(int start) const {
        if (start < 0 || start >= vertexCount) {
            throw std::out_of_range("Неверный индекс вершины");
        }

        std::vector<int> result;
        std::vector<bool> visited(vertexCount, false);
        std::stack<int> stack;

        stack.push(start);

        while (!stack.empty()) {
            int current = stack.top();
            stack.pop();

            if (!visited[current]) {
                visited[current] = true;
                result.push_back(current);

                // Добавляем соседей в обратном порядке для соответствия рекурсивному DFS
                auto neighbors = getNeighbors(current);
                std::reverse(neighbors.begin(), neighbors.end());

                for (int neighbor : neighbors) {
                    if (!visited[neighbor]) {
                        stack.push(neighbor);
                    }
                }
            }
        }

        return result;
    }

    // Обход в ширину (BFS)
    std::vector<int> bfs(int start) const {
        if (start < 0 || start >= vertexCount) {
            throw std::out_of_range("Неверный индекс вершины");
        }

        std::vector<int> result;
        std::vector<bool> visited(vertexCount, false);
        std::queue<int> queue;

        visited[start] = true;
        queue.push(start);

        while (!queue.empty()) {
            int current = queue.front();
            queue.pop();
            result.push_back(current);

            for (int neighbor : getNeighbors(current)) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    queue.push(neighbor);
                }
            }
        }

        return result;
    }

    // Проверка на связность (для неориентированных графов)
    bool isConnected() const {
        if (directed) {
            throw std::runtime_error("Метод только для неориентированных графов");
        }

        if (vertexCount == 0) return true;

        auto bfsResult = bfs(0);
        return bfsResult.size() == vertexCount;
    }

    // Алгоритм Дейкстры (кратчайший путь)
    std::pair<std::vector<int>, std::vector<int>> dijkstra(int start) const {
        if (!weighted) {
            throw std::runtime_error("Граф не взвешенный");
        }

        if (start < 0 || start >= vertexCount) {
            throw std::out_of_range("Неверный индекс вершины");
        }

        const int INF = std::numeric_limits<int>::max();
        std::vector<int> distance(vertexCount, INF);
        std::vector<int> previous(vertexCount, -1);
        std::vector<bool> visited(vertexCount, false);

        distance[start] = 0;

        for (int i = 0; i < vertexCount; i++) {
            // Находим непосещенную вершину с минимальным расстоянием
            int minDistance = INF;
            int minVertex = -1;

            for (int v = 0; v < vertexCount; v++) {
                if (!visited[v] && distance[v] < minDistance) {
                    minDistance = distance[v];
                    minVertex = v;
                }
            }

            if (minVertex == -1) break;

            visited[minVertex] = true;

            // Обновляем расстояния до соседей
            for (const auto& neighbor : getNeighborsWithWeights(minVertex)) {
                int to = neighbor.first;
                int weight = neighbor.second;

                if (!visited[to] && distance[minVertex] != INF) {
                    int newDist = distance[minVertex] + weight;
                    if (newDist < distance[to]) {
                        distance[to] = newDist;
                        previous[to] = minVertex;
                    }
                }
            }
        }

        return {distance, previous};
    }

    // Восстановление пути по результатам Дейкстры
    std::vector<int> getPath(int start, int end) const {
        if (!weighted) {
            throw std::runtime_error("Граф не взвешенный");
        }

        auto [distance, previous] = dijkstra(start);

        if (distance[end] == std::numeric_limits<int>::max()) {
            return {}; // Путь не существует
        }

        std::vector<int> path;
        for (int at = end; at != -1; at = previous[at]) {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());

        return path;
    }

    // Минимальное остовное дерево (алгоритм Прима)
    std::vector<std::tuple<int, int, int>> primMST() const {
        if (directed) {
            throw std::runtime_error("Метод только для неориентированных графов");
        }

        if (!weighted) {
            throw std::runtime_error("Граф не взвешенный");
        }

        const int INF = std::numeric_limits<int>::max();
        std::vector<int> minEdge(vertexCount, INF);
        std::vector<int> parent(vertexCount, -1);
        std::vector<bool> inMST(vertexCount, false);

        minEdge[0] = 0;

        for (int i = 0; i < vertexCount; i++) {
            int minVertex = -1;
            for (int v = 0; v < vertexCount; v++) {
                if (!inMST[v] && (minVertex == -1 || minEdge[v] < minEdge[minVertex])) {
                    minVertex = v;
                }
            }

            if (minVertex == -1) break;
            inMST[minVertex] = true;

            for (const auto& neighbor : getNeighborsWithWeights(minVertex)) {
                int to = neighbor.first;
                int weight = neighbor.second;

                if (!inMST[to] && weight < minEdge[to]) {
                    minEdge[to] = weight;
                    parent[to] = minVertex;
                }
            }
        }

        std::vector<std::tuple<int, int, int>> mst;
        for (int i = 1; i < vertexCount; i++) {
            if (parent[i] != -1) {
                mst.push_back({parent[i], i, minEdge[i]});
            }
        }

        return mst;
    }

    // Вывод матрицы смежности
    void printAdjacencyMatrix() const {
        std::cout << "Матрица смежности:" << std::endl;
        std::cout << "   ";
        for (int i = 0; i < vertexCount; i++) {
            std::cout << std::setw(3) << getVertexName(i);
        }
        std::cout << std::endl;

        for (int i = 0; i < vertexCount; i++) {
            std::cout << std::setw(3) << getVertexName(i);
            for (int j = 0; j < vertexCount; j++) {
                std::cout << std::setw(3) << adjacencyMatrix[i][j];
            }
            std::cout << std::endl;
        }
    }

    // Вывод списков смежности
    void printAdjacencyList() const {
        std::cout << "Списки смежности:" << std::endl;
        for (int i = 0; i < vertexCount; i++) {
            std::cout << getVertexName(i) << ": ";
            for (const auto& neighbor : adjacencyList[i]) {
                std::cout << getVertexName(neighbor.first);
                if (weighted) {
                    std::cout << "(" << neighbor.second << ")";
                }
                std::cout << " ";
            }
            std::cout << std::endl;
        }
    }

    // Вывод информации о графе
    void printGraphInfo() const {
        std::cout << "=== ИНФОРМАЦИЯ О ГРАФЕ ===" << std::endl;
        std::cout << "Тип: " << (directed ? "Ориентированный" : "Неориентированный") << std::endl;
        std::cout << "Взвешенный: " << (weighted ? "Да" : "Нет") << std::endl;
        std::cout << "Вершин: " << vertexCount << std::endl;
        std::cout << "Ребер: " << edgeCount << std::endl;

        if (!directed) {
            std::cout << "Связный: " << (isConnected() ? "Да" : "Нет") << std::endl;
        }
    }

    // Получение основных характеристик
    int getVertexCount() const { return vertexCount; }
    int getEdgeCount() const { return edgeCount; }
    bool isDirected() const { return directed; }
    bool isWeighted() const { return weighted; }

private:
    void dfsHelper(int vertex, std::vector<bool>& visited, std::function<void(int)> visit) const {
        visited[vertex] = true;
        visit(vertex);

        for (int neighbor : getNeighbors(vertex)) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor, visited, visit);
            }
        }
    }
};


#endif //BMSTU_GRAPH_H