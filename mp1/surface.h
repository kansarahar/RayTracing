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
    const Surface& operator[](int i) const;
    void addSurface(const Surface& s);
    const Surface& find_first_hit();
    int size();
  private:
    int length;
    struct ListNode{
      ListNode(const Surface& s);
      ~ListNode();
      const Surface& s_;
      ListNode* next;
    };
    ListNode* head;
};

#endif
