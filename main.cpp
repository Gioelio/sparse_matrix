//
// Created by gioele fiorenza on 29/12/21.
//
#include "sparse_matrix.h"

void test_fondamentali(){

    std::cout << "--- TEST FONDAMENTALI ---" << std::endl;

    std::cout << "test ctor default" << std::endl;
    sparse_matrix<int> def;
    assert(def.size() == 0);

    std::cout << "test ctor secondario" << std::endl;
    sparse_matrix<int> sec(10);
    assert(sec.size() == 0);
    int valore = sec.default_value();
    valore++;
    assert(sec.default_value() == 10);    //test modifica valore ritornato per reference

    std::cout << "test copy ctor" << std::endl;
    sparse_matrix<int> copy(sec);
    assert(sec.size() == copy.size());
    assert(sec.default_value() == copy.default_value());
    copy.set(0,0, 10);
    assert(sec.size() + 1 == copy.size()); //test per fare in modo che i 2 oggetti siano scollegati

    std::cout << "test assegnamento" << std::endl;
    def = copy;
    def.print_test();
    copy.print_test();
    assert(def.size() == copy.size());
    assert(def.default_value() == copy.default_value());
}

void test_sparse_matrix() {

    std::cout << "--- TEST METODI sparse_matrix ---" << std::endl;

    std::cout << "test set value" << std::endl;
    sparse_matrix<int> set(-1);
    assert(set.size() == 0);
    set.set(1, 1, 30);
    assert(set.size() == 1);
    set.set(2, 10, 50);
    assert(set.size() == 2);
    set.set(4, 4, -1); //inserimento del valore di default
    assert(set.size() == 3);

    std::cout << "test get value" << std::endl;
    assert(set(1, 1) == 30);
    assert(set(2, 10) == 50);
    assert(set(2, 4) == -1); //valore di default

    std::cout << "test column number" << std::endl;
    assert(set.columns() == 10);

    std::cout << "test rows number" << std::endl;
    assert(set.rows() == 4);

}


int main() {
    test_fondamentali();
    test_sparse_matrix();

    sparse_matrix<int> a(-3);

    a.set(10, 10, 50);



    return 0;
}