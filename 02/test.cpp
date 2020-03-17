#include <iostream>
#include "Callback.h"

void onNumberFound (const char* num);
void onTextFound   (const char* txt);
void onStartFound ();
void onEndFound   ();

void onNumberFound (const char* num)
{
	std::cout << num << "\n";
}

void onTextFound (const char* txt)
{
    std::cout << txt << "\n";
}

void onStartFound ()
{
    std::cout << "Start \n";
}

void onEndFound ()
{
    std::cout << "End \n";
}

int main ()
{
    register_on_num_callback   (onNumberFound);
    register_on_txt_callback   (onTextFound);
    register_on_end_callback   (onEndFound);
    register_on_start_callback (onStartFound);

    std::cout << "-------start-of-tests---------" << '\n';
    parse ("a \n b \t c");

    std::cout << "------------------------------" << '\n';
    parse ("");

    std::cout << "------------------------------" << '\n';
    parse ("1 243   23 13 js apkoerng");

    std::cout << "------------------------------" << '\n';
    parse ("asdadasda");

    std::cout << "------------------------------" << '\n';
    parse ("123 abc 4567");
    std::cout << "---------end-of-tests---------" << '\n';

    return 0;
}
