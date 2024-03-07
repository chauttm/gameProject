struct Point {
	double x;
	double y;
};

struct Triangle {
	Point a;
	Point b;
	Point c;
};

struct Triangle2 {
	Point a[3];
};

int main(int argc, char** argv) {
    Point p;
    Triangle t1;
    Triangle2 t2;
}
