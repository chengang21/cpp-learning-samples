/**
  tested using compiler option: -std=c++14  -static-libgcc
*/

#include <iostream>
#include <functional>
#include <algorithm>

using namespace std;
int f()
{
	auto ii = 15;
	cout << ii <<endl;
}

int main()
{
	auto hello = []()								//Assign the lambda expression
	// function<string()> hello = []()
	{
		static int num = 0;
		cout << "hello: " << num << " " << endl;
		++num;

		return "return";
	};

	hello;								//Empty
	cout << hello << endl;				//1 
	hello();							//hello: 0
	cout << hello() << endl ; 	//hello: 0 return
	
	auto str = hello();
	cout << str << endl;
	
	auto sum1 = [](int x, int y) { return x + y; };		//Assign other the lambda expression
	cout << sum1(2, 3) << endl;			// 5
	
	function<int(int, int)> sum2 = [](int x, int y) { return x + y; };	//Assign the same lambda expression to a function object
	cout << sum2(3, 4) << endl;
	
	//Passing arguments in the expression

	int i = 3;
	int j = 5;

	// function<int (void)> paite = [i, &j] { return i + j; };
	auto paite = [i, &j] { return i + j; };

	cout << "1: paite(): " << paite() << endl;  // 8
	
	i = 22;
	j = 44;

	cout << "2: paite(): " << paite() << endl;  // 47
	
	//Create lambda expression with arguments

	int aod = [] (int x, int y) { return x + y; } (5, 4);
	cout << "aod: " << aod << endl;		//9
	
	// cout << "aod: " << aod(12, 13) << endl;		// error: 'aod' cannot be used as a function
	
	//Lambda expression like arguments of function
	
	{
		int arr[] {1, 2, 3, 4, 5};

		cout << "In for_each: ";
		for_each(arr, arr+5, [](int x) {cout << x << ", ";} );
		cout << endl;
	}
 
 	
	//The following lambda expression contains a nested lambda
	int timestwoplusthree = [](int x) { return [](int y) { return y * 2; }(x) + 3; }(5);
	cout << timestwoplusthree << endl; 	//	13
	
	//Lambda higher-order functions

	auto addtwointegers = [](int x) {
		// Return lambda expression
		return [=](int y) { return x + y; };
	};

	auto higherorder = [](const function<int(int)>& f, int z)
	{
		return f(z) * 2;
	};

	auto answer = higherorder(addtwointegers(7), 8);  // (7 + 8) * 2  = 30

	cout << answer << endl; 
	
}


