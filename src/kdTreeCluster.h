#ifndef KDTREECLUSTER_H_
#define KDTREECLUSTER_H_

#include "render/render.h"

// Structure to represent node of kd tree
struct Node
{
	std::vector<float> point;
	int id;
	Node* left;
	Node* right;

	Node(std::vector<float> arr, int setId)
	:	point(arr), id(setId), left(NULL), right(NULL)
	{}
};

struct KdTree
{
	Node* root;

	KdTree()
	: root(NULL)
	{}

	
	void insertHelper(Node** node, uint depth, std::vector<float> point, int id){
		// the function should create a new node and place correctly with in the root 
		if(*node == NULL)
      	{
        	*node = new Node(point, id);
      	}

      	else 
      	{
			// Calculate current depth
        	uint cd = depth%3;
			if (point[cd] < ((*node)->point[cd]))
				insertHelper(&((*node)->left), depth+1, point, id);
			else
				insertHelper(&((*node)->right), depth+1, point, id);				
      	}

	}
	
	void insert(std::vector<float> point, int id)
	{
		// TODO: Fill in this function to insert a new point into the tree
		insertHelper(&root, 0, point, id);
		

	}
	
	/*
	std::vector<int> sortbyIndex(uint k, std::vector<std::vector<float>> points){
		std::vector<int> indexList;
		std::vector<int> a;
		for (size_t i=0; i<points.size(); ++i){
			indexList.push_back(i);
			a.push_back(pionts[i][k]);
		}

		for(size_t i=1; i<n; ++i){
			int end= i-1;
			float tmp= a[i];
			int tmp_index = indexList[i];
			while (end >=0)
			{
				
				if(a[end]>tmp)
				{
					a[end+1] = a[end];
					indexList[end+1] = indexList[end];
					--end;
				}
				else 
					break;
			}
			a[end+1] = tmp;
			indexList[end+1] = tmp_index;
		}

		return indexList;
	}

	void insertHelper(Node** node, uint depth, std::vector<std::vector<float>> points, int id)
	{	
		// the function should create a new node and place correctly with in the root 
		if(*node == NULL)
      	{
        	*node = new Node(point, id);
      	}

      	else 
      	{
			// Calculate current depth
        	uint cd = depth%3;
			if (point[cd] < ((*node)->point[cd]))
				insertHelper(&((*node)->left), cd, point, id);
			else
				insertHelper(&((*node)->right), cd, point, id);				
      	}
		
		
	}

	void insert(std::vector<std::vector<float>> points)
	{
		// insert points into the tree
		int depth = 0;
		int len = points.size();       // get points vector size
		std::vector<int> ids;          // create points index vector
		for(int i=0; i<len; ++i)
			ids.push_back(i);
		int midpointIndex = len/2;
		// to construct balanced tree in order to reduce the depth of the tree.
		// in first 2 depth, namely x, y cordinate, sort the points index by depth or cordinate. sort index,not change points by self.
		// then pick up the midpoint by index in the points vector.
		if (depth<2)
		{
			std::vector<int> ids = sortbyIndex(depth,points);
			depth++;
		}

		// then insert the picked midpoint
		
	}
	*/

	void searchHelper(std::vector<float> target, Node* node, int depth, float distanceTol, std::vector<int>& ids){
		if (node!=NULL ){
			if((node->point[0]>=target[0]-distanceTol)&&(node->point[0]<=target[0]+distanceTol)&&
			(node->point[1]>=target[1]-distanceTol)&&(node->point[1]<=target[1]+distanceTol)&&
			(node->point[2]>=target[2]-distanceTol)&&(node->point[2]<=target[2]+distanceTol)){
				float distance = sqrt((node->point[0]-target[0])*(node->point[0]-target[0])+(node->point[1]-target[1])*(node->point[1]-target[1])
				+(node->point[2]-target[2])*(node->point[2]-target[2]));
				if(distance<=distanceTol)
					ids.push_back(node->id);
			}

			// check across boundary
			if((target[depth%3]-distanceTol)<node->point[depth%3])
				searchHelper(target, node->left, depth+1, distanceTol, ids);
			if((target[depth%3]+distanceTol)>node->point[depth%3])
				searchHelper(target, node->right, depth+1, distanceTol, ids);
		}

	}

	// return a list of point ids in the tree that are within distance of target
	std::vector<int> search(std::vector<float> target, float distanceTol)
	{
		std::vector<int> ids;
		searchHelper(target, root, 0, distanceTol,ids);
		return ids;
	}
	

};

void clusterHelper(int indice, const std::vector<std::vector<float>>& points, std::vector<int>& cluster, std::vector<bool>& processed, KdTree* tree, 
float distanceTol,int maxSize);

std::vector<std::vector<int>> euclideanCluster(const std::vector<std::vector<float>>& points, KdTree* tree, float distanceTol,int minSize, int maxSize);


#endif