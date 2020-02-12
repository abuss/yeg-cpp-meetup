#include <iostream>
#include <string>

template <typename T>
std::enable_if_t<std::is_convertible_v<T, std::string>, std::string> str(T t)
{
    return t;
}

template <typename T>
std::enable_if_t<!std::is_convertible_v<T, std::string>, std::string> str(T t)
{
    return std::to_string(t);
}

int main()
{
  std::string val = "10";
  auto t = str(43.4);
  std::cout << t+"!" << std::endl;
  return 0;
}
