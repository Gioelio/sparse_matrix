#include "myexception.h"

my_out_of_range::my_out_of_range(const std::string &msg): std::runtime_error(msg) {}
