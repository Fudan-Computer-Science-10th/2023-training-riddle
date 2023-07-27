#ifndef CHAPTER_HPP
#define CHAPTER_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <utility>
#include "question.hpp"
#include "ui.hpp"

#define String std::string
#define Vector std::vector
#define to_string std::__cxx11::to_string
#define Pair std::pair

class Chapter : protected Question {
  private:
    String chapter_name;
    Vector<String> content;
    bool available;
    void read() {
      String file_name = chapter_name + ".txt";
      std::ifstream file(file_name);
      if(!file.is_open() || file.bad()) {
        std::cerr << "In Chpater::read(): cannot open file\n";
        return;
      }
      while(!file.eof()) {
        String line;
        std::getline(file, line);
        content.push_back(line);
      }
    }

  public:
    Chapter(Pair<int, int> info) {
      chapter_name = "ch_" + to_string(info.first) + "_" + to_string(info.second);
      read();
    }
    Chapter* start() {
      print_chapter_content(content);
      return new Chapter(ask());
    }
    Chapter(const Chapter&);
};  // for compile testing

#undef Str
#undef Vector
#undef to_string

#endif
