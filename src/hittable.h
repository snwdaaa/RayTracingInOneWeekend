#ifndef HITTABLE_H
#define HITTABLE_H

// hit 정보
class hit_record {
public:
    point3 p; // 충돌 지점
    vec3 normal; // 충돌 지점의 법선 벡터
    double t; // 레이 방정식 매개변수
    bool front_face; // 레이가 바깥쪽에서 들어오는지 여부

    // outward_normal은 기존에 구한 법선 벡터
    // outward_normal은 단위 벡터라고 가정
    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal);
        // 항상 레이의 반대 방향으로 설정
        normal = front_face ? outward_normal : -outward_normal; // front_face면 바깥으로 나가는 방향 그대로, 아니면 반대로
    }
};

// hittable한 오브젝트의 부모가 될 추상 클래스
class hittable {
public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, interval ray_t, hit_record& rec) const = 0; // 레이와 오브젝트의 hit 여부를 판단할 메서드
};

#endif