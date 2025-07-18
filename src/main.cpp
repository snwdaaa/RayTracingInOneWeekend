#include "rtWeekend.h"
#include "interval.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "image_opener.h"
#include "camera.h"

int main() {
    // 월드
    hittable_list world; // 모든 hittable한 오브젝트를 저장
    world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    // 카메라
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 4096;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    cam.render(world); // hittable_list에 있는 모든 물체에 대해 렌더링
}