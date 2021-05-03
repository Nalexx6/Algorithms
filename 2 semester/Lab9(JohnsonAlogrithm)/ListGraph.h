//
// Created by Win10Pro on 5/1/2021.
//

#ifndef LAB9_JOHNSONALOGRITHM__LISTGRAPH_H
#define LAB9_JOHNSONALOGRITHM__LISTGRAPH_H

#include <vector>
#include <queue>
#include "FibonacciHeap.h"
#include "DijkstraNode.h"


template <typename V, typename E>
class ListGraph {

    class Edge {
    public:
        int vertex{};
        E edge;
        int weight;

        Edge(const int &vertex, const E &edge) {

            this->vertex = vertex;
            this->edge = edge;

        }

        Edge(const int &vertex, const E &edge, const int weight) {

            this->vertex = vertex;
            this->edge = edge;
            this->weight = weight;

        }
    };

    //variables
    std::vector<V> vertices; //list of our vertices
    std::vector<std::vector<Edge>> adj; //adjacency list
    int edges;
    bool directed;
    bool weighted;

    //private algorithms for corresponding methods
    void dfs(const int &v, bool *visited) {

        if (visited[v])
            return;
        visited[v] = true;

        for (auto &i: adj[v]) {

            dfs(i.vertex, visited);

        }

    }

    void bfs(int &v, bool *visited) {

        std::queue<int> queue;
        visited[v] = true;
        queue.push(v);

        while (!queue.empty()) {

            v = queue.front();
            queue.pop();

            for (auto &i: adj[v]) {
                if (!visited[i.vertex]) {
                    visited[i.vertex] = true;
                    queue.push(i.vertex);
                }
            }

        }

    }

    void find_distance(const int &from, std::vector<int> *distances, bool *visited, std::vector<int>& costs, int &sum_visited) {

        int min = from;
        auto* heap = new FibonacciHeap<DijkstraNode>();

        DijkstraNode* temp;
        for(int i = 0; i < vertices.size(); i++){
            if(!visited[i]){
                temp = new DijkstraNode(i, costs[i]);
                heap->insert(*temp);
            }
        }


        DijkstraNode* decreased;
        while (heap->min() != nullptr) {

//            heap->print();

            min = heap->extractMin().index;
//            std::cout<<min<<"\n";
            visited[min] = true;
            sum_visited++;

            for (auto &i: adj[min]) {

                if ((costs[i.vertex] > costs[min] + i.weight) && !visited[i.vertex]) {

                    temp = new DijkstraNode(i.vertex, costs[i.vertex]);

                    costs[i.vertex] =
                            costs[min] + i.weight;
                    decreased = new DijkstraNode(i.vertex, costs[i.vertex]);
                    distances[i.vertex].clear();
                    for (auto j: distances[min])
                        distances[i.vertex].emplace_back(j);

                    distances[i.vertex].emplace_back(min);

                    heap->decreaseKey(*temp, *decreased);

                }

//                std::cout << "min = " << min << "(" << costs[min] << ")"
//                            << "\t i = " << i.vertex << "(" << costs[i.weight] << ")\n";

            }
        }

    }


public:

    //constructor, destructor
    ListGraph() : edges(0), directed(false), weighted(false) {};

    explicit ListGraph(const bool &directed, const bool &weighted) : edges(0), directed(directed),
                                                                     weighted(weighted) {};

    ~ListGraph() = default;

    //getters
    bool empty() { return this->vertices.empty(); }

    std::vector<V> _vertices() { return this->vertices; }

    int _edges() { return this->edges; }

    bool _directed() { return this->directed; }

    bool _weighted() { return this->weighted; }

    //public methods
    void add_vertex(const V &vertex) {

        this->vertices.emplace_back(vertex);

        std::vector<Edge> new_vertex;
        this->adj.emplace_back(new_vertex);


    }

    void delete_vertex(const int& index) {

        vertices.erase(vertices.begin() + index);
        adj.erase(adj.begin() + index);

        for (auto &j: adj) {
            for (std::size_t i = 0; i < j.size(); i++) {

                if (j[i].vertex == index) {
                    j.erase(j.begin() + i);
                    this->edges--;

                }
                if (j[i].vertex > index) {

                    j[i].vertex--;

                }
            }
        }
    }


    void add_edge(const int &from, const int &to, E edge) {
        add_edge(from, to, edge, 1);
    }

    void add_edge(const int &from, const int &to, E edge, int weight) {


        this->adj[from].emplace_back(Edge(to, edge, weight));

        if (!this->directed) {

            this->adj[to].emplace_back(Edge(from, edge, weight));

        }

        edges++;

    }

    void delete_edge(const int &from, const int &to) {

        for (std::size_t i = 0; i < adj[from].size(); i++) {

            if (adj[from][i].vertex == to)
                this->adj[from].erase(adj[from].begin() + i);


        }

        if (!this->directed) {

            for (std::size_t i = 0; i < adj[to].size(); i++) {

                if (adj[to][i].vertex == from)
                    this->adj[to].erase(adj[to].begin() + i);


            }

        }

    }

    void clear() {

        this->vertices.clear();
        this->edges = 0;
        for (auto i: this->adj) {

            i.clear();
        }
        this->adj.clear();

    }

    void print() {

        for (int i = 0; i < this->vertices.size(); i++) {
            std::cout << "Vertex " << i << " adjacent with vertices:\t";
            for (int j = 0; j < adj[i].size(); j++) {

                std::cout << adj[i][j].vertex;
                if(weighted){
                    std::cout << "(" << adj[i][j].weight << ")";
                }
                std::cout << "\t";

            }
            std::cout << "\n";

        }


    }

    int dfs() {

        bool *visited = new bool[vertices.size()];
        for (int i = 0; i < vertices.size(); i++) {
            visited[i] = false;
        }

        int components = 0;
        for (int i = 0; i < vertices.size(); i++) {
            if (!visited[i]) {
                dfs(i, visited);
                components++;
            }
        }

        delete[] visited;
        return components;

    }

    int bfs() {

        bool *visited = new bool[vertices.size()];
        for (int i = 0; i < vertices.size(); i++) {
            visited[i] = false;
        }

        int components = 0;
        for (int i = 0; i < vertices.size(); i++) {
            if (!visited[i]) {
                bfs(i, visited);
                components++;
            }
        }

        delete[] visited;
        return components;

    }

    std::vector<std::vector<int>> dijkstraAllGraph(){
        std::vector<std::vector<int>> res;
        res.resize(vertices.size(), {});
        std::cout<<res.size()<<"\n";
        for(int i = 0; i < vertices.size(); i++){
            for(int j = 0; j < vertices.size(); j++){
                res[i].template emplace_back(dijkstra_distance(i, j, true)[j]);
            }
        }

        return res;
    }

    /*
     * if costsNeeded function will return vector of all costs from "from" vertex to all others,
     * else it will return sequence of vertices, that are path between "from" and "to" vertices
    */
    std::vector<int> dijkstra_distance(const int &from, const int &to, bool costsNeeded) {

        auto *distances = new std::vector<int>[this->vertices.size()];

        bool *visited = new bool[this->vertices.size()];
        std::vector<int> costs;
        costs.resize(vertices.size(), INT32_MIN);
        int sum_visited = 0;

        for (int i = 0; i < this->vertices.size(); i++) {
            visited[i] = false;
        }

        dfs(from, visited);//defines set of vertices, which are in the same connectivity component as the vertex "from"

        for (int i = 0; i < this->vertices.size(); i++) {
            if (!visited[i]) {
                visited[i] = true;
                sum_visited++;

            } else {
                visited[i] = false;
                costs[i] = INT32_MAX;

            }
        }

        costs[from] = 0;
        if (costs[to] == -1 || from == to) {
            if (costsNeeded) {
                return costs;
            } else
                return distances[to];
        }

        find_distance(from, distances, visited, costs, sum_visited);

        delete[] visited;
//        for(int i = 0 ; i < costs.size(); i++){
//            std::cout << costs[i] << "\t";
//        }
//        std::cout << "\n";

        if(costsNeeded){
            return costs;
        } else
            return distances[to];

    }

    std::vector<std::vector<int>> johnsonDistances(){
        expandGraph();
//        print();
        std::vector<int> balances = bellmanFord(vertices.size() -1);
        narrowGraph();

        for(int i = 0; i < adj.size(); i++){
            for(int j = 0; j < adj[i].size(); j++){
                adj[i][j].weight = adj[i][j].weight + balances[i] - balances[adj[i][j].vertex];
            }
        }

        std::cout<<"balances";
        for(auto i: balances){
            std::cout << i << "\t";
        }
        std::cout<<"\n";
        print();

        std::vector<std::vector<int>> result = dijkstraAllGraph();

        for(int i = 0; i < adj.size(); i++){
            for(int j = 0; j < adj[i].size(); j++){
                adj[i][j].weight = adj[i][j].weight - balances[i] + balances[adj[i][j].vertex];
            }
        }

        return result;
    }

    void expandGraph(){
        add_vertex(V());
        for(int i = 0; i < vertices.size() - 1; i++){
            add_edge(vertices.size() - 1, i, E(), 0);
        }
    }

    void narrowGraph(){
        delete_vertex(vertices.size() - 1);
    }

    std::vector<int> bellmanFord(const int from){

        std::vector<int> result;
        result.resize(vertices.size(), INT16_MAX);
        result[from] = 0;
        for(int k = 0; k < vertices.size() - 1; k++) {
            for (int i = 0; i < adj.size(); i++) {
                for (int j = 0; j < adj[i].size(); j++) {
                    if (adj[i][j].weight + result[i] < result[adj[i][j].vertex]) {
//                        std::cout << i << "\t" << adj[i][j].vertex << std::endl;
                        result[adj[i][j].vertex] = adj[i][j].weight + result[i];
                    }
                }
            }
        }

        return result;
    }


};

#endif //LAB9_JOHNSONALOGRITHM__LISTGRAPH_H
