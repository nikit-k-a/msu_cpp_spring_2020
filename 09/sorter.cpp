#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <mutex>
#include <condition_variable>
#include <thread>
#include<exception>
#include <iostream>

const size_t max_size = 1000;
std::mutex mut;
std::condition_variable cond;
int iter = 0;

void split(std::ifstream& in, size_t size, std::ofstream& out1, std::ofstream& out2, size_t& i)
{
    uint64_t tmp_val;

    while (in.peek() != EOF || i < size)
    {
        std::unique_lock<std::mutex> lock(mut);

        in.seekg(i*sizeof(uint64_t));

        in.read(reinterpret_cast<char*> (&tmp_val), sizeof(uint64_t));

        if (i < max_size)
        {
            out1.write(reinterpret_cast<char*> (&tmp_val), sizeof(uint64_t));
        }
        else
        {
            out2.write(reinterpret_cast<char*> (&tmp_val), sizeof(uint64_t));
        }
        i++;
    }
}

void sort (std::string& input_name, size_t size, std::string& output_name)
{
    std::ifstream in(input_name, std::ios::binary | std::ios::in);
    if(!in)
    {
        throw std::runtime_error("Can't open in file");
    }
    std::vector<uint64_t> buff(size);

    for(int i = 0; i < size; i++)
    {
        in.seekg(i*sizeof(uint64_t));
        in.read(reinterpret_cast<char*> (&buff[i]), sizeof(uint64_t));
    }

    in.close();

    std::sort(buff.begin(), buff.end());

    std::ofstream out(output_name, std::ios::binary | std::ios::out);
    if(!out)
    {
        throw std::runtime_error("Can't open out file");
    }

    for(int i = 0; i < size; i++)
    {
        out.write(reinterpret_cast<char*> (&buff[i]), sizeof(uint64_t));
    }

    out.close();
}

void merge_files(std::ifstream& in, std::ofstream& out, std::uint64_t& barrier)
{
    uint64_t tmp_val;

    while(true)
    {
        std::unique_lock<std::mutex> lock(mut);

        if(in.peek() == EOF)
        {
            if(barrier != -1)
            {
                out.write(reinterpret_cast<char*> (&barrier), sizeof(uint64_t));
                barrier = -1;
            }
            cond.notify_one();
            break;
        }
        in.read(reinterpret_cast<char*> (&tmp_val), sizeof(uint64_t));

        if(tmp_val == barrier) continue;

        if(barrier == -1)
        {
            out.write(reinterpret_cast<char*> (&tmp_val), sizeof(uint64_t));
            continue;
        }

        if(tmp_val < barrier) out.write(reinterpret_cast<char*> (&tmp_val), sizeof(uint64_t));
        else
        {
            out.write(reinterpret_cast<char*> (&barrier), sizeof(uint64_t));
            barrier = tmp_val;
            cond.notify_one();
            if(barrier == tmp_val) cond.wait(lock);
        }
    }
}

void merge_sort(std::string& filename)
{
    std::cout << iter;
    size_t size = 0;
    uint64_t barrier;

    std::string output_name = filename;

    if(iter == 0) output_name = "output.bin";
    iter++;

    uint64_t tmp_val = 0;

    std::ifstream in(filename, std::ios::binary | std::ios::in);

    while(in.read(reinterpret_cast<char*> (&tmp_val), sizeof(uint64_t)))
    {
        size++;
    }

    if (size <= max_size)
    {
        sort(filename, size, output_name);
    }

    else
    {
        std::string fn1 = std::to_string(iter) + "1.bin";
        std::string fn2 = std::to_string(iter) + "2.bin";

        std::ifstream in(filename, std::ios::binary | std::ios::in);
        std::ofstream out1(fn1, std::ios::binary | std::ios::out);
        std::ofstream out2(fn2, std::ios::binary | std::ios::out);
        if(!(in && out1 && out2))
        {
            throw std::runtime_error("Error opening files");
        }

        size_t pos = 0;
        std::thread thread1(split, std::ref(in), size, std::ref(out1), std::ref(out2), std::ref(pos));
        std::thread thread2(split, std::ref(in), size, std::ref(out1), std::ref(out2), std::ref(pos));

        thread1.join();
        thread2.join();
        in.close();
        out1.close();
        out2.close();

        merge_sort(std::ref(fn1));
        merge_sort(std::ref(fn2));

        std::ifstream in1(fn1, std::ios::binary | std::ios::in);
        std::ifstream in2(fn2, std::ios::binary | std::ios::in);
        std::ofstream out(output_name, std::ios::binary | std::ios::out);
        if(!(in1 && in2 && out))
        {
            throw std::runtime_error("Error opening files");
        }

        in2.read(reinterpret_cast<char*> (&barrier), sizeof(uint64_t));
        std::thread merge1(merge_files, std::ref(in1), std::ref(out), std::ref(barrier));
        std::thread merge2(merge_files, std::ref(in2), std::ref(out), std::ref(barrier));

        merge1.join();
        merge2.join();
        in1.close();
        in2.close();
        out.close();

        const char* file1 = fn1.c_str();
        const char* file2 = fn2.c_str();
        std::remove(file1);
        std::remove(file2);
    }
}
