#ifndef STORY_HPP
#define STORY_HPP

#include <vector>
#include <utility>
#include <string>
#include <fstream>
#include "chapter.hpp"

#define Vector std::vector
#define Pair std::pair
#define String std::string

class Story : protected Chapter {
  private:
    Chapter *now_chapter;
    Vector<Vector<bool>> is_chapter_visited;
    const String GAME_LOG_FN = "2023-trainning-riddle.log";

  public:
    Story(Pair<int, int> total_info_count) : Chapter(std::make_pair(0, 0)) {
      now_chapter = new Chapter(std::make_pair(0, 0));
      is_chapter_visited = Vector<Vector<bool>>(total_info_count.first, Vector<bool>(total_info_count.second, false));
    }
    ~Story() { delete now_chapter; }
    Story(const Story& other) : Chapter(other), now_chapter(other.now_chapter), is_chapter_visited(other.is_chapter_visited) {}
    void start() {
      while(now_chapter != nullptr) {
        Chapter *next_chapter = now_chapter->start();
        Pair<int, int> now_chapter_info = now_chapter->get_chapter_info();
        is_chapter_visited[now_chapter_info.first][now_chapter_info.second] = true;
        delete now_chapter;
        now_chapter = next_chapter;
      }
    }
};

#undef Vector
#undef Pair
#undef String

#endif

