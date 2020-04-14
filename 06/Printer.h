#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <stdexcept>
#include <sstream>

std::string format (const std::string& str)
{
    return str;
}

template <typename T>
void insert (std::string& str, T&& val)
{
    std::ostringstream buff;
    buff << val;
    str += buff.str();
}

template <typename T>
void process (std::string& str, int num, int count, T&& val)
{
    if (num == count)
    {
        insert (str, val);
        return;
    }
    if (num > count)
    {
        throw std::runtime_error ("Parameter > qty of parameters");
    }
}

template <typename T, typename... Args>
void process (std::string& str, int num, int count, T&& val, Args&&... args)
{
    if (num == count)
    {
        insert (str, val);
        return;
    }
    count++;
    process (str, num, count, std::forward<Args>(args)...);
}

template <typename... Args>
std::string format (const std::string& data, Args&&... args)
{
    std::string out;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] == '{')
        {
            if (std::isdigit(data [i+1]) && data [i+2] == '}')
            {
                int num = data [i+1] - '0';
                process (out, num, 0, args...);
                i+=2;
            }
            else
            {
                throw std::runtime_error ("Invalid syntax");
            }
        }

        else
        {
            out += data [i];
        }
    }
    return out;
}

#endif //PRINTER_H
