#ifndef PRINTER_H
#define PRINTER_H

#include <string>
#include <stdexcept>
#include <sstream>
#include <vector>
#include <algorithm>


template <typename T>
void process (std::vector <std::string>& str, T&& val)
{
    std::ostringstream os;
    os << val;

    str.push_back (os.str());
}

template <typename T, typename... Args>
void process (std::vector <std::string>& str, T&& val, Args&&... args)
{
    std::ostringstream os;
    os << val;

    str.push_back (os.str());

    process (str, std::forward<Args>(args)...);
}

template <typename... Args>
std::string format (const std::string& data, Args&&... args)
{
    std::vector <std::string> param;
    process (param, args...);

    int qty = param.size();
    std::string out;
    for (int i = 0; i < data.size(); i++)
    {
        if (data[i] == '{')
        {
            i++;
            std::string index = "";
            while(data[i] != '}')
            {
                index += data[i];
                i++;
            }
            if (index.empty()|| !std::all_of (index.begin (), index.end (), ::isdigit))
                {
                    throw std::runtime_error ("Invalid syntax");
                }

            int number = std::stoi (index);
            if (number >= qty) throw std::runtime_error ("Invalid parameters number");
            out += param [number];
            }

        else if (data [i] == '}')
        {
            throw std::runtime_error ("Invalid syntax2");
        }

        else
        {
            out += data [i];
        }
    }
    return out;
}

#endif //PRINTER_H
