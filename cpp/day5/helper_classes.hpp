#pragma once

#include <memory>
#include <stack>

class Crate {
public:
  Crate(char ip) : val{ip} {}
  void setVal(char ip) { val = ip; }
  char getVal() { return val; };

private:
  char val{0};
};

using crateStack = std::stack<Crate>;
using crateStackPtr = std::unique_ptr<crateStack>;

struct MoveDirective {
public:
  MoveDirective(int target, int origin, int amount)
      : target{target}, origin{origin}, amount{amount} {}

  int target{};
  int origin{};
  int amount{};
};
