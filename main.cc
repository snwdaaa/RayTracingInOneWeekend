#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <iostream>

color ray_color(const ray& r) {
    vec3 unit_direction = unit_vector(r.direction()); // 단위 벡터로 만들기
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0); // lerp -> a가 1이면 하늘색, 0이면 흰색, 그 사이면 blend
}

int main() {
    // 레이 트레이싱 기본 흐름
    // 1. 카메라(eye)에서 화면의 픽셀 통과하는 ray 계산
    // 2. 그 ray가 scene의 어떤 오브젝트와 교차하는지 판단
    // 3. 가장 가까운 교차 지점에서 색상 계산

    // 3D 공간에 있는 가상의 직사각형 화면 viewport
    // 렌더링될 이미지의 픽셀 위치와 1:1 매핑됨
    // 카메라에서 뷰포트의 각 지점으로 레이를 발사
    // 뷰포트 가로/세로 비율 -> 렌더링 이미지의 해상도와 동일해야 픽셀들이 정사각형으로 매핑

    // 픽셀 간 간격은 뷰포트의 해상도 크기에 따라 결정
    // 대부분 정사각형 픽셀 기준

    // 이미지
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;

    // 이미지 높이 계산. 1 이상이여야 함
    int image_height = int(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // 카메라
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    // viewport_height를 구할 때 이론적인 aspect ratio 말고 이미지의 aspect ratio 사용
    // truncation때문에 실제 이미지의 aspect ratio와 다를 수 있기 때문
    auto viewport_width = viewport_height * (double(image_width) / image_height);
    auto camera_center = point3(0, 0, 0);

    // 뷰포트 엣지 수직, 수평 벡터 계산
    auto viewport_u = vec3(viewport_width, 0, 0); // 뷰포트 엣지 수평 벡터
    auto viewport_v = vec3(0, -viewport_height, 0); // 뷰포트 엣지 수직 벡터

    // 픽셀 사이 간격 -> 수직, 수평 델타 벡터 계산
    auto pixel_delta_u = viewport_u / image_width; // 수평 델타 벡터
    auto pixel_delta_v = viewport_v / image_height; // 수직 델타 벡터

    // 왼쪽 위 픽셀 위치 계산
    // 카메라 센터에서 focal_length만큼 앞으로 간 후(뷰포트에 붙음), 뷰포트 절반만큼 왼쪽으로 & 위쪽으로 이동
    auto viewport_upper_left = camera_center - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
    // 각 픽셀 중심 -> 뷰포트 왼쪽 위에서 (u + v) 절반만큼 간 위치
    auto pixel100_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // 렌더
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    // 위->아래, 왼쪽->오른쪽으로 그림
    for (int j = 0; j < image_height; j++) {
        // 이미지를 std::cout으로 내보내므로, progress indicator는 std::clog로
        std::clog << "\rScanlines remaining: " << (image_height - j) << " " << std::flush;
        for (int i = 0; i < image_width; i++) {
            // 이미지 좌표계 (i, j)를 월드 좌표계로 변환 -> i와 j에 뷰포트의 각 셀 간격을 곱함
            auto pixel_center = pixel100_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center; // 카메라 센터에서 각 픽셀 센터로 발사하는 레이 방향
            ray r(camera_center, ray_direction); // 코드를 간결하게 하기 위해 ray_direction을 단위 벡터로 만들지 않음

            color pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::clog << "\rDone                    \n";
}