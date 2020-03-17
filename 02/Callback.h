#ifndef CALLBACK_H
#define CALLBACK_H

using OnToken = void (*)(const char* num);
using OnPoint = void (*)();

void register_on_num_callback   (OnToken callback);
void register_on_txt_callback   (OnToken callback);
void register_on_start_callback (OnPoint callback);
void register_on_end_callback   (OnPoint callback);

void parse (const char* txt);

#endif //CALLBACK_H
