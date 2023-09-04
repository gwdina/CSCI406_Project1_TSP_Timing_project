#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <utility>
#include <iomanip>



using namespace std;


// idea for the use of struct Coordinate came from https://www.geeksforgeeks.org/k-nearest-neighbours/
struct Coordinate{
    int nodeID;
    double x;
    double y;
    double distanceToNode;
};

int totalNodes;

vector <Coordinate> points;
set <int> notVisted; // helps locate what points to go to

// opens the text file containing the number of nodes and coordinates and stores them 
void inputFile(string file_name){
    ifstream file;
    file.open(file_name);

    file >> totalNodes; // first line of the file is the # of nodes
    
    int x;
    int y;

    int i = 0;    
    // !file.eof()    cin >> x >> y
    while (file >> x >> y) { 
        //cout << x << " " << y << endl;

        Coordinate point;

        point.x = x;
        point.y = y;
        point.nodeID = i;

        notVisted.insert(i);

        points.push_back(point);

        i++;
        }
        
        /*for(int j: notVisted){
        cout << j << " ";
    }
    cout << '\n';*/
       // cout << totalNodes << '\n';
       // cout << points.size() << '\n';

}


// starts at a node and will move to the nearest node, goes to each node stopping once all nodes have been visted and returns cost
double nearestNeighbor(Coordinate initialPoint, double totalCost){
    
    notVisted.erase(initialPoint.nodeID); // removes current node so that we don't go back to it

    // once we reach the last node will go back to the starting node
    if (notVisted.size() == 0){
        double finalPoint = sqrt((points[0].x - initialPoint.x) * (points[0].x - initialPoint.x) +
        (points[0].y - initialPoint.y) * (points[0].y - initialPoint.y));

        return (finalPoint + totalCost);
    }
    

    // calculates distance to each node from current node 
    for(int j: notVisted){
        points[j].distanceToNode = sqrt((points[j].x - initialPoint.x) * (points[j].x - initialPoint.x) +
        (points[j].y - initialPoint.y) * (points[j].y - initialPoint.y));

        //cout << points[j].distanceToNode << '\n';
    }

    double path = points[*notVisted.begin()].distanceToNode; // initial distance for testing 

    int nextPoint = points[*notVisted.begin()].nodeID; // initial location for testing

    // compares each distance to find the shortest one
    for(int k: notVisted){
        if (points[k].distanceToNode < path){
            path = points[k].distanceToNode;
            nextPoint = k;
        }
        //cout << nextPoint << '\n';
    } // if distances are the same, first appearance of that distance will be used
    

    return nearestNeighbor(points[nextPoint], totalCost + path);
    //return path;
}


int main(int argc, char* argv[]) {


    inputFile(argv[1]);
    //inputFile("TSP.txt");

    cout << fixed << setprecision(3);

    cout <<  nearestNeighbor(points[0], 0) << '\n';
    
}