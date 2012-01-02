#include <iostream>
#include "util.h"

i32 add(const i32 a, const i32  b)
{
  return a+b;
};

int main(/*const int argc, const char **argv*/)
{
  int i = 10;
  i = add(i, 5);
  std::cout << "Hello world!" << std::endl;

  bool b = file_exists("Data/test.txt");
  std::cout << "File exists: " << b << std::endl;

  getchar();
  return 0;
};
