#include "Summator.h"
#include <thread>
#include <vector>
#include <condition_variable>
#include <queue>
#include <sstream>
#include <fstream>

int res = 0;
bool end = false;
std::mutex mut;
std::condition_variable cond;
std::queue<std::string> lines_q;

void sum_line();
void read_by_line(const std::string& f_name);

int summator(const std::string& f_name)
{
	std::thread read_thread(read_by_line, f_name);
	std::thread sum0(sum_line);
	std::thread sum1(sum_line);

	read_thread.join();
	sum0.join();
	sum1.join();

	return res;
}

void read_by_line(const std::string& f_name)
{
	std::ifstream in(f_name);
	if(!in.is_open())
	{
		throw std::runtime_error("Can't open file");
	}

	std::string line;
	while (std::getline(in, line))
	{
		std::unique_lock<std::mutex> lock(mut);
		lines_q.push(line);
		cond.notify_one();
	}

	std::unique_lock<std::mutex> lock_stop(mut);
	end = true;
	cond.notify_all();
}

void sum_line()
{
	std::string line;
	while (true)
	{
		std::unique_lock<std::mutex> lock(mut);
		cond.wait(lock, []() { return (!lines_q.empty() || end); });

		if (end && lines_q.empty()) break;

		line = lines_q.front();
		lines_q.pop();
		lock.unlock();

		std::istringstream s_str(line);
		int sum_local = 0;
		int num = 0;
		while (s_str >> num)
		{
			sum_local += num;
		}

		lock.lock();
		res += sum_local;
		lock.unlock();
	}
}
