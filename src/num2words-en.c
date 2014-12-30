#include "num2words-en.h"
#include "TextWatch.h"
#include "string.h"

static const char* const ONES[] = {
  "o'clock",
  "one",
  "two",
  "three",
  "four",
  "five",
  "six",
  "seven",
  "eight",
  "nine"
};

static const char* const TEENS[] ={
  "",
  "eleven",
  "twelve",
  "thirteen",
  "fourteen",
  "fifteen",
  "sixteen",
  "seventeen",
  "eightteen",
  "nineteen"
};

static const char* const TENS[] = {
//   #if INCLUDE_OH
//   "oh",
//   #else
  "",
//   #endif
  "ten",
  "twenty",
  "thirty",
  "forty",
  "fifty",
  "sixty",
  "seventy",
  "eighty",
  "ninety"
};

static size_t append_number(char* words, int num, o_setting_t o_setting) {
  // isOh is true if we should add a leading "o'" or "oh " to the numbers 1 -9
  int tens_val = num / 10 % 10;
  int ones_val = num % 10;

  size_t len = 0;

  if (tens_val > 1) { // Handle the tens part
    // 11-19 can be dealt with straight away
    if (tens_val == 1 && num != 10) {
      strcat(words, TEENS[ones_val]);
      return strlen(TEENS[ones_val]);
    }
    
    strcat(words, TENS[tens_val]);
    len += strlen(TENS[tens_val]);
    
    // if there's more to come, add the spacer
    if (ones_val > 0) {
      strcat(words, " ");
      len += 1;
    }
  } // tens part

  if (ones_val > 0 || num == 0) { // Handle the ones part
    if (tens_val == 0 && num != 0) {
      switch (o_setting) {
        case O_SETTING_LEADING_O: {
          strcat(words, "o'");
          len += 2;    
          break;
        }
        case O_SETTING_LEADING_OH: {
          strcat(words, "oh ");
          len += 3;
          break;
        }
        case O_SETTING_NONE: // fall through
        default: 
          break;
      }
    }
    strcat(words, ONES[ones_val]);
    len += strlen(ONES[ones_val]);
  }
  return len;
}

static size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}


void time_to_words(int hours, int minutes, char* words, size_t length, o_setting_t o_setting) {

  size_t remaining = length;
  memset(words, 0, length);

  if (hours == 0 || hours == 12) {
    remaining -= append_string(words, remaining, TEENS[2]);
  } else {
    remaining -= append_number(words, hours % 12, O_SETTING_NONE); // no leading O on hours
  }

  remaining -= append_string(words, remaining, " ");
  remaining -= append_number(words, minutes, o_setting);
  remaining -= append_string(words, remaining, " ");
}

void time_to_3words(int hours, int minutes, char *line1, char *line2, char *line3, size_t length, o_setting_t o_setting)
{
	char value[length];
	time_to_words(hours, minutes, value, length, o_setting);
	
	memset(line1, 0, length);
	memset(line2, 0, length);
	memset(line3, 0, length);
	
	char *start = value;
	char *pch = strstr (start, " ");
	while (pch != NULL) {
		if (line1[0] == 0) {
			memcpy(line1, start, pch-start);
		}  else if (line2[0] == 0) {
			memcpy(line2, start, pch-start);
		} else if (line3[0] == 0) {
			memcpy(line3, start, pch-start);
		}
		start += pch-start+1;
		pch = strstr(start, " ");
	}
	
	// Truncate long teen values, except thirteen
	if (strlen(line2) > 7 && minutes != 13) {
		char *pch = strstr(line2, "teen");
		if (pch) {
			memcpy(line3, pch, 4);
			pch[0] = 0;
		}
	}

//   if(minutes > 0 && minutes < 10) {
//     char new_line2[8] = "o'";
//     strcat(new_line2, line2);
//     memcpy(line2, new_line2, strlen(new_line2)+1);
//   }

}
