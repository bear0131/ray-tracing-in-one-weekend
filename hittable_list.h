#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>

#include "hittable.h"
#include "rtweekend.h"

using std::make_shared;
using std::shared_ptr;

class hittable_list : public hittable {
  public:
    std::vector<shared_ptr<hittable> > objs;
    hittable_list() {}
    hittable_list(shared_ptr<hittable> p) { add(p); }
    void add(shared_ptr<hittable> p) { objs.push_back(p); }
    bool hit(const ray& r, const interval& ray_t, hit_record& rec) const override {
        if (is_debugging) {
            std::cerr << "world hitting " << r << std::endl;
        }
        hit_record temp_rec;
        float closest_hit = ray_t.max;
        bool hit_anything = false;
        for (const auto& p : objs) {
            if (p->hit(r, interval(ray_t.min, closest_hit), temp_rec)) {
                hit_anything = true;
                closest_hit = temp_rec.t;
                rec = temp_rec;
            }
        }
        return hit_anything;
    }
};

#endif