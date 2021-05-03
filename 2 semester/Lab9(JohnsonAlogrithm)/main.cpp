#include <iostream>
#include "ListGraph.h"

void dijkstra_test(){
    auto* graph = new ListGraph<int, int>(true, true);
    graph->add_vertex(0);
    graph->add_vertex(1);
    graph->add_vertex(2);
    graph->add_vertex(3);
    graph->add_vertex(4);
    graph->add_vertex(5);

    graph->add_edge(0, 2, 0, 1);
    graph->add_edge(1, 2, 0, 2);
    graph->add_edge(1, 3, 0, 20);
    graph->add_edge(1, 4, 0, 4);
    graph->add_edge(0, 3, 0, 1);
    graph->add_edge(2, 3, 0, 9);
    graph->add_edge(1, 5, 0, 3);
    graph->add_edge(3, 4, 0, 4);

    graph->print();
    std::vector<std::vector<int>> res = graph->dijkstraAllGraph();

    std::cout << "#\t";
    for(int i = 0; i < res.size(); i++){
        std::cout << i << "\t";
    }

    for(int i = 0; i < res.size(); i++){
        std::cout << "\n" << i << "\t";
        for(int j = 0; j < res[i].size(); j++){
            std::cout << res[i][j] << "\t";
        }
    }

}

void johnsonTest() {
    auto *graph = new ListGraph<int, int>(true, true);
    graph->add_vertex(4);
    graph->add_vertex(1);
    graph->add_vertex(2);
    graph->add_vertex(3);


    graph->add_edge(0, 1, 0, -2);
    graph->add_edge(1, 2, 0, 8);
    graph->add_edge(0, 2, 0, 7);
    graph->add_edge(2, 1, 0, 3);
    graph->add_edge(0, 3, 0, 5);
    graph->add_edge(3, 0, 0, -1);
    graph->add_edge(1, 3, 0, 6);
    graph->add_edge(2, 3, 0, -4);



    graph->print();
    std::vector<std::vector<int>> res = graph->johnsonDistances();

    std::cout << "#\t";
    for (int i = 0; i < res.size(); i++) {
        std::cout << i << "\t";
    }

    for (int i = 0; i < res.size(); i++) {
        std::cout << "\n" << i << "\t";
        for (int j = 0; j < res[i].size(); j++) {
            std::cout << res[i][j] << "\t";
        }
    }
}

int main() {
//    dijkstra_test();
    johnsonTest();
}


