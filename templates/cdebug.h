// START OF DEBUGGING MACROS

#ifndef C_DEBUG_LOCAL
#define C_DEBUG_LOCAL 1

#define MAGENTA "\033[35m"
#define GREEN   "\033[32m"
#define RESET   "\033[0m"

#define get_format_specifier(x) \
  _Generic((x), \
  char: "%c", \
  signed char: "%hhd", \
  unsigned char: "%hhu", \
  signed short: "%hd", \
  unsigned short: "%hu", \
  signed int: "%d", \
  unsigned int: "%u", \
  long int: "%ld", \
  unsigned long int: "%lu", \
  long long int: "%lld", \
  unsigned long long int: "%llu", \
  float: "%f", \
  double: "%f", \
  long double: "%Lf", \
  char *: "%s", \
  void *: "%p")

#define dbg(x) { \
  printf(MAGENTA); \
  printf("%d ", __LINE__); \
  printf(#x); \
  printf(": "); \
  printf(GREEN); \
  printf(get_format_specifier(x), x); \
  printf("\n"); \
  printf(RESET); \
  fflush(stdout); }

#define dba1(arr, n) { \
  printf(MAGENTA); \
  printf("%d ", __LINE__); \
  printf(#arr); \
  printf(": "); \
  printf(GREEN); \
  printf("{"); \
  for (int _x = 0; _x < (n); _x++) { \
    printf(get_format_specifier(arr[_x]), arr[_x]); \
    if (_x < (n) - 1) { \
      printf(", "); \
    } \
  } \
  printf("}\n"); \
  printf(RESET); \
  fflush(stdout); }

#define dba2(arr, n1, n2) { \
  printf(MAGENTA); \
  printf("%d ", __LINE__); \
  printf(#arr); \
  printf(": "); \
  printf(GREEN); \
  printf("{\n"); \
  for (int _d = 0; _d < (n1); _d++) { \
    printf("{"); \
    for (int _x = 0; _x < (n2); _x++) { \
      printf(get_format_specifier(arr[_d][_x]), arr[_d][_x]); \
      if (_x < (n2) - 1) { \
        printf(", "); \
      } \
    } \
    printf("}"); \
    if (_d < (n1) - 1) { \
      printf(","); \
    } \
    printf("\n"); \
  } \
  printf("}\n"); \
  printf(RESET); \
  fflush(stdout); }
  
#endif  // C_DEBUG_LOCAL

// END OF DEBUGGING MACROS