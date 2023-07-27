#include <utility>
#include "story.hpp"

int main() {
  Story story(std::make_pair(3, 3));
  story.start();
}