#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

// 구 클래스
class sphere : public hittable {
public:
    sphere(const point3& center, double radius) : center(center), radius(std::fmax(0, radius)) {}

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        vec3 oc = center - r.origin(); // C-Q
        auto a = r.direction().length_squared(); // d dot d == |d|^2
        auto h = dot(r.direction(), oc); // h = d dot (C-Q)
        auto c = oc.length_squared() - radius * radius; // (C-Q) dot (C-Q) - r^2 = |(C-Q)|^2 - r^2
        auto discriminant = h*h - a*c; // 판별식 h^2 - a*c
    
        if (discriminant < 0) {
            return false;
        }

        auto sqrtd = std::sqrt(discriminant);

        // tmin ~ tmax 사이에서 가장 가까운 교차 지점 찾기
        auto root = (h - sqrtd) / a; // 이차방정식 근의 공식 -> +-라서 실근이 두 개 나오는데, 먼저 -부터 판별
        if (root <= ray_tmin || ray_tmax <= root) { // 실근이 범위를 벗어나는 경우
            root = (h + sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root)
                return false; // +- 둘 다 범위 벗어나는거면 실근 없음 -> 충돌 X
        }

        // 충돌 정보는 hit_record 객체에 레퍼런스로 전달
        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal); // 법선 벡터 방향 결정

        return true; // 충돌 O
    }
private:
    point3 center;
    double radius;
};

#endif