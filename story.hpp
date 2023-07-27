#ifndef STORY_HPP
#define STORY_HPP

#include <vector>
#include <utility>
#include "chapter.hpp"

#define Vec std::vector
#define Pair std::pair

class Story : protected Chapter {
  private:
    Chapter *now_chapter;
    Vec<Vec<bool>> is_chapter_visited;

  public:
    Story() : Chapter(std::make_pair(0, 0)) {
      now_chapter = new Chapter(std::make_pair(0, 0));
    }
    ~Story() { delete now_chapter; }
    Story(const Story& other) : Chapter(other), now_chapter(other.now_chapter), is_chapter_visited(other.is_chapter_visited) {}
    void start() {
      while(now_chapter != nullptr) {
        Chapter *next_chapter = now_chapter->start();
        delete now_chapter;
        now_chapter = next_chapter;
      }
    }
};

#undef Vec

#endif

