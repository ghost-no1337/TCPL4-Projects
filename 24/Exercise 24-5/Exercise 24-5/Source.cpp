#include <iostream>
#include <vector>
using namespace std;

struct Record {
	int count;
	int price;
};

template <typename T, typename Compare = std::less<T>>
void sort(vector<T>& v)
{
	Compare cmp;
	const size_t n = v.size();

	for (int gap = n / 2; 0 < gap; gap /= 2)
		for (int i = gap; i < n; i++)
			for (int j = i - gap; 0 <= j; j -= gap)
				if (cmp(v[j + gap], v[j]))
					swap(v[j], v[j + gap]);
}

class Comp_count {
public:
	bool operator()(const Record& r1, const Record& r2) {
		return r1.count < r2.count;
	}
};

class Comp_price {
public:
	bool operator()(const Record& r1, const Record& r2) {
		return r1.price < r2.price;
	}
};

ostream& operator<<(ostream& os, const Record& r)
{
	return os << r.count << ' ' << r.price;
}

istream& operator>>(istream& is, Record& r)
{
	return is >> r.count >> r.price;
}

int main()
{
	vector<Record> vr;
	for (Record r; cin >> r;)
		vr.push_back(r);

	sort<Record, Comp_count>(vr);
	for (Record r : vr)
		cout << r << '\n';

	sort<Record, Comp_price>(vr);
	for (Record r : vr)
		cout << r << '\n';
}