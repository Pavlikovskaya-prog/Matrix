#include <cstdlib>
#include <iostream>
#include <stdexcept>

namespace {

    class matrix {
        int Row, Col;
        double **Value;
    public:

        matrix(unsigned int, unsigned int);

        matrix(const matrix &);

        int GetRow();

        int GetCol();


        friend bool operator==(const matrix &m1, const matrix &m2);

        friend bool operator!=(const matrix &m1, const matrix &m2);

        friend std::istream &operator>>(std::istream &istr, matrix &m);

        friend std::ostream &operator<<(std::ostream &ostr, matrix &m);

        friend matrix operator+(const matrix &m1, const matrix &m2);

        friend matrix operator-(const matrix &m1, const matrix &m2);

        friend matrix operator*(const matrix &m1, const matrix &m2);
    };


    bool operator==(const matrix &m1, const matrix &m2) {
        return m1.Row == m2.Row && m1.Col == m2.Col;
    }

    bool operator!=(const matrix &m1, const matrix &m2) {
        return !(m1 == m2);

    }


    ~

    matrix();
};

matrix::matrix(int row, int col) {
    Row = row;
    Col = col;
    Value = new double *[row];
    for (int i = 0; i < row; i++) Value[i] = new double[col];
}

matrix::matrix(const matrix &m)
        : Row(m.Row),
          Col(m.Col) {
    Value = new double *[Row];
    for (int i = 0; i < Row; i++) Value[i] = new double[Col];
    for (int i = 0; i < Row; i++) {
        for (int j = 0; j < Col; j++)
            Value[i][j] = m.Value[i][j];
    }
}

int matrix::GetRow() {
    return Row;
}

int matrix::GetCol() {
    return Col;
}

std::istream &operator>>(std::istream &istr, matrix &m) {
    for (int i = 0; i < m.GetRow(); i++)
        for (int j = 0; j < m.GetCol(); j++)
            istr >> m(i, j);
    return (istr);
}

std::ostream &operator<<(std::ostream &ostr, matrix &m) {
    for (int i = 0; i < m.GetRow(); i++) {
        for (int j = 0; j < m.GetCol(); j++)
            ostr << m(i, j) << "\t";
        ostr << "\n";
    }
    return (ostr);
}

matrix operator+(matrix & m1, matrix & m2) {
    matrix temp(m1.GetRow(), m1.GetCol());
    for (int i = 0; i < m1.GetRow(); i++)
        for (int j = 0; j < m1.GetCol(); j++)
            temp(i, j) = m1(i, j) + m2(i, j);
    return (temp);
}

matrix operator-(matrix & m1, matrix & m2) {
    matrix temp1(m1.GetRow(), m1.GetCol());
    for (int i = 0; i < m1.GetRow(); i++)
        for (int j = 0; j < m1.GetCol(); j++)
            temp1(i, j) = m1(i, j) - m2(i, j);
    return (temp1);
}

matrix operator*(matrix & m1, matrix & m2) {
    matrix temp1(m1.GetRow(), m1.GetCol());
    for (int i = 0; i < m1.GetRow(); i++)
        for (int j = 0; j < m1.GetCol(); j++)
            temp1(i, j) = m1(i, j) * m2(i, j);
    return (temp1);
}

double &matrix::operator()(int row, int col) {
    return (Value[row][col]);
}

matrix::~matrix() {
    for (int i = 0; i < Row; i++)
        delete[] Value[i];
    delete[] Value;
}


////////////////////////////////////////////////////////////////////////////////

#define assert(x) if (!(x)) {                                                  \
    fprintf(stderr, "Assertion failed: %s, function %s, file %s, line %d.\n",  \
        #x, __PRETTY_FUNCTION__, __FILE__, __LINE__                            \
    );                                                                         \
    abort();                                                                   \
}

////////////////////////////////////////////////////////////////////////////////



int test_matrix_addition() {
    matrix m1{(1, 1, 1), (1, 1, 1), (1, 1, 1)};
    matrix m2{(1, 1, 1), (1, 1, 1), (1, 1, 1)};

    matrix actual = m1 + m2;
    matrix expected = {(2, 2, 2), (2, 2, 2), (2, 2, 2)};

    assert(actual == expected);
};

int test_matrix_substitution() {
    matrix m1{(1, 1, 1), (1, 1, 1), (1, 1, 1)};
    matrix m2{(1, 1, 1), (1, 1, 1), (1, 1, 1)};

    matrix actual = m1 - m2;
    matrix expected = {(0, 0, 0), (0, 0, 0), (0, 0, 0)};

    assert(actual == expected);
};

int test_matrix_multiplication() {
    matrix m1{(1, 1, 1), (1, 1, 1), (1, 1, 1)};
    matrix m2{(1, 1, 1), (1, 1, 1), (1, 1, 1)};

    matrix actual = m1 * m2;
    matrix expected = {(3, 3, 3), (3, 3, 3), (3, 3, 3)};

    assert(actual == expected);

    try {
        m1 + m2;
    } catch (const std::runtime_error &e) {
        return 0;  // Fine
    } catch (...) {
// pass
    }


    assert(false);
};


int run_all_tests() {
    test_matrix_addition();
    test_matrix_substitution();
    test_matrix_multiplication();
}

}


////////////////////////////////////////////////////////////////////////////////

int main() {
    

    try {
        run_all_tests();
    } catch (...) {
        std::cerr << "Tests failed!" << std::endl;
        return 1;
    }

    std::cerr << "Tests passed!" << std::endl;
    return 0;
}

