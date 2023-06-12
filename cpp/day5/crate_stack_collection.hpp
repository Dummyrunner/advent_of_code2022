#pragma once

#include <stack>
#include <vector>

class Crate {
public:
  Crate(int ip) : val{ip} {}
  void setVal(int ip) { val = ip; }
  int getVal() { return val; };

private:
  int val{0};
};
using crateStack = std::vector<std::stack<Crate>>;

struct MoveDirective {
public:
  MoveDirective(int target, int origin, int amount)
      : target{target}, origin{origin}, amount{amount} {}

  int target{};
  int origin{};
  int amount{};
};

class CrateStackCollection {

private:
  std::vector<crateStack> m_stacks{};
};
