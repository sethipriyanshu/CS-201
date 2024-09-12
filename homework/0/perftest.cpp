#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <chrono>
using namespace std;



template< class RandomIt >
constexpr void insertionsort( RandomIt first, RandomIt last ) {
    for (auto i= first; i!= last; ++i) {
        for (auto j= i; j != first && *j <*(j-1); --j) {
            swap(*j, *(j-1));
        }
    }
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

int main(int argc, char *argv[]) {

	std::cout << "Problem Size\tTime Taken (seconds)" << std::endl;
	for (int size = 10; size <= 100000000; size *= 10) {
		 int *a = new int[size];
        int *temp_a = new int[size];
	
		std::generate(a, a+size, std::rand);
		auto starttime = std::chrono::steady_clock::now();
		mergesort(a, a+size,temp_a);
		auto endtime = std::chrono::steady_clock::now();
		std::chrono::duration<double> timetaken = endtime - starttime;
		std::cout << size << "\t" << timetaken.count() << std::endl;
        delete[] temp_a;
		delete[] a;
	}

	return 0;
}
