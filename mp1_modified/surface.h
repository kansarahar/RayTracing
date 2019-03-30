#ifndef SURFACE_H_
#define SURFACE_H_

#include "ray.h"
#include <string>

class Surface{
  public:
    virtual bool hit(Ray& r, float tmin, float tmax) const = 0;
    std::string type;
    Vec color;
};

class Surface_List{
  public:
    Surface_List();
    ~Surface_List();
    Surface& operator[](int i);
    void addSurface(Surface* s);
    int size();
    int capacity();
    bool empty();
  private:
    int length_;
    int capacity_;
    bool empty_;
    Surface** slist;
    // struct ListNode{
    //   ListNode(const Surface& s);
    //   ~ListNode();
    //   const Surface& s_;
    //   ListNode* next;
    // };
    // ListNode* head;
};

#endif
