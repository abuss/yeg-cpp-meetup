// Metaprogramming

#include <iostream>

template <int N>
struct fibo
{
  enum { value = fibo<N-1>::value + fibo<N-2>::value };
};

template <>
struct fibo<0>
{
  enum { value = 1 };
};

template <>
struct fibo<1>
{
  enum { value = 1 };
};

int main()
{
  long res = fibo<42>::value;
  std::cout << "fibo(42): " << res << std::endl;
  return 0;
}
