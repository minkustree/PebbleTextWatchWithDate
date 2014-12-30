#pragma once

// Optional leading "o'" or "oh " for minutes 1-9
typedef enum {
  O_SETTING_NONE,       // No leading text for minutes 1-9, e.g. "eleven nine"
  O_SETTING_LEADING_O,  // Minutes 1-9 prefixed with "o'", e.g. "eleven o'nine"
  O_SETTING_LEADING_OH, // Minutes 1-9 prefixed with "oh ", e.g. "eleven oh nine"
} o_setting_t;



