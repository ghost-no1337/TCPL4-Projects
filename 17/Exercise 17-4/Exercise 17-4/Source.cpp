#include <iostream>
#include <map>
using namespace std;

class Histogram {
public:
	Histogram(double mn, double mx, double gp);
	void insert(double value);
	
	double minimum() const { return min; }
	double maximum() const { return max; }
	double interval_gap() const { return gap; }
	int times(double interval_min) { return values[interval_min]; }
private:
	map<double, int> values;
	double min;
	double max;
	double gap;
};

Histogram::Histogram(double mn, double mx, double gp)
	:min{ mn }, max{ mx }, gap{ gp }
{
	if (max <= min)
		throw runtime_error("bad interval");
	if (gap <= 0)
		throw runtime_error("bad gap");

	double d = min;
	while (d < max) {
		values[d] = 0;
		d += gap;
	}
}

void Histogram::insert(double value)
{
	if (value < min || value > max)
		throw runtime_error("insert out of range");
	double d = min;
	while (d + gap < max) {
		if (d <= value && value < d + gap) {
			++values[d];
			return;
		}
		d += gap;
	}
	++values[d];
}

ostream& operator<<(ostream& os, Histogram& h)
{
	double d = h.minimum();
	while (d + h.interval_gap() < h.maximum()) {
		os << "Range [" << d << ", " << d + h.interval_gap() << "): " << h.times(d) << '\n';
		d += h.interval_gap();
	}
	os << "Range [" << d << ", " << h.maximum() << "]: " << h.times(d) << '\n';
	return os;
}

int main()
try {
	Histogram hg{ 0, 10, 1 };
	hg.insert(0.5);
	hg.insert(5.5);
	hg.insert(9.5);
	cout << hg;
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	char ch; cin >> ch;
	return 1;
}
catch (...) {
	cerr << "error: unknown error\n";
	char ch; cin >> ch;
	return -1;
}