#include "matrix_lib.h"
#ifndef TEST_H
#define TEST_H
void test_add() 
{
	double data1[6] = { 3, 1, 2,
					   4, 5, 7 };
	double data2[6] = { 8, 2, 1,
					   -2, 2, 4 };
	double ans_d[6] = { 11, 3, 3,
					   2, 7, 11 };
	Matrix matrix1 = Matrix(2, 3).fill_from_array(data1);
	Matrix matrix2 = Matrix(2, 3).fill_from_array(data2);
	Matrix test_add = Matrix(2, 3).fill_from_array(ans_d);
	if (test_add != matrix1 + matrix2) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout<<"Addition test failed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Addition test passed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_sub() 
{
	double data1[6] = { 3, 1, 2,
					   4, 5, 7 };
	double data2[6] = { 8, 2, 1,
					   -2, 2, 4 };
	double ans_d[6] = { -5, -1, 1,
					   6, 3, 3 };
	Matrix matrix1 = Matrix(2, 3).fill_from_array(data1);
	Matrix matrix2 = Matrix(2, 3).fill_from_array(data2);
	Matrix test_add = Matrix(2, 3).fill_from_array(ans_d);
	if (test_add != matrix1 - matrix2) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Substraction test failed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Substruction test passed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_mult() 
{
	double data1[9] = { 1, 7, 4,
					    0, 9, 4, 
						8, 8, 2 };
	double data2[9] = { 4, 5, 5,
					    1, 7, 1,
					    1, 5, 2};
	double ans_d[9] = { 15, 74, 20,
					    13, 83, 17,
					    42, 106, 52};
	Matrix matrix1 = Matrix(3, 3).fill_from_array(data1);
	Matrix matrix2 = Matrix(3, 3).fill_from_array(data2);
	Matrix test_add = Matrix(3, 3).fill_from_array(ans_d);
	if (test_add != matrix1 * matrix2) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Multiplication test failed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Multiplication test passed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_mult_k() 
{
	double data1[3] = { 1, 7, 4};
	double ans_d[3] = {3, 21, 12};
	Matrix matrix1 = Matrix(1, 3).fill_from_array(data1);
	Matrix test_add = Matrix(1, 3).fill_from_array(ans_d);
	if (test_add != matrix1 * 3) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Multiplication test failed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Multiplication test passed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_div_k() {
	double data1[3] = { 6, 21, 18 };
	double ans_d[3] = { 2, 7, 6 };
	Matrix matrix1 = Matrix(1,3).fill_from_array(data1);
	Matrix test_div = Matrix(1, 3).fill_from_array(ans_d);
	if (test_div != matrix1 / 3) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Division test failed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Division test passed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_det() 
{
	double data1[9] = { 1, 7, 4,
						0, 9, 4,
						8, 8, 2 };
	Matrix matrix1 = Matrix(3, 3).fill_from_array(data1);
	double determinant = matrix1.determinant(matrix1, matrix1.getrow());
	if (determinant != -78) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Determinant test failed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Determinant test passed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_rev() {
	double data1[9] = { 1, 7, 4,
						0, 9, 4,
						8, 8, 2 };
	double ans[9] = { 0.179487,  -0.230769, 0.102564,
					 -0.410256,	  0.384615, 0.0512821,
					 0.923077,   -0.615385, -0.115385 };
	Matrix matrix1 = Matrix(3, 3).fill_from_array(data1);
	Matrix test_rev = Matrix(3, 3).fill_from_array(ans);
	Matrix rev = matrix1.reverse(matrix1, matrix1.getrow());
	if (rev == test_rev) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Reverse test passed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Reverse test failed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_transpose()
{
	double data1[3] = { 1, 7, 4 };
	double ans[3] = {1,7,4};
	Matrix matrix1 = Matrix(3,1).fill_from_array(data1);
	Matrix test_trans = Matrix(1, 3).fill_from_array(ans);
	if (matrix1.set_transpose() == test_trans) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "Trasposition test passed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "Transposition test failed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_set_identity()
{
	double data1[9] = { 1, 7, 4,
						0, 9, 4,
						8, 8, 2 };
	double ans[9] = { 1,  0, 0,
					 0,	  1, 0,
					 0,   0, 1 };
	Matrix matrix1 = Matrix(3, 3).fill_from_array(data1);
	Matrix test_identity = Matrix(3, 3).fill_from_array(ans);
	if (matrix1.set_identity() == test_identity) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "SetIdentity test passed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "SetIdentity test failed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


void test_set_zero()
{
	double data1[3] = { 1, 7, 4 };
	double ans[3] = { 0,0,0 };
	Matrix matrix1 = Matrix(3, 1).fill_from_array(data1);
	Matrix test_zero = Matrix(3, 1).fill_from_array(ans);
	if (matrix1.set_zero() == test_zero) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		std::cout << "SetZero test passed\n";
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		std::cout << "SetZero test failed\n";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void test() {
	test_add();
	test_sub();
	test_div_k();
	test_mult_k();
	test_mult();
	test_det();
	test_rev();
	test_transpose();
	test_set_identity();
	test_set_zero();
}

#endif  // TEST_H