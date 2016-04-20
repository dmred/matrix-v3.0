#include "stdafx.h"
#include "matrix.h"
#include <iostream>
#include <catch.hpp>

SCENARIO("Matrix init", "[init]") 
{
	GIVEN("The number of rows and columns") 
	{
		auto rows = 3;
		auto columns = 4;
		WHEN("Create instansce of Matrix") 
		{
			Matrix<int> A(rows, columns);
			Matrix<int> B;
			THEN("The number of rows and columns must be preserved") 
			{
				REQUIRE(A.Rows() == rows);
				REQUIRE(A.Columns() == columns);
				REQUIRE(B.Rows() == 0);
				REQUIRE(B.Columns() == 0);
			}
		}
	}
}

SCENARIO("Matrix operator >>", "[Fill]") 
{
	std::ifstream input("A.txt");
	Matrix<int> A(2, 2);
	std::cout << endl;
	REQUIRE( input >> A );
	REQUIRE( A[0][0] == 2 );
	REQUIRE( A[0][1] == 1 );
	REQUIRE( A[1][0] == 1 );
	REQUIRE( A[1][1] == 2 );
}
SCENARIO("Matrix operator <<", "[out]") 
{
	Matrix<int> A(2, 2);
	Matrix<int> B(2, 2);
	std::ifstream("A.txt") >> A;
	fstream out; 
	out.open("out.txt");
	REQUIRE(out << A);
	std::ifstream("out.txt") >> B;
	out.close();
	REQUIRE(A==B);
}
SCENARIO("Matrix operator +", "[addition]") 
{
	Matrix<int> A(2, 2);
	Matrix<int> B(2, 2);
	Matrix<int> expected(2, 2);
	Matrix<int> result(2, 2);
	std::ifstream("A.txt") >> A;
	std::ifstream("B.txt") >> B;
	std::ifstream("A+B.txt") >> result;
	expected=A+B;
	REQUIRE(expected==result);
}
SCENARIO("Matrix operator -", "[subtraction]") 
{
	Matrix<int> A(2, 2);
	Matrix<int> B(2, 2);
	Matrix<int> expected(2, 2);
	Matrix<int> result(2, 2);
	std::ifstream("A.txt") >> A;
	std::ifstream("B.txt") >> B;
	std::ifstream("A-B.txt") >> result;
	expected=A-B;
	REQUIRE(expected==result);
}
SCENARIO("Matrix operator *", "[multiplication]") 
{
	Matrix<int> A(2, 2);
	Matrix<int> B(2, 2);
	Matrix<int> expected(2, 2);
	Matrix<int> result(2, 2);
	std::ifstream("A.txt") >> A;
	std::ifstream("B.txt") >> B;
	std::ifstream("AxB.txt") >> result;
	expected=A*B;
	REQUIRE(expected==result);
}
SCENARIO("Matrix operator [](int)", "[row]") 
{
	Matrix<int> A(2, 2);
	std::ifstream("A.txt") >> A;
	int* row = A[1];
	REQUIRE(row[0]==2);
	REQUIRE(row[1]==2);
}
SCENARIO("Matrix operator ==", "[comparison]") 
{
	Matrix<int> A(2, 2);
	Matrix<int> B(2, 2);
	std::ifstream("A.txt") >> A;
	std::ifstream("A.txt") >> B;
	REQUIRE(A==B);
}
SCENARIO("Exception fill", "[fillerror]")
{
	bool f1=false, f2=false;
	Matrix<int> A(3, 2);
	Matrix<int> B(2, 2);
	try {
		std::ifstream("A.txt") >> A;
	}
	catch (MatrixException &) {
		f1 = true;
	}
	REQUIRE(f1);
	try {
		std::ifstream("404.txt") >> A;
	}
	catch (MatrixException &) {
		f2 = true;
	}
	REQUIRE(f2);
}
SCENARIO("Exception emty", "[emptyerror]")
{
	bool f=false;
	Matrix<int> A;
	try {
	int* row = A[0];
	}
	catch (MatrixException &) {
		f = true;
	}
		REQUIRE(f);
}
SCENARIO("Exception row's index", "[indexerror]")
{
	bool f=false;
	Matrix<int> A(2, 2);
	std::ifstream("A.txt") >> A;
	try {
	int* row = A[404];
	}
	catch (MatrixException &) {
		f = true;
	}
		REQUIRE(f);
}
SCENARIO("Exception size", "[sizerror]")
{
	bool f=false;
	Matrix<int> A(2, 2);
	Matrix<int> B(3, 3);
	try {
		A+B;
	}
	catch (MatrixException &) {
		f = true;
	}
		REQUIRE(f);
}
SCENARIO("Exception size for *", "[sizerror1]")
{
	bool f=false;
	Matrix<int> A(2, 2);
	Matrix<int> B(3, 3);
	try {
		A*B;
	}
	catch (MatrixException &) {
		f = true;
	}
		REQUIRE(f);
}
