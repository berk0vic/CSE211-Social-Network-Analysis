#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include "Person.h"


class Graph {
public:
    Graph();
    void addPerson(int id, const Person &person);
    const Person* getPerson(int id) const;

    void suggestFriends(int person_id, int mode) const;

    void suggestFriendsByCommonFriends(const Person *person) const;
    void suggestFriendsByOccupation(const Person *person) const;
    void suggestFriendsByAge(const Person *person) const;

    int getSize() const;
    friend ostream& operator<<(ostream& os, const Graph& g);
    bool areNeighbors(int u, int v) const;

    void degreeCentrality() const;
    void clusteringCoefficient(int id) const;

    vector<pair<int, Person> > getGraph() const;


    vector<vector<int> > findCommunitiesDFS() const;
    vector<vector<int> >  girvanNewman(int iterations) const;
    double edgeWeight(const Graph &graph, int u, int v) const ;



    vector<vector<int> > findpathsBFS(const Graph &graph, int start, int end) const;
    void removeFriendship(int id1, int id2);

private:
    std::vector<std::pair<int,Person> > graph;
    int size;


};


#endif // GRAPH_H