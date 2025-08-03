#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
  public:
    float min, max;
    interval() : min(+infinity), max(-infinity) {}
    interval(float l, float r) : min(l), max(r) {}
    float size() const { return max - min; }

    bool contains(float x) const { return min <= x && x <= max; }
    bool surrounds(float x) const { return min < x && x < max; }
    float clamp(float x) const {
        if (x < min) x = min;
        if (x > max) x = max;
        return x;
    }

    static const interval empty, universe;
};

static const interval empty = interval(+infinity, -infinity);
static const interval universe = interval(-infinity, +infinity);

std::ostream &operator<<(std::ostream &o, const interval &I) {
    // use "[]" to distinguish from vectors
    return o << "[" << I.min << ", " << I.max << "]";
}

#endif