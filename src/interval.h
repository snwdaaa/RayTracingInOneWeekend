#ifndef INTERVAL_H
#define INTERVAL_H

class interval {
    public:
	double min, max;

	interval() : min(+infinity), max(-infinity) {}
	interval(double min, double max) : min(min), max(max) {}

	// ���� ũ��
	double size() const {
	    return max - min;
	}

	// x�� ���� �ȿ� �ִ���? (�糡 ����)
	bool contains(double x) const {
	    return min <= x && x <= max;
	}

	// x�� ���� �ȿ� �ִ���? (�糡 ����)
	bool surrounds(double x) const {
	    return min < x && x < max;
	}

	static const interval empty, universe;
};

const interval interval::empty = interval(+infinity, -infinity);
const interval interval::universe = interval(-infinity, infinity);

#endif