#ifndef QUESTION_HPP
#define QUESTION_HPP

#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <fstream>
#include <sstream>
#include <windows.h>
#include "ui.hpp"

class Option {
public:
	std::pair<int, int> next_chapter;
	bool available;
	std::string option_name, option_word;
	std::pair<int, int> get_next_chapter() {return next_chapter;}
};

class Question {
	private:
		std::string question_name, correct_option_name = "#";
		bool print_option;
		std::vector<Option> options;
		Option correct_option;

		void read(int i, int j) {
			//1. question name 2. # 3. correct_option 4. print_options 5. {option_word+condition+next_chap}
			std::string str;
			int n, m, type;//type1=normal question, 2=all ans ques, 3=answer exist
			std::fstream ifile;
			ifile.open("qs_" + std::__cxx11::to_string(i) + "_" + std::__cxx11::to_string(j) + ".txt", std::ios::in);
			ifile >> type;
			while (getline(ifile, str)) {
				if (str != "#") question_name += str + '\n';
				else break;
			}
			if (type == 3) getline(ifile, str), correct_option_name = str;
			ifile >> print_option;
			std::stringstream ss;
			if (!print_option) {
				Option tmp;
				getline(ifile, str);
				if (str != "") {
					ss << str;
					ss >> n, ss >> m;
					tmp.next_chapter = std::make_pair(n, m);
					ss.str(""), ss.clear();
				}
				else tmp.next_chapter = std::make_pair(-1, -1);
				tmp.option_name = correct_option_name;
				tmp.available = false;
				correct_option = tmp;
				options.push_back(tmp);
			}
			else {
				Option tmp; std::string idx = "A";
				while (getline(ifile, str)) {
					tmp.option_name = idx, idx[0]++;
					tmp.option_word = str;
					ifile >> tmp.available;
					getline(ifile, str);
					if (str != "") {
						ss << str;
						ss >> n, ss >> m;
						tmp.next_chapter = std::make_pair(n, m);
						ss.str(""), ss.clear();
					}
					else tmp.next_chapter = std::make_pair(-1, -1);
					options.push_back(tmp);
					if (tmp.option_name == correct_option_name) {
						correct_option = tmp;
					}
				}
			}
		}

		void wait_for(int time) { //counted by ms
			int Second_cnt = time / 1000;
			std::cout << "wait for " << Second_cnt << " seconds";
			while ( Second_cnt ) {
				Second_cnt--;
				std::cout << '\r';
				Sleep(1000);
				std::cout << "wait for " << Second_cnt << " seconds           ";
			}
			std::cout << "\r                                                        \r";
			return;
		}

	public:
		std::pair<int, int> ask() {
			bool ask_flag = false;
			if (correct_option_name != "#") ask_flag = true;
			std::string your_ans;
			std::cout << "input your answer:";
			getline(std::cin, your_ans);
			while (your_ans != correct_option_name && ask_flag) {
				if (your_ans != "")
					std::cout << "Wrong Answer\n", wait_for(30000);
				std::cout << "input your answer:", getline(std::cin, your_ans);
			}
			if (ask_flag) std::cout << "Correct\n", Sleep(1000);
			if (ask_flag) return correct_option.get_next_chapter();
			else {
				if (your_ans.size() == 1) your_ans[0] = toupper(your_ans[0]);
				your_ans[0] -= 'A';
				if (0 <= your_ans[0] && your_ans[0] < int(options.size()))
					return options[your_ans[0]].get_next_chapter();
			}
			return std::make_pair(-1, -1);
		}
};

#endif