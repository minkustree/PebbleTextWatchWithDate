#pragma once
#include "TextWatch.h"
#include "string.h"

void time_to_words(int hours, int minutes, char* words, size_t length, o_setting_t o_setting);
void time_to_3words(int hours, int minutes, char *line1, char *line2, char *line3, size_t length, o_setting_t o_setting);
