#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// C++ std usings

using std::make_shared;
using std::shared_ptr;

// 상수

const double infinity = std::numeric_limits<double>::infinity(); // double 최댓값
const double pi = 3.1415926535897932385;

// 유틸리티 함수

// 도 -> 라디안 변환
inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0f;
}

// Common Header

#include "color.h"
#include "ray.h"
#include "vec3.h"

#endif