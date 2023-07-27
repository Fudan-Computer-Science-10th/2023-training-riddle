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
  for (auto& c : content) {
    Cout << c << "\n";
    std::getline(Cin, tmp);
  }
}
void print_question_content(String STR, Vector<String>& content) {
  Cout << STR << '\n';
  for (auto & i : content) Cout << i << "\n\n";
}
#undef Cout
#undef Cin
#undef Vector
#undef String

#endif
