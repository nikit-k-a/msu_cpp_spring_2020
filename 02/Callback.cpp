#include <iostream>
#include "Callback.h"

OnToken Number = nullptr;
OnToken Text   = nullptr;
OnPoint Start  = nullptr;
OnPoint End    = nullptr;

bool isNum       (char letter);
bool isSeparator (char letter);
bool isTxt       (char letter);

void register_on_num_callback (OnToken callback)
{
    Number = callback;
}

void register_on_txt_callback (OnToken callback)
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

bool isNum (char letter)
{
    if (letter >= '0' && letter <= '9') return true;

    return false;
}

bool isSeparator (char letter)
{
    if (letter == ' '  ||
        letter == '\t' ||
        letter == '\n'   ) return true;

    return false;
}
bool isTxt (char letter)
{
    if ( (letter < '0' || letter > '9') &&
         !isSeparator(letter)           &&
         letter != '\0'                   ) return true;

    return false;
}

void parse (const char* txt)
{
    if (!Start || !End || !Number || !Text)
    {
        std::cout << "All callbacks should be initialized. Parsing stopped. \n";
        return;
    }
    Start ();
    for (int i = 0; txt [i] != '\0'; i++)
    {
        while (isSeparator (txt [i])) i++;
        int j = 0;
        char tmp [256] = {};
        while (isNum (txt [i]) || isTxt (txt[i]))
        {
            tmp [j] = txt [i];
            j++;
            i++;
        }
        tmp [j] = '\0';

        if(isNum (tmp [j-1])) Number (tmp);

        if(isTxt (tmp [j-1])) Text (tmp);
    }
    End ();
}
