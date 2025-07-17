#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
    public:
	double min, max;

	interval() : min(+infinity), max(-infinity) {}
	interval(double min, double max) : min(min), max(max) {}

	// 구간 크기
	double size() const {
	    return max - min;
	}

	// x가 구간 안에 있는지? (양끝 포함)
	bool contains(double x) const {
	    return min <= x && x <= max;
	}

	// x가 구간 안에 있는지? (양끝 제외)
	bool surrounds(double x) const {
	    return min < x && x < max;
	}

	static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, infinity);

#endif