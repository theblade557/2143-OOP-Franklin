

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
    // string print() {
    //   return "[color=" + att["color"] + ",arrow_type=" + att["arrow_type"] +
    //   "]";
    // }
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
            //cout << x.first << "=" << x.second << endl;
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
        os << "];";

        return os;
    }

    friend fstream &operator<<(fstream &fout, Attribute &e)
    {

        fout << "[";
        int i = 0;
        for (auto const &x : e.att)
        {
            fout << x.first << "="
                 << "\"" << x.second << "\"";
            if (i < e.att.size() - 1)
            {

                fout << ", ";
            }
            i++;
        }

        fout << "]";
        fout << endl;
        fout << "}";

        return fout;
    }

};

class Edge : public Attribute
{
    int eid;
    int start;
    int end;

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
    Edge(int start, int end)
    {
        this->start = start;
        this->end = end;
    }

    friend ostream &operator<<(ostream &os, Edge &e)
    {
        os << e.start << "->" << e.end << " ";
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
        os << "];";

        return os;
    }

};

class Node : public Attribute
{
    int nid;

public:
    Node()
    {
        att["color"] = "black";  // default color
        att["shape"] = "record"; // default arrow shape
    }

    Node(map<string, string> atts)
    {
        for (auto const &x : atts)
        {
            att[x.first] = x.second;
        }
    }
};

struct Shape
{
    string shape;
    Shape(string name) { shape = name; }
};

class GraphViz
{
    int edgeId;
    int nodeId;
    vector<Edge> Edges;
    vector<Node> Nodes;
    string graphName;
    string graphShape;

    //string makeEid(int v, int w) { return to_string(v) + "-" + to_string(w); }

public:
    GraphViz()
    {
        edgeId = 0;
        nodeId = 0;
        graphName = "foo";
    }

    GraphViz(string graph_name, string graph_shape)
    {
        edgeId = 0;
        nodeId = 0;
        graphName = graph_name;
        graphShape = graph_shape;
    }

    int addNode()
    {
        Nodes.push_back(Node());
        return Nodes.size() - 1;
    }

    int addNode(map<string, string> atts)
    {
        Nodes.push_back(Node(atts));

        return Nodes.size() - 1;
    }

    void updateNode(int id, string key, string value)
    {
        Nodes[id].addAttribute(key, value);
    }

    void addEdge(int start, int end)
    {
        // make and edge constructor that receives two ints so you
        // can print them out
        Edges.push_back(Edge(start, end));
    }

    void addEdge(int start, int end, map<string, string> att)
    {

        Edges.push_back(Edge(start, end));
        Edges[Edges.size() - 1].addAttributes(att);
    }

    // output your graphviz stuff
    void printGraph(string graphName = "")
    {
        if (graphName.size() == 0)
            graphName = this->graphName;

        cout << "digraph" << graphName << "{";
        // loop over nodes and print them
        for (int i = 0; i < Nodes.size(); i++)
        {
            cout << i << " " << Nodes[i] << endl;
        }
        // loop over edges and print them
        cout << "}\n";
    }

    friend ostream &operator<<(ostream &banana, GraphViz &g)
    {
        for (int i = 0; i < g.Nodes.size(); i++)
        {
            banana << i << " " << g.Nodes[i] << endl;
        }
        for (int i = 0; i < g.Edges.size(); i++)
        {
            banana << g.Edges[i] << endl;
        }
        return banana;
    }
};

int main()
{
    ofstream fout;
    fout.open("test.out");
    printHeading(fout);
    // create graphviz instances with specific shapes
    GraphViz G("LinkedList", "LL");
    GraphViz D("DoublyLinkedList", "DLL");
    GraphViz B("BinarySearchTree", "BST");

    // used as an example to load attributes for a node
    map<string, string> Box;
    map<string, string> Arrow;
    // example attribute that gets a map of attributes and
    // adds them to "A"
    Attribute A;
    Box["shape"] = "box";
    Box["color"] = "blue";
    Box["opacity"] = "0.8";
    A.addAttributes(Box);


    Arrow["color"] = "black";
    Arrow["arrow_type"] = "vee";
    A.addAttributes(Arrow);

    // Creating nodes in graphviz and sending in default
    // colors / shapes, etc.
    int nodeId = G.addNode(Box);
    nodeId = G.addNode(Box);
    G.updateNode(nodeId, "shape", "circle");
    G.updateNode(nodeId, "color", "red");
    nodeId = G.addNode(Box);
    nodeId = G.addNode(Box);
    nodeId = G.addNode(Box);

    G.addEdge(0, 1, Arrow);
    G.addEdge(1, 2, Arrow);
    G.addEdge(2, 3, Arrow);
    G.addEdge(3, 4, Arrow);

    //printing Linked List
    cout << "digraph LL {" << endl;
    fout << "digraph LL {" << endl;
    cout << G;
    fout << G;
    cout << "}" << endl << endl;
    fout << "}" << endl << endl;

    // making the doubly linked list
    // and sending in default colors and shapes
    nodeId = D.addNode(Box);
    nodeId = D.addNode(Box);
    nodeId = D.addNode(Box);
    nodeId = D.addNode(Box);
    nodeId = D.addNode(Box);

    D.addEdge(0, 1, Arrow);
    D.addEdge(1, 0, Arrow);
    D.addEdge(1, 2, Arrow);
    D.addEdge(2, 1, Arrow);
    D.addEdge(2, 3, Arrow);
    D.addEdge(3, 2, Arrow);
    D.addEdge(3, 4, Arrow);
    D.addEdge(4, 3, Arrow);

    //printing Doubly Linked List
    cout << "digraph DLL {" << endl;
    fout << "digraph DLL {" << endl;
    cout << D;
    fout << D;
    cout << "}" << endl << endl;
    fout << "}" << endl << endl;

    nodeId = B.addNode(Box);
    nodeId = B.addNode(Box);
    nodeId = B.addNode(Box);
    nodeId = B.addNode(Box);
    nodeId = B.addNode(Box);
    nodeId = B.addNode(Box);
    nodeId = B.addNode(Box);

    B.addEdge(0, 1, Arrow);
    B.addEdge(0, 2, Arrow);
    B.addEdge(1, 3, Arrow);
    B.addEdge(1, 4, Arrow);
    B.addEdge(2, 5, Arrow);
    B.addEdge(2, 6, Arrow);

    //printing Binary Search Tree
    cout << "digraph BST {" << endl;
    fout << "digraph BST {" << endl;
    cout << B;
    fout << B;
    cout << "}" << endl << endl;
    fout << "}" << endl << endl;
}

void printHeading(ofstream &fout) {
  fout << "Collin Franklin" << endl;
  fout << "March 9th, 2023" << endl;
  fout << "Spring 2143" << endl;
  fout << endl;
}