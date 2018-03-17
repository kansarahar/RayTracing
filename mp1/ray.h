#ifndef RAY_H_
#define RAY_H_

#include "vec.h"

class Hit_Record{
  public:
    Hit_Record(float tval, const Vec& p, const Vec& n, const Vec& c);
    Hit_Record(const Hit_Record& other);
    ~Hit_Record();

    float t;
    Vec point;
    Vec normal;
    Vec color;
};

class Hit_Record_List{
  public:
    Hit_Record_List();
    ~Hit_Record_List();
    const Hit_Record& operator[](int i) const;
    void addHR(const Hit_Record& hr);
    const Hit_Record& find_first_hit();
    int size();
  private:
    int length;
    struct ListNode{
      ListNode(const Hit_Record& hr);
      ~ListNode();
      const Hit_Record& hr_;
      ListNode* next;
    };
    ListNode* head;
};

class Ray{
  public:
    Ray();
    Ray(const Vec& o, const Vec& d);
    ~Ray();

    Vec origin() const;
    Vec direction() const;
    Vec point_at_t(float t);

    Hit_Record_List hrl;

  private:
    Vec o_;
    Vec d_;
};

#endif
