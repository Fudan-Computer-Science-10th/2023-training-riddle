#ifndef UI_HPP
#define UI_HPP

#include <iostream>
#include <vector>
#include <string>

#define Cout std::cout
#define Cin std::cin
#define Vector std::vector
#define String  std::string

void print_chapter_content(Vector<String>& content) {
  String tmp;
  for(auto& c : content) {
    Cout << c << "\n\n";
    std::getline(Cin, tmp);
  }
}

#undef Cout
#undef Cin
#undef Vector
#undef String

#endif
