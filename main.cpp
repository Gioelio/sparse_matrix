#include "SparseMatrix.h" //SparseMatrix
#include <assert.h> //assert
#include <iostream> //cout
#include "test_class.h" //test_class

struct predicate{
    bool operator() (int value){
        return value < 5;
    }
};

struct predicate_test_class {
    bool operator() (test_class test) {
        return test.get_value() > 5 && test.get_value_ptr() < 5;
    }
};

/**
 * @brief Funzione di valutazione
 *
 * Esegue il predicato F per ogni elemento T contenuto all'interno della matrice
 *
 * @tparam T tipo di dato contenuto all'interno della matrice mat
 * @tparam F tipo di dato del predicato che esegue il confronto
 * @param mat matrice su cui eseguire il confronto
 * @param pred predicato che effettivamente esegue il controllo sull'elemento
 * @return numero di elementi della matrice che soddisfano il predicato
 */
template<typename T, typename F>
int evaluate (const SparseMatrix<T> &mat, F pred) {
    unsigned int cont = 0;
    for(typename SparseMatrix<T>::const_iterator iter = mat.begin(); iter != mat.end(); ++iter) {
        if (pred(iter->value))
            cont++;
    }

    if(pred(mat.default_value()))
        cont += (mat.columns() * mat.rows()) - mat.size();

    return cont;
}


void test_fondamentali(){

    std::cout << "--- TEST FONDAMENTALI ---" << std::endl;

    std::cout << "test ctor default" << std::endl;
    SparseMatrix<int> def;
    assert(def.size() == 0);

    std::cout << "test ctor secondario" << std::endl;
    SparseMatrix<int> sec(10, 100, 100);
    assert(sec.size() == 0);
    int valore = sec.default_value();
    valore++;
    assert(sec.default_value() == 10);    //test modifica valore ritornato per reference

    std::cout << "test copy ctor" << std::endl;
    SparseMatrix<int> copy(sec);
    assert(sec.size() == copy.size());
    assert(sec.default_value() == copy.default_value());
    copy.set(0,0, 10);
    assert(sec.size() + 1 == copy.size()); //test per fare in modo che i 2 oggetti siano scollegati

    std::cout << "test assegnamento" << std::endl;
    copy.set(1, 1, 30);
    def = copy;
    assert(def.size() == copy.size());
    assert(def.default_value() == copy.default_value());
    assert(&def(1, 1) != &copy(1, 1)); //controllo che le aree di memoria siano diverse
}

void test_sparse_matrix() {

    std::cout << "--- TEST METODI SparseMatrix ---" << std::endl;

    std::cout << "test set value" << std::endl;
    SparseMatrix<int> set(-1, 100, 100);
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

    SparseMatrix<int> dim(-5, 4, 6);

    std::cout << "test column number" << std::endl;
    assert(set.columns() == 100);
    assert(dim.columns() == 6);

    std::cout << "test rows number" << std::endl;
    assert(set.rows() == 100);
    assert(dim.rows() == 4);

}

void test_const_sparse_matrix(const SparseMatrix<int> const_mat) {

    //i metodi di scrittura dovrebbero dare errore
    //const_mat.set(1, 2, 10);


    //i metodi di lettura devono funzionare
    assert(const_mat(1, 1) == 10);
    assert(const_mat(2, 2) == -1);
    assert(const_mat.columns() == 10);
    assert(const_mat.rows() == 100);
    assert(const_mat.default_value() == -1);
    assert(const_mat.size() == 1);
}

void test_const(){
    SparseMatrix<int> const_mat(-1, 100, 10);

    const_mat.set(1,1, 10);

    test_const_sparse_matrix(const_mat);
}

void test_sparse_matrix_iterator() {
    std::cout << "--- TEST sparse matrix iterator ---" << std::endl;

    SparseMatrix<int> mat_iter(10, 20, 20);

    std::cout << "test add values" << std::endl;

    mat_iter.set(1,1, 20);
    mat_iter.set(1, 2, 30);
    mat_iter.set(2, 1, 50);
    mat_iter.set(1,4, 100);

    std::cout << "test get iterator begin" << std::endl;

    SparseMatrix<int>::const_iterator iter = mat_iter.begin();

    std::cout << "test getting value from iterator" << std::endl;

    assert(iter->value == 20);
    assert(iter->x == 1);
    assert(iter->y == 1);

    std::cout << "test post increment" << std::endl;

    SparseMatrix<int>::const_iterator iter_2 = iter++;

    assert(iter_2->value == 20);
    assert(iter->value == 30);

    std::cout << "test pre increment" << std::endl;

    SparseMatrix<int>::const_iterator iter_pre = ++iter;
    assert(iter->value == iter_pre->value);
    assert(iter->value == 50);

    std::cout << "test operator=" << std::endl;
    assert(iter == iter_pre);

    std::cout << "test deferencing" << std::endl;
    SparseMatrix<int>::element a = *iter;
    assert(a.value == 50);

}

void test_custom_class(){
    std::cout << "--- TEST custom class ---" << std::endl;

    test_class a(100);
    test_class b(a);

    std::cout << "test ctor default value" << std::endl;
    SparseMatrix<test_class> mat(a, 20, 100);

    std::cout << "test set value" << std::endl;
    mat.set(18, 10, test_class(100));
    mat.set(19, 25, test_class(10));

    std::cout << "test size value" << std::endl;
    assert(mat.size() == 2);

    std::cout << "test get default value" << std::endl;
    assert(mat(19, 50) == mat(12, 10));

}

void test_evaluate(){
    std::cout << "--- TEST evaluate predicate ---" << std::endl;
    SparseMatrix<int> mat(-1, 2, 2);

    //mat.set(1,1, -1);
    mat.set(1, 0, 6);
    mat.set(0, 0, -2);
    mat.set(0, 1, -1);

    //valori minori di 5
    predicate p;

    std::cout << "test value returned from evaluate" << std::endl;
    assert(evaluate(mat, p) == 3);

    mat.set(1, 1, 10);
    assert(evaluate(mat, p) == 2);

    std::cout << "test evaluate on custom class" << std::endl;

    SparseMatrix<test_class> a(test_class(10, 20), 10, 10);
    SparseMatrix<test_class> b(test_class(6 , 4), 10, 2);

    a.set(1,1, test_class(10, 2));
    predicate_test_class pred;

    assert(evaluate(a, pred) == 1);
    assert(evaluate(b, pred) == 20);

}

void execute_tests(){
    test_fondamentali();
    test_sparse_matrix();
    test_sparse_matrix_iterator();
    test_const();
    test_evaluate();
    test_custom_class();
}

int main() {
    execute_tests();

    return 0;
}