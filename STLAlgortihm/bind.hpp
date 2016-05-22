#pragma once
#include <iostream>

namespace bind {

  template <class F, class ...Args>
  auto bind(F f, Args... args)
  {
    return [f, args...] {
      return f(args...);
    };
  }

  int add(int i, int j)
  {
    return i + j;
  }

  int inc(int i)
  {
    return i + 1;
  }

  void run()
  {
    std::cout << bind(add, 20, 20)() << std::endl;
    std::cout << bind(inc, 10)() << std::endl;
  }
}