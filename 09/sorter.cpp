#include <iostream>
#include "sorter.h"
#include <vector>
#include <algorithm>
#include <memory>
#include <queue>
//TODO: binary output + prallel
const uint64_t RAM = 8*1024*1024;
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


int make_chuncks (const std::string& in_fname)
{
    std::ifstream in (in_fname, std::ifstream::binary);
    if (!in.is_open())
    {
        throw std::runtime_error("Can't open file");
    }
    std::vector<uint64_t> buffer(BLOCK_SIZE);

    in.seekg (0, in.end);
    int length = in.tellg()/sizeof(uint64_t);
    in.seekg (0, in.beg);

    uint64_t counter = 0;
    int reading = 0;
    while (in)
    {
        int sz = length - BLOCK_SIZE*counter;
        if (sz <= 0) break;

        if (sz/BLOCK_SIZE > 0) reading = BLOCK_SIZE;
        else
        {
            reading = sz%BLOCK_SIZE;
            buffer.resize(reading);
        }

        bool status = read_block (in, reading, buffer);
        if (!status) break;

        std::sort(buffer.begin(), buffer.end());

        std::string name = FOLDER +
                           std::string("out") +
                           std::to_string(counter) +
                           std::string(".txt");

        std::ofstream out_file(name);
        for (const auto &element : buffer)
        {
            out_file << element << "\n";
        }

        ++counter;
    }
    return counter;
}

void external_sort(const int num_of_chunks)
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
        // in_files[i] = std::make_unique<std::ifstream>(FOLDER
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

        std::cout << "val = " << val << '\n';
        Ipair top (val, i);
        queue.push(top);
    }

    std::ofstream out_file("out.txt");

    while (queue.size() > 0)
    {
        int next_val = 0;

        Ipair min_pair = queue.top(); // get min
        queue.pop();

        out_file << min_pair.first << ' ';  // write value to file

        std::flush(out_file);

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
