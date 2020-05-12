
#ifndef SORTER_H
#define SORTER_H
#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <mutex>
#include <condition_variable>
#include <thread>
#include<exception>


void merge_sort (std::string& filename);
void split (std::ifstream& in, size_t size, std::ofstream& out1, std::ofstream& out2, size_t& i);
void sort (std::string& input_name, size_t size, std::string& output_name);

void merge_files(std::ifstream& in, std::ofstream& out, std::uint64_t& bar);
#endif //SORTER_H
