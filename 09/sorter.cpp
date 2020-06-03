#include <iostream>
#include "sorter.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <memory>
#include <queue>

#include <thread>
#include <mutex>

//TODO: binary output + prallel
// const uint64_t RAM = 8*1024*1024;
const uint64_t BLOCK_SIZE = 1000;
const std::string FOLDER = "tmp/";


struct Compare
{
    bool operator() (std::pair<uint64_t, int>& left,  std::pair<uint64_t, int>& right)
    {
        return left.first >= right.first;
    }
};

bool read_block(std::ifstream& file, uint64_t size, std::vector<uint64_t>& buffer);
void make_chuncks (std::ifstream& in, int& counter, std::mutex& mut, const int length);
void external_merge(const int num_of_chunks);


bool read_block(std::ifstream& file, uint64_t size, std::vector<uint64_t>& buffer)
{
    int got = 0;
    while (got < size && file)
    {
        uint64_t tmp = 0;
        if (file.read(reinterpret_cast<char*> (&tmp), sizeof(uint64_t)))
        {
            buffer[got] = tmp;
            ++got;
        }
    }
    if (file) return true;
    else
    {
        std::cout << "error: only " << file.gcount() << " could be read\n";
        return false;
    }
}


void make_chuncks (std::ifstream& in, int& counter, std::mutex& mut, const int length)
{
    std::vector<uint64_t> buffer(BLOCK_SIZE);

    uint64_t cnt = 0;
    // int a = in.tellg()/sizeof(uint64_t);
    // std::cout << "a = " << a << '\n';
    int reading = 0;
    while (in)
    {
        int sz = length - BLOCK_SIZE*cnt;
        // std::cout << "sz = " << sz <<  '\n';
        if (sz <= 0) break;

        if (sz/BLOCK_SIZE > 0) reading = BLOCK_SIZE;
        else
        {
            reading = sz%BLOCK_SIZE;
            buffer.resize(reading);
        }

        bool status = read_block (in, reading, buffer);
        std::unique_lock <std::mutex> Lock(mut);
        ++counter;

        std::string name = FOLDER +
                           std::string("out") +
                           std::to_string(counter-1) +
                           std::string(".txt");
        // std::cout << "name = " << name << (a>0) << '\n';
        Lock.unlock();
        if (!status) break;

        std::sort(buffer.begin(), buffer.end());

        std::ofstream out_file(name);
        for (const auto &element : buffer)
        {
            out_file << element << "\n";
        }
        cnt++;
    }
}

void external_merge(const int num_of_chunks)
{

    using Ipair = std::pair <uint64_t, int>;
    std::priority_queue<Ipair, std::vector<Ipair>, Compare> queue;

    if (num_of_chunks <= 0)
    {
        throw std::runtime_error("Invalid chunks number");
    }

    std::ifstream* in_files = new std::ifstream[num_of_chunks];

    for (size_t i = 0; i < num_of_chunks; ++i)
    {
        std::string in_fname (FOLDER +
                          std::string("out") +
                          std::to_string(i) +
                          std::string(".txt"));
        in_files[i].open(in_fname);
        if (!in_files[i])
        {
            throw std::runtime_error("couldn't open file");
        }
        uint64_t val = 0;
        in_files[i] >> val;

        // std::cout << "val = " << val << '\n';
        Ipair top (val, i);
        queue.push(top);
    }

    std::ofstream out_file("out.bin", std::ios::out  | std::ios::binary);

    if (!out_file.is_open())
    {
        throw std::runtime_error("Can't open file");
    }

    while (queue.size() > 0)
    {
        int next_val = 0;

        Ipair min_pair = queue.top(); // get min
        queue.pop();

        out_file.write(reinterpret_cast<char*>(&min_pair.first), sizeof(min_pair.first));

        if (in_files[min_pair.second] >> next_val)
	    {
            Ipair np(next_val, min_pair.second );
	        queue.push(np);
	    }
    }

    for (size_t i = 0; i < num_of_chunks; ++i)
    {
        std::string name = FOLDER +
                           std::string("out") +
                           std::to_string(i) +
                           std::string(".txt");
         std::remove(name.c_str());
    }

    delete [] in_files;
}

void parallel_sort (const std::string& f_name)
{
    std::mutex mut;
    int num_chunks = 0;


    std::ifstream in (f_name, std::ios::in | std::ios::binary);
    if (!in.is_open())
    {
        throw std::runtime_error("Can't open file");
    }

    in.seekg (0, in.end);
    int length = in.tellg()/sizeof(uint64_t);
    in.seekg (0, in.beg);

    int half = length/2;

    std::ifstream in2 (f_name, std::ios::in | std::ios::binary);
    if (!in2.is_open())
    {
        throw std::runtime_error("Can't open file");
    }
    in2.seekg(half*sizeof(uint64_t), std::ios::beg);


    std::thread t1(make_chuncks, std::ref(in),
                                 std::ref(num_chunks),
                                 std::ref(mut),
                                 half);

    std::thread t2(make_chuncks, std::ref(in2),
                                 std::ref(num_chunks),
                                 std::ref(mut),
                                 length - half);
    t1.join();
    t2.join();

    // std::cout << "chunks = " << num_chunks<< '\n';


	external_merge(num_chunks);
}
