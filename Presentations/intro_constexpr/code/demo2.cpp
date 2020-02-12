#include <iostream>

template<typename T>
struct Foo {
  T value;

  T bar1(T& x) const { return value; }
  T bar2(const T& x) const { return x; }
  const T& bar3(T x) const { return value; }
  const T& bar4(const T& x) { return x; }
};

int main(int argc, const char** argv) 
{
  {
    int v = 8;
    Foo<int> a{5};

    int b1 = a.bar1(v);
    int b2 = a.bar2(v);
    int b3 = a.bar3(v);
    int b4 = a.bar4(v);

    int c1 = a.bar1(5);
    int c2 = a.bar2(5);
    int c3 = a.bar3(5);
    int c4 = a.bar4(5);

    const int& d1 = a.bar1(v);
    const int& d2 = a.bar2(v);
    const int& d3 = a.bar3(v);
    const int& d4 = a.bar4(v);

    std::cout << a.value << std::endl;
  }

/*
  {
    int v = 8;
    const Foo<int> a{5};

    int b1 = a.bar1(v);
    int b2 = a.bar2(v);
    int b3 = a.bar3(v);
    int b4 = a.bar4(v);

    // int c1 = a.bar1(5);
    int c2 = a.bar2(5);
    int c3 = a.bar3(5);
    int c4 = a.bar4(5);

    const int& d1 = a.bar1(v);
    const int& d2 = a.bar2(v);
    const int& d3 = a.bar3(v);
    const int& d4 = a.bar4(v);

    std::cout << a.value << std::endl;
  }
*/
  return 0;
}
