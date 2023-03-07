/**
https://replit.com/@rugbyprof/graphvizsp23#main.cpp
*/

#include <fstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

void printHeading(ofstream &fout);

class Attribute
{
protected:
    map<string, string> att; // attributes

public:
    Attribute() {}

    /**
     * Very basic print method to print out some graphviz style
     * code defining an edge.
     */
    string print()
    {
        return "[color=" + att["color"] + ",arrow_type=" + att["arrow_type"] + "]";
    }
    /**
     * Update an edge attribute. Assumes key is valid.
     */
    void addAttribute(string key, string val) { att[key] = val; }

    /**
     * Takes a map of attributes. Loops over them and saves them
     * locally.
     */
    void addAttributes(map<string, string> atts)
    {
        for (auto const &x : atts)
        {
            cout << x.first << "=" << x.second << endl;
            att[x.first] = x.second;
        }
    }
    /**
     * Use our basic print to dump this class out.
     */
    friend ostream &operator<<(ostream &os, Attribute &e)
    {
        os << "[";
        int i = 0;
        for (auto const &x : e.att)
        {
            os << x.first << "="
               << "\"" << x.second << "\"";
            if (i < e.att.size() - 1)
            {
                os << ", ";
            }
            i++;
        }
        os << "]";
        return os;
    }
};

class Edge : public Attribute
{
    int eid;

public:
    Edge()
    {
        att["color"] = "black";    // default color
        att["arrow_type"] = "vee"; // default arrow shape
    }

    Edge(string color, string arrow)
    {
        att["color"] = color;      // default color
        att["arrow_type"] = arrow; // default arrow shape
    }
};

class Node : public Attribute
{
    int nid;

public:
    Node()
    {
        att["color"] = "black"; // default color
        att["shape"] = "box";   // default arrow shape
    }
};

class GraphViz
{
    int edgeId;
    int nodeId;
    vector<Edge> Edges;
    vector<Node> Nodes;

    string makeEid(int v, int w) { return to_string(v) + "-" + to_string(w); }

public:

    //GraphViz constructor
    GraphViz()
    {
        edgeId = 0;
        nodeId = 0;
    }

    //adds node to the back
    int addNode()
    {
        Nodes.push_back(Node());
        return Nodes.size() - 1;
    }
    
    //adds an edge to the back
    void addEdge(int start, int end) { Edges.push_back(Edge()); }

    // output your graphviz stuff
    void printGraph(string graphName)
    {
        cout << "Digraph" << graphName << "{";
        // loop over nodes and print them
        // loop over edges and print them
        cout << "}\n";
    }
};

int main()
{
    // add and save nodes and edges

    ofstream fout;
    fout.open("test.out");
    printHeading(fout);

    int start;
    int end;

    Edge e;
    map<string, string> stuff;

    stuff["fillcolor"] = "red";
    stuff["nodecolor"] = "purple";
    stuff["edgestyle"] = "dashed";

    vector<Node> Nodes;

    // index = 0-3
    Nodes.push_back(Node());
    Nodes.push_back(Node());
    Nodes.push_back(Node());
    Nodes.push_back(Node());

    // adding attributes
    Nodes[1].addAttribute("fillColor", "blue");
    Nodes[2].addAttribute("fillColor", "purple");
    Nodes[3].addAttribute("fillColor", "red");

    //printing out graphviz stuff
    cout << "digraph"
         << " linkedlist"
         << "{\n";

    fout << "digraph"
         << " linkedlist"
         << "{\n";

    cout << "rankdir=LR" << endl;
    fout << "rankdir=LR" << endl;

    for (int i = 0; i < Nodes.size(); i++)
    {
        cout << "\t" << i << " " << Nodes[i] << endl;
        fout << "\t" << i << " " << Nodes[i] << endl;
    }
    cout << "}\n";
    fout << "}\n";

    //   cout<<"=================="<<endl;
    //   cout<<e<<endl;
    // cout<<"=================="<<endl;

    //   GraphViz g;

    //   start = g.addNode();
    //   g.updateNode(id,key,value);

    // g.addEdge(0, 1);
    // g.addEdge(0, 4);
    // g.addEdge(1, 2);
    // g.addEdge(1, 3);
    // g.addEdge(1, 4);
    // g.addEdge(2, 3);
    // g.addEdge(3, 4);
    // g.addEdge(9, 10);
    // g.addEdge(4, 9);

    // g.printGraph();
    return 0;
}

//prints heading
void printHeading(ofstream &fout)
{
    fout << "Collin Franklin" << endl;
    fout << "March 2nd, 2023" << endl;
    fout << "Spring 2143" << endl;
    fout << endl;
}