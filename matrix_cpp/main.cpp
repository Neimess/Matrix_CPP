#include <iostream>
#include <ctime>
#include <windows.h>
#include <cmath>
#include "matrix_lib.h"
#include "test.h"

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "ru");

	double data[9] = {1, 7, 4, 0, 9, 4, 8, 8, 2};
	Matrix A = Matrix(3, 3).fill_from_array(data);
	Matrix B = Matrix(3, 4).fill_random(10);
	std::cout << "First Matrix\n"
			  << A;
	std::cout << "Second Matrix\n"
			  << B;

	try
	{
		std::cout << "Addiction of two matrix\n"
				  << A + B;
		std::cout << "Subtraction of two matrix\n"
				  << A - B;
	}
	catch (const Matrix_Exception &e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	try
	{
		std::cout << "Minor\n"
				  << B.minor(0, 0);
	}
	catch (const Matrix_Exception &e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}
	try
	{
		std::cout << "Multiplication of two matrix\n"
				  << A * B;
	}
	catch (const Matrix_Exception &e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	try
	{
		std::cout << "Determinant\n"
				  << A.determinant(&A) << std::endl;
		std::cout << "Reverse Matrix\n"
				  << A.reverse(&A) << std::endl;
		std::cout << "Exponent Matrix\n"
				  << A.exponent();
	}
	catch (Matrix_Exception &e)
	{
		std::cerr << "Caught: " << e.what() << std::endl;
		std::cerr << "Type: " << typeid(e).name() << std::endl;
	}

	test();
}