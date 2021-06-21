#include "graph.h"
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
Graph::Graph(){

}
void Graph::read_gml_id(QString ss){
        string temp;
        string s;
        s = ss.toStdString();
        ifstream myfile(s);
        while (!myfile.eof())
        {
            myfile >> temp;
            if (temp == "id")
            {
                myfile >> temp;
                id.push_back(stoi(temp));
            }
        }
    }
void Graph::read_gml_edge(QString ss) {
        string temp;
        string s = ss.toStdString();
        ifstream myfile(s);
        for (int i = 0; i < id.size(); i++)
        {
            vector<int> wow;
            edge.push_back(wow);
        }
        while (!myfile.eof())
        {
            myfile >> temp;
            if (temp == "source")
            {
                myfile >> temp;
                int node1 = stoi(temp);
                myfile >> temp;
                myfile >> temp;
                int node2 = stoi(temp);
                edge[node1].push_back(node2);
            }
        }
    }
void Graph::read_gml_id_label(QString ss) {
        string temp;
        string s= ss.toStdString();
        ifstream myfile(s);
        while (!myfile.eof())
        {
            myfile >> temp;
            if (temp == "id")
            {
                myfile >> temp;
                id.push_back(stoi(temp));
            }
            if (temp == "label"){
                string labelo;
                myfile>>temp;
                while(!(temp == "value")&&!(temp=="]")){//这里咋回事。。。。
                    labelo =labelo + " "+ temp;
                    myfile>>temp;
                }
                label_name.push_back(QString::fromStdString(labelo));
            }
        }
    }
void Graph::read_value(QString ss){
    string temp;
    string s;
    s = ss.toStdString();
    ifstream myfile(s);
    while (!myfile.eof())
    {
        myfile >> temp;
        if (temp == "value")
        {
            myfile >> temp;
            this->value.push_back(QString::fromStdString(temp));
        }
    }
}
