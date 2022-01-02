//
// Created by gioele fiorenza on 02/01/22.
//

#ifndef SPARSE_MATRIX_MYEXCEPTION_H
#define SPARSE_MATRIX_MYEXCEPTION_H

#include <stdexcept>

class my_out_of_range: public std::range_error {
public:
    my_out_of_range(const std::string &msg);
};


#endif //SPARSE_MATRIX_MYEXCEPTION_H
