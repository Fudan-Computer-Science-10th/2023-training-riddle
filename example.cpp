/* Solution 1 */

// question.hpp
#include <vector>

class Option {
  private:
    Option* next_chapter;
  public:
    Option* get_next_chapter() { return next_chapter; }
};

class Question {
  private:
    std::vector<Option> options;
  public:
    Question(Question* question) {
      // to something
    }
    Question(Option* option) {
      // to something
    }
    Question() {
      // to something
    }
    Question* ask() {
      return new Question(options[0].get_next_chapter());
    }
};


// chapter.hpp
// #include "question.hpp"
class Chapter : protected Question {
  public:
    Chapter(Question* question) : Question(question) {
      // to something
    }
    Chapter* next_chapter() {
      return new Chapter(ask());
    }
};


// story.hpp
class Story : protected Chapter {
  private:
    Story(Chapter* chapter) : Chapter(chapter) {}
  public:
    void start() {
      *this = new Story(next_chapter());
    }
};
