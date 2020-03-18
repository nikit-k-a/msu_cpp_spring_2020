#ifndef CALLBACK_H
#define CALLBACK_H

using OnText  = void (*)(const std::string & token);
using OnNum   = void (*)(int token);
using OnPoint = void (*)();

void register_on_num_callback   (OnNum   callback);
void register_on_txt_callback   (OnText  callback);
void register_on_start_callback (OnPoint callback);
void register_on_end_callback   (OnPoint callback);

bool parse (const std::string & txt);

#endif //CALLBACK_H
