#include "Graph.h"
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <set>
#ifndef GRAPH_CPP
#define GRAPH_CPP
using namespace std;
Graph::Graph()
{
    size = 0;
}
void Graph::addPerson(int id, const Person &person){
    graph.emplace_back(make_pair(person.Person_Id(), person));
    size++;
}
const Person* Graph::getPerson(int id) const{
    for (int i = 0; i < size; i++) {
        if(graph[i].first == id) {
            return &graph[i].second;
        }
    }
    return nullptr;
}
void Graph::suggestFriendsByOccupation(const Person *person) const {
    vector<string> commonfriends_occupation;
    vector<int> commonfriends_occupation_id;
    for (int i = 0; i < size; i++) {
        if (graph[i].first != person->Person_Id()) {
            if (graph[i].second.person_Occupation() == person->person_Occupation()) {
                commonfriends_occupation.push_back(graph[i].second.person_Name());
                commonfriends_occupation_id.push_back(graph[i].second.Person_Id());
            }
        }
    }
    cout << "Suggested friends(by Occupation): " << endl;
    for (int i = 0; i < commonfriends_occupation.size(); i++) {
        cout << commonfriends_occupation[i] << "(" << commonfriends_occupation_id[i] << ")" << endl;
    }
}
void Graph::suggestFriendsByAge(const Person *person) const {//range between 2 years
    vector<string> commonfriends_age;
    vector<int> commonfriends_age_id;
    for (int i = 0; i < size; i++) {
        if (graph[i].first != person->Person_Id()) {
            if (graph[i].second.Person_age() >= person->Person_age() - 2 && graph[i].second.Person_age() <= person->Person_age() + 2) {
                commonfriends_age.push_back(graph[i].second.person_Name());
                commonfriends_age_id.push_back(graph[i].second.Person_Id());
            }
        }

    }
    cout << "Suggested friends(by Age): " << endl;
    for (int i = 0; i < commonfriends_age.size(); i++) {
        cout << commonfriends_age[i] << "(" << commonfriends_age_id[i] << ")" << endl;
    }
}
void Graph::suggestFriendsByCommonFriends(const Person *person) const {
    vector<string> commonfriends_common;
    vector<int> commonfriends_common_id;
    for (int i = 0; i < size; i++) {
        if (graph[i].first != person->Person_Id()) {
            for (int j = 0; j < graph[i].second.person_Friends().size(); j++) {
                for (int k = 0; k < person->person_Friends().size(); k++) {

                    if (graph[i].second.person_Friends()[j] == person->person_Friends()[k]) {
                        commonfriends_common.push_back(graph[i].second.person_Name());
                        commonfriends_common_id.push_back(graph[i].second.Person_Id());
                    }
                }
            }
        }
    }
    //removing the duplicates
    for(int i = 0; i < commonfriends_common.size(); i++){
        for(int j = 1; j < commonfriends_common.size(); j++){
            if(commonfriends_common[i] == commonfriends_common[j]){
                commonfriends_common.erase(commonfriends_common.begin() + j);
                commonfriends_common_id.erase(commonfriends_common_id.begin() + j);
            }
        }
    }
    //removing the friends of the person
    for (int i = 0; i < person->person_Friends().size(); i++) {
        for (int j = 0; j < commonfriends_common.size(); j++) {
            if (person->person_Friends()[i] == commonfriends_common_id[j]) {
                commonfriends_common.erase(commonfriends_common.begin() + j);
                commonfriends_common_id.erase(commonfriends_common_id.begin() + j);
            }
        }
    }

    //printing
    cout << "Suggested friends(by Common Friends): " << endl;
    for (int i = 0; i < commonfriends_common.size(); i++) {
        cout << commonfriends_common[i] << "(" << commonfriends_common_id[i] << ")" << endl;
    }
}
void Graph::suggestFriends(int person_id, int mode) const {
    const Person *person = getPerson(person_id);
    if (mode == 1) {
        suggestFriendsByOccupation(person);
    } else if (mode == 2) {
        suggestFriendsByAge(person);
    } else if (mode == 3) {
        suggestFriendsByCommonFriends(person);
    }
    else if(mode == 4){
        cout <<"Exiting from Suggestion mode"<<endl;
    }
    else {
        cout << "Invalid mode" << endl;
    }
}
int Graph::getSize() const {//returning size of the graph
    return size;
}
std::vector<std::pair<int, Person>> Graph::getGraph() const { //returning the graph
    return graph;
}
void Graph::degreeCentrality() const { //degree centrality
    vector<int> degree;
    degree.reserve(size);
    for (int i = 0; i < size; i++) {
        degree.push_back(graph[i].second.person_Friends().size());
        }
    cout << "Degree Centrality: " << endl;
    for (int i = 0; i < size; i++) {
        cout << graph[i].second.person_Name() << ": " << degree[i] << endl;
    }
}
void Graph::clusteringCoefficient(int id) const {
    const Person* person = getPerson(id);
    const vector<int>& friends = getPerson(id)->person_Friends();
    if (friends.size() < 2 || !person) {
        cout <<0.0f;
    }
    set<pair<int, int>> calculation_set;

    for (int i = 0; i < friends.size(); i++) {
        int friendId = friends[i];
        const Person* currentFriend = getPerson(friendId);
        if (!currentFriend) continue;

        const vector<int>& friends_of_friend = currentFriend->person_Friends();

        for (int i = 0; i < friends_of_friend.size(); i++) {
            int friendFriendId = friends_of_friend[i];
            if (std::find(friends.begin(), friends.end(), friendFriendId) != friends.end()) {
                calculation_set.insert({min(friendId, friendFriendId), max(friendId, friendFriendId)});
            }
        }
    }

    int friends_number = friends.size();
    int calculation_triangle = calculation_set.size();
    float x = (2.0f * calculation_triangle) / (friends_number * (friends_number - 1));
    cout << "Clustering Coefficient of " << "id "<< getPerson(id)->Person_Id() << ": " <<getPerson(id)->person_Name()<< " is: " << x <<endl;
}




vector<vector<int>> Graph::findpathsBFS(const Graph &graph, int start, int end) const {
    // BFS
    vector<vector<int>> allPaths;
    queue<vector<int>> q;
    // Start the path with the start node
    q.push(vector<int>{start});
    while (!q.empty()) {
        // Get the first path from the queue
        vector<int> path = q.front();
        q.pop();
        // Get the last node from the path
        int last = path[path.size() - 1];
        if (last == end) {
            allPaths.push_back(path);
        }
        // If we haven't reached the end node
        else {
            const Person* person = graph.getPerson(last);
            if (person != nullptr) {
                vector<int> neighbors = person->person_Friends();
                for (int i = 0; i < neighbors.size(); i++) {
                    // If the neighbor hasn't been visited
                    if (std::find(path.begin(), path.end(), neighbors[i]) == path.end()) {
                        vector<int> newPath(path);
                        newPath.push_back(neighbors[i]);
                        q.push(newPath);
                    }
                }
            }
        }
    }

    return allPaths;
}




void Graph::removeFriendship(int id1, int id2) {
    for (auto& entry : graph) {
        if (entry.first == id1) {
            // Remove id2 from id1's friends list
            auto friends = entry.second.person_Friends();
            friends.erase(std::remove(friends.begin(), friends.end(), id2), friends.end());
            entry.second.set_person_Friends(friends);
        }
        if (entry.first == id2) {
            // Remove id1 from id2's friends list
            auto friends = entry.second.person_Friends();
            friends.erase(std::remove(friends.begin(), friends.end(), id1), friends.end());
            entry.second.set_person_Friends(friends);
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Graph& g) {
    for (const auto& entry : g.graph) {
        os << "Person ID: " << entry.first << " - Name: " << entry.second.person_Name() << std::endl;
    }
    return os;
}


vector<vector<int>> Graph::girvanNewman(int iterations) const {
    Graph graph = *this;
    vector<vector<int>> communities;
    //addition of edge betweenness
    for (int i = 0; i < iterations; i++) {
        map<pair<int, int>, double> edgeBetweenness;
        for (int u = 1; u < graph.getSize()+1; u++) {
            for (int v = u + 1; v < graph.getSize()+1; v++) {
                double weight = graph.edgeWeight(graph, u, v);
                //cout << "Edge between " << u << " and " << v << " has betweenness " << weight << endl;
                edgeBetweenness[{u, v}] = weight;
            }
        }

        double maxBetweenness = 0;
        pair<int, int> selected_edges;

        // Find the edge with the highest betweenness
        for (const auto& entry : edgeBetweenness) {
            if (entry.second > maxBetweenness) {
                maxBetweenness = entry.second;
                selected_edges = entry.first;
            }
        }



        // Remove the edge with the highest betweenness
        graph.removeFriendship(selected_edges.first, selected_edges.second);
    }

    communities = graph.findCommunitiesDFS();
    return communities;
}

vector<vector<int>> Graph::findCommunitiesDFS() const {
    vector<vector<int>> communities;
    vector<bool> visited(size, false);


    for (int i = 1; i < size+1; i++) {
        // If the node hasn't been visited yet
        if (!visited[i]) {
            vector<int> community;
            stack<int> stack;
            stack.push(i);
            visited[i] = true;

            while (!stack.empty()) {
                // Getting the top element from the stack
                int current = stack.top();
                stack.pop();
                community.push_back(current);

                const Person* person = getPerson(current);
                if (person) {
                    // Getting the friends of the current person
                    for (int friendId : person->person_Friends()) {
                        int friendIndex = friendId;
                        // If the friend hasn't been visited yet
                        if (!visited[friendIndex]) {
                            stack.push(friendIndex);
                            visited[friendIndex] = true;
                        }
                    }
                }
            }
            communities.push_back(community);
        }
    }

    return communities;
}

double Graph::edgeWeight(const Graph &graph, int u, int v) const {
    if (!areNeighbors(u, v)) {
        return 0.0;
    }
    double edgeBetweenness = 0.0;
    for (int i = 1; i <= graph.getSize(); ++i) {
        for (int j = i + 1; j <= graph.getSize(); ++j) {
            // Find all shortest paths between i and j
            vector<vector<int>> paths = graph.findpathsBFS(graph, i, j);
            int totalPaths = paths.size();
            if (totalPaths > 0) {
                for (const auto &path : paths) {
                    // Check if the path contains the edge between u and v
                    for (int k = 0; k < path.size() - 1; ++k) {
                        if ((path[k] == u && path[k + 1] == v) || (path[k] == v && path[k + 1] == u)) {
                            edgeBetweenness += 1.0 / totalPaths;
                            break;
                        }
                    }
                }
            }
        }
    }

    return edgeBetweenness;
}
bool Graph::areNeighbors(int u, int v) const {
    vector<int> friends_u = getPerson(u)->person_Friends();
    vector<int> friends_v = getPerson(v)->person_Friends();
    for (int i = 0; i < friends_u.size(); i++) {
        if (friends_u[i] == v) {
            return true;
        }


    }
    return false;
}







#endif
















