#pragma once

#include <iostream>

namespace lambda {

  void mutable_test()
  {
    int a = 1, b = 1, c = 1;

    // <mutable>: make value capture variable 
    // to chanagable only in body scope.
    auto m1 = [a, &b, &c]() mutable {
      auto m2 = [a, b, &c]() mutable {
        std::cout << a << b << c << '\n';
        a = 4; b = 4; c = 4;
      };
      // a is value captured, but changable in m1
      a = 3; b = 3; c = 3;
      std::cout << a << b << c << '\n';
      m2();
    };

    a = 2; b = 2; c = 2;

    m1();                             // calls m2() and prints 123
    std::cout << a << b << c << '\n'; // prints 234
  }

  // generic lambda, operator() is a template with one parameter
  auto vglambda = [](auto printer) {
    return [=](auto&&... ts) // generic lambda, ts is a parameter pack
    {
      printer(std::forward<decltype(ts)>(ts)...);
      return [=] { printer(ts...); }; // nullary lambda (takes no parameters)
    };
  };

  auto printer1(int a)
  {
    std::cout << a << std::endl;
  }

  auto printer2(int a, int b) 
  {
    std::cout << a << "," << b << std::endl;
  }

  void vglambda_test()
  {
    vglambda(printer1)(10);
    vglambda(printer2)(10, 20);
    vglambda([](auto a, auto b, auto c) {
      std::cout << a << "," << b << "," << c << std::endl; })(1, 'a', 10)();
  }

  void run()
  {
    //mutable_test();
    vglambda_test();
  }
}