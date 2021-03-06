#include <iostream>
#include "Callback.h"

void onNumberFound (int num);
void onTextFound   (const std::string & txt);
void onStartFound  ();
void onEndFound    ();

void onNumberFound (int num)
{
	std::cout << num << "\n";
}

void onTextFound (const std::string & txt)
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
    bool state = parse ("a \n b \t c");
	if (!state) std::cout << "parse error" << '\n';

    std::cout << "------------------------------" << '\n';
    state = parse ("");
	if (!state) std::cout << "parse error" << '\n';

    std::cout << "------------------------------" << '\n';
    state = parse ("1 243   23 13js apkoerng");
	if (!state) std::cout << "parse error" << '\n';

    std::cout << "------------------------------" << '\n';
    state = parse ("asdadasda");
	if (!state) std::cout << "parse error" << '\n';

    std::cout << "------------------------------" << '\n';
    state = parse ("123 abc 4567");
	if (!state) std::cout << "parse error" << '\n';

    std::cout << "---------end-of-tests---------" << '\n';

    return 0;
}
