//
// Created by gioele fiorenza on 29/12/21.
//
#include "sparse_matrix.h"

struct predicate{
    bool operator() (int value){
        return value < 5;
    }
};

template<typename T, typename F>
int evaluate (const sparse_matrix<T> &mat, F pred) {
    unsigned int cont = 0;
    for(typename sparse_matrix<T>::const_iterator iter = mat.begin(); iter != mat.end(); ++iter) {
        std::cout << iter->value << pred(iter->value) << std::endl;
        if (pred(iter->value))
            cont++;
    }

    return cont;
}

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

    sparse_matrix<int> dim(-5, 4, 6);

    std::cout << "test column number" << std::endl;
    assert(set.columns() == 100);
    assert(dim.columns() == 4);

    std::cout << "test rows number" << std::endl;
    assert(set.rows() == 100);
    assert(dim.rows() == 6);

}

void test_const_sparse_matrix(const sparse_matrix<int> const_mat) {

    //i metodi di scrittura dovrebbero dare errore
    //const_mat.set(1, 2, 10);


    //i metodi di lettura devono funzionare
    assert(const_mat(1, 1) == 10);
    assert(const_mat(2, 2) == -1);
    assert(const_mat.columns() == 100);
    assert(const_mat.rows() == 10);
    assert(const_mat.default_value() == -1);
    assert(const_mat.size() == 1);
}

void test_const(){
    sparse_matrix<int> const_mat(-1, 100, 10);

    const_mat.set(1,1, 10);

    test_const_sparse_matrix(const_mat);
}

void test_sparse_matrix_iterator() {
    std::cout << "--- TEST sparse matrix iterator ---" << std::endl;
    sparse_matrix<int> mat_iter(10, 20, 20);
    mat_iter.set(1,1, 20);
    mat_iter.set(1, 2, 30);
    mat_iter.set(2, 1, 50);
    mat_iter.set(1,4, 100);

    sparse_matrix<int>::const_iterator iter = mat_iter.begin();
    //todo: aggiungere i test di pre e post incremento
}

void test_specific_class(){

}

void test_evaluate(){
    std::cout << "-- TEST evaluate predicate --" << std::endl;
    sparse_matrix<int> mat(-1, 20, 20);

    //mat.set(1,1, -1);
    mat.set(2, 2, 6);
    mat.set(1, 1, -2);
    mat.set(3, 3, -1);

    predicate p;

    assert(evaluate(mat, p) == 2);

}

void execute_tests(){
    test_fondamentali();
    test_sparse_matrix();
    test_sparse_matrix_iterator();
    test_const();
    test_evaluate();
}

int main() {
    execute_tests();

    return 0;
}