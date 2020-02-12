// Runtime

#include <iostream>

long fibo(int n)
{
  if (n==0 || n==1)
    return 1;
  return fibo(n-1)+fibo(n-2);
}

int main()
{
  long res = fibo(42);
  std::cout << "fibo(42): " << res << std::endl;
  return 0;
}
