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
			Matrix<int> B(rows*2+columns,columns*2+rows);
			Matrix<int> C;
			THEN("The number of rows and columns must be preserved") 
			{
				REQUIRE(A.Rows() == rows);
				REQUIRE(A.Columns() == columns);
				REQUIRE(B.Rows() == 2*rows+columns);
				REQUIRE(B.Columns() == 2*columns+rows);
				REQUIRE(C.Rows() == 0);
				REQUIRE(C.Columns() == 0);
			}
		}
	}
}

SCENARIO("Matrix operator >>", "[Fill]") 
{
	std::ifstream input("A.txt");
	Matrix<int> A(2, 2);
	REQUIRE( input >> A );
	REQUIRE( A[0][0] == 2 );
	REQUIRE( A[0][1] == 3 );
	REQUIRE( A[1][0] == 2 );
	REQUIRE( A[1][1] == 1 );
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
	REQUIRE(row[1]==1);
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
	bool flagA=false, flagB=false;
	Matrix<int> A(3, 2);
	Matrix<int> B(2, 2);
	try {
		std::ifstream("A.txt") >> A;
	}
	catch (MatrixException &) {
		flagA = true;
	}
	REQUIRE(flagA);
	try {
		std::ifstream("404.txt") >> A;
	}
	catch (MatrixException &) {
		flagB = true;
	}
	REQUIRE(flagB);
}
SCENARIO("Exception empty", "[emptyerror]")
{
	bool flag=false;
	Matrix<int> A;
	try {
	int* row = A[0];
	}
	catch (MatrixException &) {
		flag = true;
	}
		REQUIRE(flag);
}
SCENARIO("Exception row's index", "[indexerror]")
{
	bool flag=false;
	Matrix<int> A(2, 2);
	std::ifstream("A.txt") >> A;
	try {
	int* row = A[404];
	}
	catch (MatrixException &) {
		flag = true;
	}
		REQUIRE(flag);
}
SCENARIO("Exception size", "[sizerror]")
{
	bool flag=false;
	Matrix<int> A(2, 2);
	Matrix<int> B(3, 3);
	try {
		A+B;
	}
	catch (MatrixException &) {
		flag = true;
	}
		REQUIRE(flag);
}
SCENARIO("Exception size for *", "[sizerror1]")
{
	bool flag=false;
	Matrix<int> A(2, 2);
	Matrix<int> B(3, 3);
	try {
		A*B;
	}
	catch (MatrixException &) {
		flag = true;
	}
		REQUIRE(flag);
}
