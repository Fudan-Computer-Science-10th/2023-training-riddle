#include <utility>
#include <cstdlib>
#include "story.hpp"

int main() {
  Story story(std::make_pair(6, 74)); // puts the maximum value of n and m
  story.start();

  std::system("pause");
  return 0;
}