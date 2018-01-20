#include <iostream>
#include <string>

using namespace std;

//struct of 2D point to cluster
struct point
{
	double x;
	double y;
	int cluster;
};

//This class gets a bunch of 2D coordinates,
//and cluster them with "Hierarchical Clustering" by 2 ways: 'single link' or 'average link'.
class HierarchicalClustering
{
private:
	point *coordinates;
	int numOfPoints;
	string distanceAlgorithm;
	int finalNumOfClusters;
	int nowNumOfClusters;
	int originalNumOfClusters;

	// Set 1-to-number_of_points clusters to the points.
	void initPoints();
	//Find the distance between 2 clusters by "single-link" or "average-link"
	double calDistance(int, int);
	//distance between two clusters is the shortest distance between a pair of elements from the two clusters.
	double singlelink(int, int);
	//distance between two clusters is the average distance between each pair of elements from the two clusters.
	double averagelink(int, int);
	//change 2 cluster groups to one cluster (the min cluster)
	void changeClusters(int, int);
	//Change the clusters order to "1" to "needed clusters numbers"
	void changeToRightClusters();

public:
	//constructor
	HierarchicalClustering(point *coordinates, string algorithm, int numOfClusters);
	// Clustering points to clusters.
	point* clusterPoints(int &);
	~HierarchicalClustering();
};

