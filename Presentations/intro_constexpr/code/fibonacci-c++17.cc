// C++17

#include <iostream>
#include <array>

constexpr int N = 50;
using fibo_tbl_t = std::array<long,N>;

constexpr fibo_tbl_t gen_fibo_tbl()
{
  fibo_tbl_t res = {};
  res[0] = 1;
  res[1] = 1;
  for(int i=2; i<N; ++i) {
    res[i] = res[i-1] + res[i-2];
  }
  return res;
}

int main()
{
  fibo_tbl_t fibo_tbl = gen_fibo_tbl();
  std::cout << "fibo(42): " << fibo_tbl[42] << std::endl;
  return 0;
}
