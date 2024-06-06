
#include <iostream>
#include "utils.cpp"
#include "Person.h"
#include "Graph.h"

int main() {
    Graph social_network = readData("social_network.csv");
    while (true) {
        int x;
        cout<<"1.Display the social network,"<< endl;
        cout<<"2.Suggest friends for users based on common friends, similar occupation, or similar age,"<<endl;
        cout<<"3.Calculate degree centrality for each user,"<<endl;
        cout<<"4.Calculate clustering coefficient for each user,"<<endl;
        cout<<"5.Detect communities using the Girvan-Newman algorithm,"<<endl;
        cout<<"6.Exit the program."<<endl;
        cout << "Choose from the menu: ";
        cin>> x;
        cout << endl;

        if (x == 1) {
            cout << "Social Network: " << endl;
            for (int i = 1; i < social_network.getSize()+1; i++) {
                cout << social_network.getPerson(i)->person_Name()<< "(" << i << ") (" << social_network.getPerson(i)->person_Gender() <<") (" <<social_network.getPerson(i)->Person_age()<< ") (" << social_network.getPerson(i)->person_Occupation() << ")->Friends: ";
                for (int j = 0; j < social_network.getPerson(i)->person_Friends().size(); j++) {
                    cout << social_network.getPerson(i)->person_Friends()[j] << " ";
                }
                cout << endl;

            }
        }
        else if(x == 2) {
            int number;
            int mode;
            cout << "Enter your id to get suggestion: ";
            cin >> number;
            cout << "1.ByOccupation" << endl;
            cout << "2.ByAge" << endl;
            cout << "3.ByCommonFriends" << endl;
            cout << "4.Exit" << endl;
            cout << "Choose from the menu: ";
            cin>> mode;
            social_network.suggestFriends(number,mode);
        }
        else if(x == 3) {
            social_network.degreeCentrality();

        }
        else if(x == 4) {
            cout << "Enter the id to see clustering coefficient: " << endl;
            for(int i = 1; i < social_network.getSize()+1; i++) {
                social_network.clusteringCoefficient(i);
            }
        }
        else if(x == 5) {
            int iterations;
            cout << "Enter the number of iterations: ";
            cin >> iterations;
            vector<vector<int>> communities = social_network.girvanNewman(iterations);
            cout << "Communities: " << endl;
            for (int i = 0; i < communities.size(); i++) {
                cout << "Community " << i + 1 << ": ";
                for (int j = 0; j < communities[i].size(); j++) {
                    cout << communities[i][j] << " ";
                }
                cout << endl;
            }
        }
        else if(x == 6) {
            break;
        }
        else {
            cout << "Invalid input!" << endl;
        }

    }


}