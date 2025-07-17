#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

#include <fstream>
#include <vector>
using color = vec3;

void write_color(std::vector<color>& value, std::ofstream& out) {
    for (auto& color : value)
    {
	auto r = color.x();
	auto g = color.y();
	auto b = color.z();

	// [0,1] 범위 값을 [0,255]로 변환
	static const interval intensity(0.000, 0.999); // 샘플링한 값 평균 저장
	int rbyte = int(256 * intensity.clamp(r));
	int gbyte = int(256 * intensity.clamp(g));
	int bbyte = int(256 * intensity.clamp(b));

	// 픽셀 컬러 컴포넌트 쓰기
	out << rbyte << " " << gbyte << " " << bbyte << "\n";
    }
}

#endif