Template Argument Deduction for Class Templates
Example1:

#include #include

int main()
{ 

std::map<std::string, int> mapUsersAge { { "Alex", 45 }, { "John", 25 } };

//Template Argument Deduction for Class Templates - mapCopy type is deduced from the type of mapUsersAge.

//No need to declare std::mapstd::string,int mapCopy{...}. 

std::map mapCopy{mapUsersAge};

//New inserting member function for maps - insert_or_assign 
//Structured Bindings - captures a returned pair from insert_or_assign into separate names. 
//init if statement - iter and wasAdded are visible only in the scope of the surrounding if statement 

if (auto [iter, wasAdded] = mapCopy.insert_or_assign("John", 26); !wasAdded) 
std::cout << iter->first << " reassigned...\n";


//Structured Bindings inside a range-based for loop - we can iterate using key and value rather than pair.first and pair.second. 

for (const auto& [key, value] : mapCopy) 
std::cout << key << ", " << value << '\n';

return 0; 

}

Output: 

John reassigned...
Alex, 45 
John, 26

Examples2: 

#include <iostream>

/*

if constexpr - to discard code at compile-time, used to match the
template parameter.

_v variable templates for type traits - no need to write std::trait_-
name<T>::value

*/
template<typename T> void linePrinter(const T& x) {
if constexpr (std::is_integral_v<T>)
	std::cout << "num: " << x << '\n';
else if constexpr (std::is_floating_point_v<T>) {
	const auto frac = x - static_cast<long>(x);
	std::cout << "flt: " << x << ", frac " << frac << '\n';
}
else if constexpr(std::is_pointer_v<T>) {
std::cout << "ptr, ";
linePrinter(*x);
}
else
std::cout << x << '\n';
}

template<typename ... Args> void printWithInfo(Args ... args) {

/*
Fold Expressions inside printWithInfo. This feature simplifies variadic
templates. In the example, we invoke linePrinter() over all input arguments.

*/
(linePrinter(args), ...); // fold expression over the comma operator
}

int main () {
int i = 10;
float f = 2.56f;
printWithInfo(&i, &f, 30);
}

Output: 

ptr, num: 10
ptr, flt: 2.56, frac 0.56
num: 30



Referebce Book - C++17 in detail written Filipek 
Tested on http://coliru.stacked-crooked.com/

