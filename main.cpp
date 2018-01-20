#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "HierarchicalClustering.h"

using namespace std;

// Process the input file, returns algorithm type, numbers of clusterings, and the coordinates.
point* processInputFile(ifstream& i_infile, string &i_algorithm, int &i_numberOfClusters)
{
	string strOfClusters;
	string lineOfPoint;
	int numOfPoints = 0 ;
	point* coordinates = NULL;

	if (i_infile.is_open())
	{
		getline(i_infile, i_algorithm);
		getline(i_infile, strOfClusters);
		istringstream(strOfClusters) >> i_numberOfClusters;

		//initialize coors arrey
		while (getline(i_infile, lineOfPoint))
			numOfPoints++;
		coordinates = new point[numOfPoints];
		i_infile.clear();
		i_infile.seekg(0, ios::beg);
		//go ahead 2 lines forward
		getline(i_infile, lineOfPoint);
		getline(i_infile, lineOfPoint);
		int indexInArrey = 0;
		while (getline(i_infile, lineOfPoint))
		{
			string xCoor = lineOfPoint.substr(0, lineOfPoint.find(","));
			istringstream(xCoor) >> coordinates[indexInArrey].x;
			string yCoor = lineOfPoint.substr(lineOfPoint.find(",")+1, lineOfPoint.length());
			istringstream(yCoor) >> coordinates[indexInArrey].y;
			coordinates[indexInArrey].cluster = numOfPoints;
			indexInArrey++;
		}
	}

	i_infile.close();

	return coordinates;
}

//print to the 'output' file the clusters.
void writeToOutputFile(point* result, int size)
{
	ofstream outFile;
	outFile.open("output.txt");
	for (int i = 0; i < size-1; i++)
		outFile << result[i].cluster <<endl;
	outFile << result[size-1].cluster;
	outFile.close();
}

//main function
int main()
{
	point *coordinates = NULL;
	point *clusteredCoors = NULL;
	string algorithm;
	int numberOfClusters;
	int numberOfPoints;

	ifstream file("input.txt");
	coordinates = processInputFile(file, algorithm, numberOfClusters);
	HierarchicalClustering area(coordinates, algorithm, numberOfClusters);
	clusteredCoors = area.clusterPoints(numberOfPoints);
	writeToOutputFile(clusteredCoors, numberOfPoints);
	return 0;
}	