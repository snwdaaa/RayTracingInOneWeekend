#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

// hit 정보
class hit_record {
public:
    point3 p;
    vec3 normal;
    double t;
};

// hittable한 오브젝트의 부모가 될 추상 클래스
class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0; // 레이와 오브젝트의 hit 여부를 판단할 메서드
};

#endif