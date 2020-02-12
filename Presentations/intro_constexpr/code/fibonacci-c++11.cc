// C++11

#include <iostream>

constexpr long fibo(int n)
{
  return (n==0 || n==1) ? 1 : fibo(n-1)+fibo(n-2);
}

int main()
{
  long res = fibo(42);
  std::cout << "fibo(42): " << res << std::endl;
  return 0;
}
