#ifndef RAY_H_
#define RAY_H_

#include "vec.h"
#include <vector>

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


class Ray{
  public:
    Ray();
    Ray(const Vec& o, const Vec& d);
    ~Ray();

    Vec origin() const;
    Vec direction() const;
    Vec point_at_t(float t);

    std::vector<Hit_Record> hitRecordList;

    Hit_Record find_first_hit() const;

  private:
    Vec o_;
    Vec d_;
};

#endif
