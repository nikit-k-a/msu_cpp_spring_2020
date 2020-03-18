#include <iostream>
#include <cstring> //for memcpy
#include "Callback.h"

OnNum Number  = nullptr;
OnText Text   = nullptr;
OnPoint Start = nullptr;
OnPoint End   = nullptr;

void register_on_num_callback (OnNum callback)
{
    Number = callback;
}

void register_on_txt_callback (OnText callback)
{
    Text = callback;
}

void register_on_end_callback (OnPoint callback)
{
    End = callback;
}

void register_on_start_callback (OnPoint callback)
{
    Start = callback;
}

bool parse (const std::string & txt)
{
    if (!Start || !End || !Number || !Text)
    {
        return false;
    }
    Start ();
    for (size_t i = 0; txt [i] != '\0'; i++)
    {
        while (std::isspace (txt [i])) i++;
        size_t j = 0;
        if(std::isdigit (txt [i]))
        {
            while (std::isdigit (txt [i]))
            {
                j++;
                i++;
            }
            if ((i - j) < 0) return false;
            std::string tmp = txt.substr(i-j, j);
            Number (std::stoi(tmp));
            i--;
            continue;
        }

        if(std::isalpha (txt [i]))
        {
            while (std::isalpha (txt [i]))
            {
                j++;
                i++;
            }
            if ((i - j) < 0) return false;
            std::string tmp = txt.substr(i-j, j);
            Text (tmp);
            i--;
            continue;
        }
    }
    End ();

    return true;
}
