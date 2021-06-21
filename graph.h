#ifndef GRAPH_H
#define GRAPH_H


#include<iostream>
#include<fstream>
#include<QString>
#include<vector>

using namespace std;
class Graph {
public:
    vector<int> id;
    vector<vector<int>> edge;
    vector<QString> label_name;
    vector<QString> value;
    void read_gml_id(QString s);
    void read_gml_id_label(QString s);
    void read_gml_edge(QString s);
    void read_value(QString s);
    Graph();

};

#endif // GRAPH_H
