#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int select(vector<int>& vals, int index) {
	sort(vals.begin(), vals.end());
	return vals[index];
}

int quick_select(vector<int>& vals, int index, int step=5) {
	if (vals.size() <= 5) return select(vals, index);

	// Find a good enough pivot
	int i = 0, j = 0;
	vector<int> medians, middle;
	while (i + j < vals.size()) {
		while (j < step && i + j < vals.size()) {
			middle.push_back(vals[i+j]);
			j++;
		}

		int even = (middle.size() % 2 == 0);
		medians.push_back(select(middle, middle.size()/2 - even));
		middle.clear();
		i = i + j;
		j = 0;
	}
	int even_m = (medians.size() % 2 == 0);
	int pivot = select(medians, medians.size()/2 - even_m);

	// Partition into subarrays
	vector<int> small, large;
	for (int el : vals) {
		if (el <= pivot) small.push_back(el);
		else large.push_back(el);
	}
	int n = small.size();

	if (index < n) return quick_select(small, index);
	else return quick_select(large, index - n);
}


int main() {
	int length;
	cin >> length;

	vector<int> values;
	int val;
	while (length--) {
		cin >> val;
		values.push_back(val);
	}

	int even = (values.size() % 2 == 0);
	cout << "The median is: " << quick_select(values, values.size()/2 - even) << endl;
}