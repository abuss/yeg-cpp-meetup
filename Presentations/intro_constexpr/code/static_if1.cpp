#include <iostream>
#include <string>

template <typename T>
std::string str(T t)
{
    if (std::is_convertible_v<T, std::string>)
        return t;
    else
        return std::to_string(t);
}

int main()
{
  std::string val = "10";
  auto t = str(val);
  std::cout << t+"!" << std::endl;
  return 0;
}
