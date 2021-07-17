#pragma once

#include <istream>

struct Vector {
  double x, y, z;
  Vector(const double &_x = 0., const double &_y = 0., const double &_z = 0.)
      : x(_x), y(_y), z(_z) {}
  Vector operator+(const Vector &rhs) const {
    return Vector(x + rhs.x, y + rhs.y, z + rhs.z);
  }
  Vector &operator+=(const Vector &rhs) {
    *this = *this + rhs;
    return *this;
  }
  Vector operator-(const Vector &rhs) const {
    return Vector(x - rhs.x, y - rhs.y, z - rhs.z);
  }
  Vector operator*(const double &rhs) const {
    return Vector(x * rhs, y * rhs, z * rhs);
  }
  Vector cross(const Vector &rhs) const {  // cross
    return Vector(y * rhs.z - z * rhs.y, z * rhs.x - x * rhs.z,
                  x * rhs.y - y * rhs.x);
  }
  double dot(const Vector &rhs) const {  // dot
    return x * rhs.x + y * rhs.y + z * rhs.z;
  }
  Vector operator%(const Vector &rhs) const {  // multiple
    return Vector(x * rhs.x, y * rhs.y, z * rhs.z);
  }
  Vector &normalize() {
    *this = *this * (1. / sqrt(x * x + y * y + z * z));
    return *this;
  }
  friend std::istream &operator>>(std::istream &is, Vector &other) {
    is >> other.x >> other.y >> other.z;
    return is;
  }
};

struct Ray {
  Vector ori, dir;
  Ray(const Vector &_ori = Vector(), const Vector &_dir = Vector()) {
    ori = _ori;
    dir = _dir;
  }
};
