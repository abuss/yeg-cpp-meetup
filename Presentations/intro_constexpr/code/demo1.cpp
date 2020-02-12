int main(int argc, const char** argv) {
  constexpr int a = 10;
  const int b = 10;

  const int c = 10 + a;
  const int d = 10 + b;

  constexpr int e = 10 + a;
  constexpr int f = 10 + b;
}
