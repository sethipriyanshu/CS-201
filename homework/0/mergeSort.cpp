#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

template< class RandomIt >
void print(RandomIt start, RandomIt end) {
    while (start != end) {
        std::cout << *start << " ";
        ++start;
    }
    std::cout << std::endl;
}

template< class RandomIt >
constexpr void mergesort( RandomIt first, RandomIt last, RandomIt tempstart ){
    if (last -first< 2){
        return;
    } 
    auto mid= first + (last - first) / 2;
    mergesort(first, mid, tempstart);
    mergesort(mid, last, tempstart);
    auto i = first, j= mid, k= tempstart;
    while(i < mid && j < last) {
        if(*i < *j) {
            *k = *i;
          ++i;
        }else {
         *k = *j;
         ++j;
        }
        ++k;
    }
    while(i< mid) {
         *k = *i;
        ++i;
        ++k;
    }
    while(j< last) {
        *k = *j;
        ++j;
        ++k;
    }
    for (auto i = first, tmp = tempstart; i != last; ++i, ++tmp) {
        *i = *tmp;
    }
}

int main() {
    int a0[] = {56, 23, 11, 64, 43};
    std::array<int, 5> a1 = {5, 4, 3, 2, 1};
    std::array<std::string, 5> a2 = {"lion", "dog", "cat", "fox", "pig"};
    std::vector<double> v = {4.2, 3.1, 5.6, 2.8, 1.9};
    int temp_a0[5];
    array<int,5> temp_a1;
    array<string,5> temp_a2;
    vector<double> temp_v(v.size());

    mergesort(a0, a0+5, temp_a0);
    print(a0, a0+5);

    mergesort(&a0[0], &a0[5],temp_a0);
	print(&a0[0], &a0[5]);

    mergesort(a1.begin(), a1.end(), temp_a1.begin());
    print(a1.begin(), a1.end());

    mergesort(a2.begin(), a2.end(), temp_a2.begin());
    print(a2.begin(), a2.end());

    std::reverse(a2.begin(), a2.end());
	print(a2.begin(), a2.end());

    mergesort(a2.begin(), a2.end(), temp_a2.begin());
	print(a2.begin(), a2.end());

    mergesort(v.begin(), v.end(), temp_v.begin());
    print(v.begin(), v.end());

    return 0;
}
