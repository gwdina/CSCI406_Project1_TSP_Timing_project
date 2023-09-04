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

vector<double> permutationsCost;

// goes through each possible permutation of the given nodes and finds the sequences that give the shorest cost 
void optimalPath(){
    vector<int> pathToMutate(notVisted.begin(), notVisted.end()); // next_permutation can't work with sets
      do{
            int previous;
            double sumTotal = 0;

             for(int j: pathToMutate){
                // skips if we are at the start
                if (j == pathToMutate[0]){
                    previous = j;
                    continue;
                    }

                sumTotal += sqrt((points[j].x - points[previous].x) * (points[j].x - points[previous].x) + (points[j].y - points[previous].y) * (points[j].y - points[previous].y));

                previous = j; // used for next iteration

                // goes back to starting node once every node has been visted
                if (previous == pathToMutate[pathToMutate.size()-1]){
                    sumTotal += sqrt((points[pathToMutate[0]].x - points[previous].x) * (points[pathToMutate[0]].x - points[previous].x) + (points[pathToMutate[0]].y - points[previous].y) * (points[pathToMutate[0]].y - points[previous].y));
                    }
            }
            /*for(int j: pathToMutate){
                cout << j << " ";
            }
            cout << ": " << sumTotal << endl;*/
            permutationsCost.push_back(sumTotal);
        }

       while(next_permutation(pathToMutate.begin(),pathToMutate.end()));

       cout << fixed << setprecision(3);

       double finalCost = permutationsCost[0];

        for(int k=0; k < permutationsCost.size(); k++){
            if (permutationsCost[k] < finalCost){
            finalCost = permutationsCost[k];
            }
    
    }
    cout << finalCost;
}


int main(int argc, char* argv[]) {


    inputFile(argv[1]);
    //inputFile("TSP.txt");


    optimalPath();
    
}