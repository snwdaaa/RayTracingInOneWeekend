#include "rtWeekend.h"
#include "interval.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "image_opener.h"
#include "camera.h"
#include "material.h"

int main() {
    // 월드
    hittable_list world; // 모든 hittable한 오브젝트를 저장

    // 물체에 사용할 머티리얼
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<dielectric>(1.00 / 1.33);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
    world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(make_shared<sphere>(point3(1.0, 0.0, -1.2), 0.5, material_right));

    // 카메라
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 4096;
    cam.samples_per_pixel = 10;
    cam.max_depth = 10;

    cam.render(world); // hittable_list에 있는 모든 물체에 대해 렌더링
}