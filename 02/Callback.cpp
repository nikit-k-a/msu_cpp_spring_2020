#include <iostream>
#include <cstring> //for memcpy
#include "Callback.h"

OnToken Number = nullptr;
OnToken Text   = nullptr;
OnPoint Start  = nullptr;
OnPoint End    = nullptr;

bool NumInit   = false;
bool TextInit  = false;
bool StartInit = false;
bool EndInit   = false;

void register_on_num_callback (OnToken callback)
{
    Number = callback;
    NumInit = true;
}

void register_on_txt_callback (OnToken callback)
{
    Text = callback;
    TextInit = true;
}

void register_on_end_callback (OnPoint callback)
{
    End = callback;
    EndInit = true;
}

void register_on_start_callback (OnPoint callback)
{
    Start = callback;
    StartInit = true;
}

bool parse (const char* txt)
{
    if (!StartInit || !EndInit || !NumInit || !TextInit)
    {
        std::cout << "All callbacks should be initialized. Parsing stopped. \n";
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
            char *tmp = (char*) malloc((j+1)*sizeof(char));
            if (tmp == nullptr) return false;
            if ((i - j) < 0) return false;
            std::memcpy( tmp, &txt[i-j], j*sizeof(char));
            tmp[j] = '\0';
            Number (tmp);
            free (tmp);
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
            char *tmp = (char*) malloc((j+1)*sizeof(char));
            if (tmp == nullptr) return false;
            if ((i - j) < 0) return false;
            std::memcpy( tmp, &txt[i-j], j*sizeof(char));
            tmp[j] = '\0';
            Text (tmp);
            free (tmp);
            i--;
            continue;
        }
    }
    End ();

    return true;
}
