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
    Pair<int, int> chapter_info;
    bool available, has_question;
    void read() {
      String file_name = chapter_name + ".txt";
      std::ifstream file(file_name);
      if(!file.is_open() || file.bad()) {
        std::cerr << "In Chpapter::read(): cannot open file\n";
        return;
      }
      while(!file.eof()) {
        String line;
        if(line == "#") {
          break;
        }
        std::getline(file, line);
        content.push_back(line);
      }
      if(!file.eof()) {
        String has_question_string;
        std::getline(file, has_question_string);
        has_question = (has_question_string == "1");
      } else {
        std::cerr << "In Chapter::read(): missing has_question_string";
      }
    }

  public:
    Chapter(Pair<int, int> info) : chapter_info(info) {
      chapter_name = "ch_" + to_string(info.first) + "_" + to_string(info.second);
      read();
    }
    Chapter* start() {
      print_chapter_content(content);
      Pair<int, int> ask_res = ask();
      while(ask_res == std::make_pair(-1, -1)) {
        ask_res = ask();
      }
      return new Chapter(ask_res);
    }
    Pair<int, int> get_chapter_info() { return chapter_info; }
};

#undef String
#undef Vector
#undef to_string
#undef Pair

#endif
