#ifndef STORY_HPP
#define STORY_HPP

#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include <ctime>
#include "chapter.hpp"

#define Vector std::vector
#define Pair std::pair
#define String std::string

class Story {
  private:
    Chapter *now_chapter;
    Vector<Vector<bool>> is_chapter_visited;
    const String GAME_LOG_FN = "2023-trainning-riddle.log";

    void record_game_log(Pair<int, int> now_chapter_info) {
      std::ofstream file(GAME_LOG_FN, std::ios::app);
      is_chapter_visited[now_chapter_info.first][now_chapter_info.second] = true;
      std::time_t rawtime;
      std::tm *ptm;
      time(&rawtime);
      ptm = std::gmtime(&rawtime);
      file << "[" << (ptm->tm_hour+8) % 24 << ":" << ptm->tm_min << "]" << " " 
           << now_chapter_info.first << " " << now_chapter_info.second << "\n";
      file.close();
    }

  public:
    Story(Pair<int, int> total_info_count) {
      is_chapter_visited = Vector<Vector<bool>>(total_info_count.first, Vector<bool>(total_info_count.second, false));
      std::ifstream file(GAME_LOG_FN);
      if(file.is_open()) {
        String input;
        int n, m;
        while(file >> input) {
          file >> n >> m;
          is_chapter_visited[n][m] = true;
        }
        now_chapter = new Chapter(std::make_pair(n, m));
      } else {
        now_chapter = new Chapter(std::make_pair(1, 1));
      }
      file.close();
    }
    ~Story() { delete now_chapter; }
    Story(const Story& other) : now_chapter(other.now_chapter), is_chapter_visited(other.is_chapter_visited) {}
    void start() {
      while(now_chapter != nullptr) {
        Pair<int, int> now_chapter_info = now_chapter->get_chapter_info();
        record_game_log(now_chapter_info);
        Chapter *next_chapter = now_chapter->start();
        delete now_chapter;
        now_chapter = next_chapter;
      }
    }
};

#undef Vector
#undef Pair
#undef String

#endif

