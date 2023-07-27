#ifndef QUESTION_HPP
#define QUESTION_HPP
#include<bits/stdc++.h>
//#include<windows.h>
#define to_string std::__cxx11::to_string
//#include "ui.hpp"
class Option {
public:
	std::pair<int, int> next_chapter;
	bool available;
	std::string option_name, option_word;
	std::pair<int, int> get_next_chapter() {return next_chapter;}
};
class Question {
	std::string question_name, correct_option_name;
	bool print_option;
	std::vector<Option> options;
	Option correct_option;

	// for testing
	public:
		std::pair<int, int> ask() { return std::make_pair(1, 1); }

	void read(std::vector<std::vector<bool>>& is_chapter_visited, int i, int j) {
		//1. question name 2. # 3. correct_option 4. print_options 5. {option_word+condition+next_chap}
		std::string str;
		int n, m;
		std::fstream ifile;
		ifile.open("qs_" + to_string(i) + "_" + to_string(j) + ".txt", std::ios::in);
		while (getline(ifile, str)) {
			if (str != "#") question_name += str + '\n';
			else break;
		}
		getline(ifile, str);
		correct_option_name = str;
		getline(ifile, str);
		std::stringstream ss;
		if (str == "0") {
			Option tmp;
			print_option = false;
			getline(ifile, str);
			if (str != "") {
				ss << str;
				ss >> n, ss >> m;
				tmp.next_chapter = std::make_pair(n, m);
				ss.str(""), ss.clear();
			}
			else tmp.next_chapter = std::make_pair(-1, -1);
			tmp.option_name = correct_option_name;
			tmp.available = true;
			correct_option = tmp;
			options.push_back(tmp);
		}
		else {
			print_option = true;
			Option tmp; std::string idx = "A";
			while (getline(ifile, str)) {
				tmp.option_name = idx, idx[0]++;
				tmp.option_word = str;
				getline(ifile, str);
				if (str != "") {
					tmp.available = false;
					ss << str;
					ss >> n, ss >> m;
					if (is_chapter_visited[n][m]) tmp.available = true;
					ss.str(""), ss.clear();
				}
				else tmp.available = true;
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
	/*void wait_for(int time) { //counted by ms
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
	std::pair<int, int> ask() {
		std::string your_ans;
		std::cout << "Enter your answer:";
		getline(std::cin, your_ans);
		while (your_ans != correct_option_name && correct_option_name != "") {
			if (your_ans != "") {
				std::cout << "Wrong Answer\n" ; wait_for(30000);
				std::cout << "\ninput your answer:";
				getline(std::cin, your_ans);
			}
			else std::cout << "Enter your answer:", getline(std::cin, your_ans);
		}
		std::cout << "Correct\n", Sleep(1000);
		return correct_option.get_next_chapter();
	}*/
};

#undef to_string

#endif
