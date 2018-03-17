#ifndef VEC_H_
#define VEC_H_

class Vec{
  public:
    Vec();
    Vec(float x, float y, float z);
    Vec(const Vec& other);
    ~Vec();

    float x() const;
    float y() const;
    float z() const;
    float r() const;
    float g() const;
    float b() const;


    const Vec& operator+() const;
    Vec operator-() const;
    float& operator[](int i);

    Vec operator+(const Vec& v2) const;
    Vec operator-(const Vec& v2) const;
    Vec operator*(const Vec& v2) const;
    Vec operator/(const Vec& v2) const;

    bool operator==(const Vec& v2) const;

    Vec operator*(float c) const;
    Vec operator/(float c) const;

    Vec operator+=(const Vec& v2);
    Vec operator-=(const Vec& v2);
    Vec operator*=(const Vec& v2);
    Vec operator/=(const Vec& v2);

    Vec operator*=(float c);
    Vec operator/=(float c);

    float dot(const Vec& v2) const;
    Vec cross(const Vec& v2) const;
    float sqr_mag() const;
    float magnitude() const;
    Vec unit() const;
    Vec make_unit();

    void print() const;

  private:
    float e[3];

};


#endif
