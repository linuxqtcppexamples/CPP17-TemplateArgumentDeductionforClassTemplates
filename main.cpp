#include <iostream>
#include <map>

 int main() 
 {
     
  std::map<std::string, int> mapUsersAge { { "Alex", 45 }, { "John", 25 } };
  
  //Template Argument Deduction for Class Templates - mapCopy type is deduced from the type of mapUsersAge. No need to declare std::map<std::string,int> mapCopy{...}.
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