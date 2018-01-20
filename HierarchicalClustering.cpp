#include <iostream>
#include <string>
#include <limits> 
#include <math.h>
#include "HierarchicalClustering.h"

using namespace std;

//Hierarchical Clustering class is taking care about bunch of 2D point, and clustering them,
//by 2 distance algorithms: single link and average link. 
HierarchicalClustering::HierarchicalClustering(point *i_coordinates, string i_algorithm, int i_numOfClusters)
{
	this->coordinates = i_coordinates;
	this->distanceAlgorithm = i_algorithm;
	this->finalNumOfClusters = i_numOfClusters;
	this->originalNumOfClusters = i_coordinates[0].cluster;
	this->numOfPoints = i_coordinates[0].cluster;
	this->nowNumOfClusters = i_coordinates[0].cluster;
}

// Set 1-to-number_of_points clusters to the points.
void HierarchicalClustering::initPoints()
{
	for (int i = 1; i < numOfPoints; i++)
		coordinates[i-1].cluster = i;
}

//Find the distance between 2 clusters by "single-link" or "average-link"
double HierarchicalClustering::calDistance(int cluster1, int cluster2)
{
	double dist;
	if (distanceAlgorithm == "single link")
		dist = singlelink(cluster1, cluster2);
	else
		dist = averagelink(cluster1, cluster2);
	
	return dist;
}

//distance between two clusters is the shortest distance between a pair of elements from the two clusters.
double HierarchicalClustering::singlelink(int cluster1, int cluster2)
{
	double minDist = numeric_limits<float>::max();
	double dist = minDist;
	for (int i = 0; i<numOfPoints; i++)
		for (int j = 0; j < numOfPoints; j++)
		{
			if (coordinates[i].cluster == cluster1 && coordinates[j].cluster == cluster2)
			{
				point a = coordinates[i];
				point b = coordinates[j];
				double xdis = coordinates[i].x - coordinates[j].x;
				double ydis = coordinates[i].y - coordinates[j].y;
				xdis = pow(xdis, 2);
				ydis = pow(ydis, 2);
				dist = sqrt(xdis + ydis);
				if (dist < minDist)
					minDist = dist;
			}
		}
	return dist;
}

//distance between two clusters is the average distance between each pair of elements from the two clusters.
double HierarchicalClustering::averagelink(int cluster1, int cluster2)
{
	double dist;
	double totalDist = 0;
	double numberOfCalculatedPoints = 0;
	for (int i = 0; i<numOfPoints; i++)
		for (int j = 0; j < numOfPoints; j++)
		{
			if (coordinates[i].cluster == cluster1 && coordinates[j].cluster == cluster2)
			{
				point a = coordinates[i];
				point b = coordinates[j];
				double xdis = coordinates[i].x - coordinates[j].x;
				double ydis = coordinates[i].y - coordinates[j].y;
				xdis = pow(xdis, 2);
				ydis = pow(ydis, 2);
				dist = sqrt(xdis + ydis);
				totalDist += dist;
				numberOfCalculatedPoints++;
			}
		}
	double result = totalDist / numberOfCalculatedPoints;
	return result;
}

//change 2 cluster groups to one cluster (the min cluster)
void HierarchicalClustering::changeClusters(int i_cluster, int i_clusterToChnage)
{
	if (i_cluster > i_clusterToChnage)
	{
		int swapCluster = i_clusterToChnage;
		i_clusterToChnage = i_cluster;
		i_cluster = swapCluster;
	}
	for (int i=0; i < numOfPoints; i++)
	{
		if (coordinates[i].cluster == i_clusterToChnage)
			coordinates[i].cluster = i_cluster;
	}
	nowNumOfClusters--;
}

//Change the clusters order to "1" to "needed clusters numbers"
void HierarchicalClustering::changeToRightClusters()
{
	int *coorsClusters = new int[numOfPoints];
	for (int i = 0; i < numOfPoints; i++)
		coorsClusters[i] = 1;

	int rightCluster = 1;
	for (int j = 0; j < numOfPoints; j++)
	{
		if (coorsClusters[j] != 0)
		{
			int thisCluster = coordinates[j].cluster;
			for (int i = 0; i < numOfPoints; i++)
			{
				if (coordinates[i].cluster == thisCluster)
				{
					coordinates[i].cluster = rightCluster;
					coorsClusters[i] = 0;
				}
			}
			rightCluster++;
		}
	}
}

// Clustering points to clusters.
point* HierarchicalClustering::clusterPoints(int &o_numberOfPoints)
{
	initPoints();
	o_numberOfPoints = numOfPoints;
	while (nowNumOfClusters > finalNumOfClusters)
	{
		double minimalDist = numeric_limits<float>::max();
		int c1, c2; //clusters
		for (int i = 1; i < originalNumOfClusters +1; i++)
		{
			for (int j = 1; j < originalNumOfClusters +1; j++)
			{
				if (i == j)
					continue;
				double dist = calDistance(i, j);
				if (dist < minimalDist)
				{
					c1 = i;
					c2 = j;
					minimalDist = dist;
				}
			}
		}
		changeClusters(c1, c2);
	}
	changeToRightClusters();
	return coordinates;
}

HierarchicalClustering::~HierarchicalClustering()
{
}
