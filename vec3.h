#ifndef VEC3_H

#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 {
  private:
    float e[3];

  public:
    vec3() : e{0, 0, 0} {}
    vec3(float x, float y, float z) : e{x, y, z} {}
    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }
    float operator[](int id) const { return e[id]; }
    float &operator[](int id) { return e[id]; }

    vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    vec3 &operator+=(const vec3 &rh) {
        e[0] += rh.e[0], e[1] += rh.e[1], e[2] += rh.e[2];
        return *this;
    }
    vec3 &operator-=(const vec3 &rh) {
        e[0] -= rh.e[0], e[1] -= rh.e[1], e[2] -= rh.e[2];
        return *this;
    }
    vec3 &operator*=(float rh) {
        e[0] *= rh, e[1] *= rh, e[2] *= rh;
        return *this;
    }
    vec3 &operator/=(float rh) { return (*this) *= (1. / rh); }

    float length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
    float length() const { return std::sqrt(length_squared()); }

    static vec3 random() { return vec3(random_float(), random_float(), random_float()); }
    static vec3 random(float min, float max) {
        return vec3(random_float(min, max), random_float(min, max), random_float(min, max));
    }
};

using point3 = vec3;

// Vector Utility Functions

inline std::ostream &operator<<(std::ostream &o, vec3 v) { return o << "(" << v[0] << ", " << v[1] << ", " << v[2] << ")"; }

inline vec3 operator+(const vec3 &lh, const vec3 &rh) { return vec3(lh[0] + rh[0], lh[1] + rh[1], lh[2] + rh[2]); }
inline vec3 operator-(const vec3 &lh, const vec3 &rh) { return vec3(lh[0] - rh[0], lh[1] - rh[1], lh[2] - rh[2]); }
inline vec3 operator*(float lh, const vec3 &rh) { return vec3(rh[0] * lh, rh[1] * lh, rh[2] * lh); }
inline vec3 operator*(const vec3 &lh, float rh) { return rh * lh; }
inline vec3 operator/(const vec3 &lh, float rh) { return lh * (1. / rh); }

inline float dot(const vec3 &lh, const vec3 &rh) { return lh[0] * rh[0] + lh[1] * rh[1] + lh[2] * rh[2]; }
inline vec3 cross(const vec3 &lh, const vec3 &rh) {
    return vec3(lh[1] * rh[2] - lh[2] * rh[1], lh[2] * rh[0] - lh[0] * rh[2], lh[0] * rh[1] - lh[1] * rh[0]);
}
inline vec3 unit_vector(const vec3 &v) { return v / v.length(); }

inline vec3 random_unit_vector() {
    while (true) {
        vec3 v = vec3::random(-1.0, 1.0);
        float lensq = v.length_squared();
        if (lensq > eps && lensq < 1) {
            v = unit_vector(v);
            return v;
        }
    }
}

inline vec3 random_on_hemisphere(const vec3 &norm) {
    vec3 v = random_unit_vector();
    if (dot(v, norm) > 0) {
        return v;
    } else {
        return -v;
    }
}

#endif