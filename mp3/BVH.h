#ifndef BVH_H_
#define BVH_H_

#include "surface.h"

using namespace std;

class BoundingSphere: public Surface{
public:
  BoundingSphere();
  BoundingSphere(float r, Vec c);
  virtual bool hit(Ray& r, float tmin, float tmax) const;
  Vec center;
  float radius;
  std::string type;


};

class BVHTree{
public:
  struct BVHTreeNode{
    BVHTreeNode(Vec minDims, Vec maxDims);
    vector<Surface*> slist;
    vector<Vec> points;
    BoundingSphere bs;
    vector<BVHTreeNode*> children;
    Vec bbmax;
    Vec bbmin;

    bool isleaf;
    bool continuePartitioning(Vec currentPartitionDimensions, Vec bbmin, Vec bbmax) const;
  };

  Vec smallestPartitionMax;
  Vec smallestPartitionMin;
  BVHTree(Vec minDims, Vec maxDims, Vec smallestPartitionMinVal, Vec smallestPartitionMaxVal);
  Vec BoundingBoxMax;
  Vec BoundingBoxMin;
  BVHTreeNode* root;
  void insert(Surface* surface);
  bool hitBoundingSpheres(Ray& r, float tmin, float tmax, BVHTree::BVHTreeNode* subroot);
  void TraverseTree(BVHTree::BVHTreeNode* subroot);

private:
  void insertSurface(Surface* surface, Vec minDims, Vec maxDims, BVHTree::BVHTreeNode* subroot);
  void Treebuilder(Surface* surface, Vec point, Vec minDims, Vec maxDims, BVHTree::BVHTreeNode* subroot);

};

#endif
