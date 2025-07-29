#include "rtWeekend.h"
#include "interval.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphere.h"
#include "triangle.h"
#include "image_opener.h"
#include "camera.h"
#include "material.h"
#include "polygon_mesh.h"

int main() {
    // 월드
    hittable_list world; // 모든 hittable한 오브젝트를 저장

    // 물체에 사용할 머티리얼
    auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
    //auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    auto material_left = make_shared<dielectric>(1.50);
    //auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
    //auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 1.0);

    world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
    //world.add(make_shared<sphere>(point3(0.0, 0.0, -1.2), 0.5, material_center));
    //world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
    //world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.4, material_bubble));
    //world.add(make_shared<sphere>(point3(1.0, 0.0, -1.2), 0.5, material_right));

    // 카메라 테스트 1
    //auto R = std::cos(pi / 4);
    //
    //auto material_left = make_shared<lambertian>(color(0, 0, 1));
    //auto material_right = make_shared<lambertian>(color(1, 0, 0));

    //world.add(make_shared<sphere>(point3(-R, 0, -1), R, material_left));
    //world.add(make_shared<sphere>(point3(R, 0, -1), R, material_right));

    // 삼각형 테스트
    auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
    //auto material_left = make_shared<metal>(color(0.3, 0.6, 0.8), 1.0);
    auto material_right = make_shared<metal>(color(0.8, 0.6, 0.2), 0.1);
  
    /*
    world.add(make_shared<triangle>(
	point3(-0.5, 0.1, 0), 
	point3(0.5, 0.1, 0),
	point3(0.0, 0.85, 0),
	material_center
    ));

    world.add(make_shared<triangle>(
	point3(-1.5, 0.1, 0.1),
	point3(-0.5, 0.1, 0),
	point3(-1.0, 0.85, 0.0),
	material_left
    ));

    world.add(make_shared<triangle>(
	point3(0.5, 0.1, 0),
	point3(1.5, 0.1, 0.1),
	point3(1.0, 0.85, 0),
	material_right
    ));
    */

    // 폴리곤 메시 테스트
 //   std::string teapot_path = "C:/Users/kkj48/Desktop/Projects/RayTracingInOneWeekend/res/teapot.obj";
 //   auto obj1 = make_shared<polygon_mesh>(
	//teapot_path,
	//material_center,
	//world,
	//point3(0, 1, 2),
	//vec3(1, 1, 1)
 //   );

 //   auto obj2 = make_shared<polygon_mesh>(
	//teapot_path,
	//material_left,
	//world,
	//point3(-5, 1, 1.7),
	//vec3(1, 1, 1)
 //   );

 //   std::string bunny_path = "C:/Users/kkj48/Desktop/Projects/RayTracingInOneWeekend/res/stanford-bunny.obj";
 //   auto obj3 = make_shared<polygon_mesh>(
	//bunny_path,
	//material_right,
	//world,
	//point3(4, 1, 1.3),
	//vec3(20, 20, 20)
 //   );

    // Triangle 개수에 따른 렌더 시간 테스트
    std::string bunny_path = "C:/Users/kkj48/Desktop/Projects/RayTracingInOneWeekend/res/stanford-bunny.obj";
    std::string bunny_path_08 = "C:/Users/kkj48/Desktop/Projects/RayTracingInOneWeekend/res/stanford-bunny-08.obj";
    std::string bunny_path_06 = "C:/Users/kkj48/Desktop/Projects/RayTracingInOneWeekend/res/stanford-bunny-06.obj";
    std::string bunny_path_04 = "C:/Users/kkj48/Desktop/Projects/RayTracingInOneWeekend/res/stanford-bunny-04.obj";
    std::string bunny_path_02 = "C:/Users/kkj48/Desktop/Projects/RayTracingInOneWeekend/res/stanford-bunny-02.obj";
    std::string bunny_path_01 = "C:/Users/kkj48/Desktop/Projects/RayTracingInOneWeekend/res/stanford-bunny-01.obj";

    auto bunny_test = make_shared<polygon_mesh>(
	bunny_path_06,
	material_center,
	world,
	point3(0, 1, 1.3),
	vec3(20, 20, 20)
    );

    // 카메라
    camera cam;
    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 2048;
    cam.samples_per_pixel = 4;
    cam.max_depth = 5;

    cam.vfov = 90;
    cam.lookfrom = point3(0, 5, -2);
    cam.lookat = point3(0, 1, 10);
    cam.vup = vec3(0, 1, 0);

    cam.render(world); // hittable_list에 있는 모든 물체에 대해 렌더링
}