#include <utility>
#include <cstdlib>
#include "story.hpp"

int main() {
  Story story(std::make_pair(3, 3));
  story.start();

  std::system("pause");
  return 0;
}