#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <vector>

// hittable 오브젝트를 담는 클래스
// hittable을 상속받아서 hit 메서드를 통해 담긴 모든 hittable 오브젝트에 대한 hit 검사를 할 수 있게 함
class hittable_list : public hittable {
    public:
        std::vector<shared_ptr<hittable>> objects;
        
        hittable_list() {}
        hittable_list(shared_ptr<hittable> object) { add(object); }

        void clear() { objects.clear(); }

        void add(shared_ptr<hittable> object) {
            objects.push_back(object);
        }

        // 벡터에 저장된 모든 hittable에 대해 순차적으로 hit 검사
        // rec에는 가장 가까운 충돌 정보가 저장돼 리턴
        bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
            hit_record temp_rec;
            bool hit_anything = false;
            auto closest_so_far = ray_t.max; // 가장 가까운 충돌만 기록하기 위한 변수

            for (const auto& object : objects) {
                if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) { // 오브젝트가 레이에 부딪히면
                    hit_anything = true; // 하나라도 충돌이 있으면 true
                    closest_so_far = temp_rec.t;
                    rec = temp_rec;
                }
            }

            return hit_anything;
        }
};

#endif