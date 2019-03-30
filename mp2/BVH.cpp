#include "BVH.h"
#include <iostream>
#include <cmath>

BoundingSphere::BoundingSphere(){
  BoundingSphere(100, Vec(0,0,-10));
}

BoundingSphere::BoundingSphere(float r, Vec c){
  radius = r;
  center = c;
  type = "bounding sphere";
}



bool BoundingSphere::hit(Ray& r, float tmin, float tmax) const{
  Vec oc = r.origin() - center;
  float a = r.direction().dot(r.direction());
  float b = 2*oc.dot(r.direction());
  float c = oc.dot(oc) - radius*radius;
  float discriminant = b*b-4*a*c;
  if (discriminant > 0){
    float t2 = (-1*b - sqrt(discriminant))/(2*a);
    float t1 = (-1*b + sqrt(discriminant))/(2*a);
    if (t2 > tmin && t2 < tmax){
      return true;
    }
    else{
      if (t1 > tmin && t1 < tmax){
        return true;
      }
    }
  }
  return false;
}

bool BVHTree::hitBoundingSpheres(Ray& r, float tmin, float tmax, BVHTree::BVHTreeNode* subroot){
  bool hitAnything = false;
  if (subroot->isleaf){
    if (subroot->bs.hit(r, tmin, tmax)){
      for (unsigned i = 0; i < subroot->slist.size(); i++){
        if (subroot->slist[i]->hit(r, tmin, tmax)){
          hitAnything = true;
        }
      }
    }
    return hitAnything;
  }
  else{
    if (subroot->bs.hit(r, tmin, tmax)){
      for (int i = 0; i < 8; i++){
        if (hitBoundingSpheres(r, tmin, tmax, subroot->children[i])){
          hitAnything = true;
        }
      }
    }
    return hitAnything;
  }
}

BVHTree::BVHTreeNode::BVHTreeNode(Vec minDims, Vec maxDims){
  isleaf = true;
  Vec dif = (maxDims-minDims);
  Vec center = minDims+(dif/2);
  float radius = dif.magnitude()/2;
  bs = BoundingSphere(radius, center);
  bbmin = minDims;
  bbmax = maxDims;
}


BVHTree::BVHTree(Vec minDims, Vec maxDims, Vec smallestPartitionMinVal, Vec smallestPartitionMaxVal){
  root = new BVHTreeNode(minDims, maxDims);
  BoundingBoxMax = maxDims;
  BoundingBoxMin = minDims;
  smallestPartitionMax = smallestPartitionMaxVal;
  smallestPartitionMin = smallestPartitionMinVal;
}


bool BVHTree::BVHTreeNode::continuePartitioning(Vec currentPartitionDimensions, Vec bbmin, Vec bbmax) const{
  for (int i = 0; i < 3; i++){
    if (currentPartitionDimensions[i]/2 < (bbmax-bbmin)[i]){
      return false;
    }
  }
  return true;
}

bool insideBox(Vec minDims, Vec maxDims, Vec point){
  for (int i = 0; i < 3; i++){
    if (point[i] < minDims[i] || point[i] > maxDims[i]){
      return false;
    }
  }
  return true;
}

void BVHTree::insert(Surface* surface){
  insertSurface(surface, BoundingBoxMin, BoundingBoxMax, root);
}

void BVHTree::insertSurface(Surface* surface, Vec minDims, Vec maxDims, BVHTree::BVHTreeNode* subroot){
  vector<Vec> surfaceBoundingPoints;
  Vec bmin = surface->boundingMin;
  Vec bmax = surface->boundingMax;
  surfaceBoundingPoints.push_back(Vec(bmin[0], bmin[1], bmin[2]));
  surfaceBoundingPoints.push_back(Vec(bmax[0], bmin[1], bmin[2]));
  surfaceBoundingPoints.push_back(Vec(bmin[0], bmax[1], bmin[2]));
  surfaceBoundingPoints.push_back(Vec(bmax[0], bmax[1], bmin[2]));
  surfaceBoundingPoints.push_back(Vec(bmin[0], bmin[1], bmax[2]));
  surfaceBoundingPoints.push_back(Vec(bmax[0], bmin[1], bmax[2]));
  surfaceBoundingPoints.push_back(Vec(bmin[0], bmax[1], bmax[2]));
  surfaceBoundingPoints.push_back(Vec(bmax[0], bmax[1], bmax[2]));
  int sbp = surfaceBoundingPoints.size();

  for (int i = 0; i < sbp; i++){
    Treebuilder(surface, surfaceBoundingPoints[i], minDims, maxDims, subroot);
  }
}

void BVHTree::Treebuilder(Surface* surface, Vec point, Vec minDims, Vec maxDims, BVHTree::BVHTreeNode* subroot){
  Vec bmin = surface->boundingMin;
  Vec bmax = surface->boundingMax;

  if (!subroot->continuePartitioning((maxDims-minDims), this->smallestPartitionMin, this->smallestPartitionMax)){ //if we can't partition anymore, just add to list
    subroot->slist.push_back(surface);
    return;
  }

  //vectors representing min and max dimensions of partitions of the current partition
  Vec minDimsLeftBottomBack = minDims;
  Vec maxDimsLeftBottomBack = (maxDims+minDims)/2;
  Vec minDimsRightBottomBack = Vec((maxDims[0]+minDims[0])/2, minDims[1], minDims[2]);
  Vec maxDimsRightBottomBack = Vec(maxDims[0], (maxDims[1]+minDims[1])/2, (maxDims[2]+minDims[2])/2);
  Vec minDimsLeftTopBack = Vec(minDims[0], (maxDims[1]+minDims[1])/2, minDims[2]);
  Vec maxDimsLeftTopBack = Vec((maxDims[0]+minDims[0])/2, maxDims[1], (maxDims[2]+minDims[2])/2);
  Vec minDimsRightTopBack = Vec((maxDims[0]+minDims[0])/2, (maxDims[1]+minDims[1])/2, minDims[2]);
  Vec maxDimsRightTopBack = Vec(maxDims[0], maxDims[1], (maxDims[2]+minDims[2])/2);
  Vec minDimsLeftBottomFront = Vec(minDims[0], minDims[1], (maxDims[2]+minDims[2])/2);
  Vec maxDimsLeftBottomFront  = Vec((maxDims[0]+minDims[0])/2, (maxDims[1]+minDims[1])/2, maxDims[2]);
  Vec minDimsRightBottomFront = Vec((maxDims[0]+minDims[0])/2, minDims[1], (maxDims[2]+minDims[2])/2);
  Vec maxDimsRightBottomFront = Vec(maxDims[0], (maxDims[1]+minDims[1])/2, maxDims[2]);
  Vec minDimsLeftTopFront = Vec(minDims[0], (maxDims[1]+minDims[1])/2, (maxDims[2]+minDims[2])/2);
  Vec maxDimsLeftTopFront = Vec((maxDims[0]+minDims[0])/2, maxDims[1], maxDims[2]);
  Vec minDimsRightTopFront = (maxDims+minDims)/2;
  Vec maxDimsRightTopFront = maxDims;

  if (!subroot->isleaf){
    if (!subroot->slist.empty()){subroot->slist.pop_back();}
    if (insideBox(minDimsLeftBottomBack, maxDimsLeftBottomBack, point)){
      Treebuilder(surface, point, minDimsLeftBottomBack, maxDimsLeftBottomBack, subroot->children[0]);
    }
    else if (insideBox(minDimsRightBottomBack, maxDimsRightBottomBack, point)){
      Treebuilder(surface, point, minDimsRightBottomBack, maxDimsRightBottomBack, subroot->children[1]);
    }
    else if (insideBox(minDimsLeftTopBack, maxDimsLeftTopBack, point)){
      Treebuilder(surface, point, minDimsLeftTopBack, maxDimsLeftTopBack, subroot->children[2]);
    }
    else if (insideBox(minDimsRightTopBack, maxDimsRightTopBack, point)){
      Treebuilder(surface, point, minDimsRightTopBack, maxDimsRightTopBack, subroot->children[3]);
    }
    else if (insideBox(minDimsLeftBottomFront, maxDimsLeftBottomFront, point)){
      Treebuilder(surface, point, minDimsLeftBottomFront, maxDimsLeftBottomFront, subroot->children[4]);
    }
    else if (insideBox(minDimsRightBottomFront, maxDimsRightBottomFront, point)){
      Treebuilder(surface, point, minDimsRightBottomFront, maxDimsRightBottomFront, subroot->children[5]);
    }
    else if (insideBox(minDimsLeftTopFront, maxDimsLeftTopFront, point)){
      Treebuilder(surface, point, minDimsLeftTopFront, maxDimsLeftTopFront, subroot->children[6]);
    }
    else if (insideBox(minDimsRightTopFront, maxDimsRightTopFront, point)){
      Treebuilder(surface, point, minDimsRightTopFront, maxDimsRightTopFront, subroot->children[7]);
    }
  }
  //at this point we are at a leaf
  if (subroot->isleaf){
    bool alreadyInList = false;
    for (int i = 0; i < (int)subroot->slist.size(); i++){
      if (subroot->slist[i] == surface){alreadyInList = true;}
    }
    if (!subroot->slist.empty() && !alreadyInList){
      subroot->children.push_back(new BVHTreeNode(minDimsLeftBottomBack, maxDimsLeftBottomBack));
      subroot->children.push_back(new BVHTreeNode(minDimsRightBottomBack, maxDimsRightBottomBack));
      subroot->children.push_back(new BVHTreeNode(minDimsLeftTopBack, maxDimsLeftTopBack));
      subroot->children.push_back(new BVHTreeNode(minDimsRightTopBack, maxDimsRightTopBack));
      subroot->children.push_back(new BVHTreeNode(minDimsLeftBottomFront, maxDimsLeftBottomFront));
      subroot->children.push_back(new BVHTreeNode(minDimsRightBottomFront, maxDimsRightBottomFront));
      subroot->children.push_back(new BVHTreeNode(minDimsLeftTopFront, maxDimsLeftTopFront));
      subroot->children.push_back(new BVHTreeNode(minDimsRightTopFront, maxDimsRightTopFront));
      subroot->isleaf = false;
      for (int i = subroot->points.size()-1; i >= 0; i--){
        Surface* temp = subroot->slist[0];
        Treebuilder(temp, subroot->points[i], minDims, maxDims, subroot);
        subroot->points.pop_back();
      }
      Treebuilder(surface, point, minDims, maxDims, subroot);
      subroot->slist.pop_back();
    }
    else{
      subroot->points.push_back(point);
      if (!alreadyInList){
        subroot->slist.push_back(surface);
      }
    }
  }

}
void BVHTree::TraverseTree(BVHTree::BVHTreeNode* subroot){
  if (subroot->isleaf){return;}
  TraverseTree(subroot->children[0]);
  TraverseTree(subroot->children[1]);
  TraverseTree(subroot->children[2]);
  TraverseTree(subroot->children[3]);
  TraverseTree(subroot->children[4]);
  TraverseTree(subroot->children[5]);
  TraverseTree(subroot->children[6]);
  TraverseTree(subroot->children[7]);
}
