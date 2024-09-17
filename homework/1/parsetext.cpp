/*
 Name: Priyanshu Sethi
 Email: psethi@crimson.ua.edu
 Course Section: Fall 2024 CS 201
 Homework #: 1
 To Compile: g++ -o parsetext parsetext.cpp  
 To Run: .\parsetext <inputfile.txt>
*/


#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <unordered_map>
#include <algorithm>
#include <chrono> 
using namespace std;


// custom comparator for when frequencies are equal 
bool compare(const pair<string, int>& val1, const pair<string, int>& val2) {
    if (val1.second != val2.second)
        return val1.second > val2.second; 
    return val1.first < val2.first;
}

// function to merge after sorting
void merge(vector<pair<string, int>>& vec, int left, int med, int right) {
    int n1 = med - left + 1;
    int n2 = right - med;

    vector<pair<string, int>> L(n1);
    vector<pair<string, int>> R(n2);



    for (int i = 0; i <n1; i++)
        L[i] = vec[left + i];
    for (int i = 0; i <n2; i++)
        R[i] = vec[med + 1 + i];



    int i= 0;
    int j = 0;
    int k = left;


    while (i < n1 && j < n2) {
        if (compare(L[i], R[j])) {
            vec[k] = L[i];
            i++;
        } else {
            vec[k] = R[j];
            j++;
        }
        k++;
   }


    while (i < n1) {
        vec[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        vec[k] = R[j];
        j++;
        k++;
    }
}

// recursive merge sort function
void mergeSort(vector<pair<string, int>>& res, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(res, left, mid);
        mergeSort(res, mid + 1, right);

        merge(res, left, mid, right);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    auto timestart = chrono::high_resolution_clock::now();

    string text((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
    unordered_map<string, int> wordCount;
    const regex delim("\\s+");

    auto begin = sregex_token_iterator(text.begin(), text.end(), delim, -1);
    auto end = sregex_token_iterator();
    for (sregex_token_iterator word = begin; word != end; word++) {
        string token = *word;
        wordCount[token]++;
    }

    vector<pair<string, int>> wordcount(wordCount.begin(), wordCount.end());

    mergeSort(wordcount, 0, wordcount.size() - 1);
    for (const auto& pair : wordcount) {
        cout << pair.first << ": " << pair.second << endl;
    }
    auto timeend = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = timeend - timestart;
    cout << "running time: " << elapsed.count() << " seconds" << endl;
    cout << "word count: "<< wordcount.size()<< " word" <<endl;
    return 0;
}