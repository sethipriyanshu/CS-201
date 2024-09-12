#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

template< class RandomIt >
constexpr void insertionsort ( RandomIt first, RandomIt last ) {
    for (auto i = first; i != last; ++i) {
        for (auto j = i; j != first && *j < *(j-1); --j) {
            swap(*j, *(j-1));
        }
    }
}
template< class RandomIt >
constexpr void mergesort ( RandomIt first, RandomIt last, RandomIt tempstart ){
    if (last - first < 2){
        return;
    } 
    auto mid = first + (last - first) / 2;
    mergesort(first, mid, tempstart);
    mergesort(mid, last, tempstart);
    auto i = first, j = mid, k = tempstart;
    while (i < mid && j < last) {
        if (*i < *j) {
            *k = *i;
            ++i;
        } else {
            *k = *j;
            ++j;
        }
        ++k;
    }
    while (i < mid) {
        *k = *i;
        ++i;
        ++k;
    }
    while (j < last) {
        *k = *j;
        ++j;
        ++k;
    }
    for (auto i = first; i != last; ++i) {
        *i = *tempstart;
        ++tempstart;
    }
}

template< class RandomIt >
void print(RandomIt start, RandomIt end) {
	while (start != end) {
		std::cout << *start << " ";
		++start;
	}
	std::cout << std::endl;
}

int main(int argc, char *argv[]) {
	int a0[] = {56, 23, 11, 64, 43};
	std::array<int, 5> a1 = {5, 4, 3, 2, 1};
	std::array<std::string, 5> a2 = {"lion", "dog", "cat", "fox", "pig"};
	std::vector<double> v = {4.2, 3.1, 5.6, 2.8, 1.9};

	std::sort(a0, a0+5);
	print(a0, a0+5);

	std::sort(&a0[0], &a0[5]);
	print(&a0[0], &a0[5]);

	std::sort(a1.begin(), a1.end());
	print(a1.begin(), a1.end());

	std::sort(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	std::reverse(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	std::sort(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

	std::sort(v.begin(), v.end());
	print(v.begin(), v.end());

	return 0;
}
