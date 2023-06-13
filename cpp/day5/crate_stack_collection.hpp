#pragma once

#include "vector_utils.hpp"
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <vector>

using stringVector = std::vector<std::string>;

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

class CrateStackCollection {
public:
  CrateStackCollection(stringVector vec, char empty_crate_char = '_') {
    addNEmptyCrateStacks(vec.size());
    size_t vecsize{vec.size()};
    for (int iline{vecsize - 1}; iline >= 0; --iline) {
      const auto line{vec[iline]};
      for (int ichar{0}; ichar < line.size(); ++ichar) {
        if (line[ichar] != empty_crate_char) {
          char val_to_push{line[ichar]};
          pushToStack(val_to_push, ichar);
        }
      }
    }
  }

  void addEmptyCrateStack() {
    auto new_stack = std::make_unique<crateStack>();
    m_stacks.push_back(std::move(new_stack));
  }

  void addNEmptyCrateStacks(int n) {
    for (int i{0}; i < n; ++i) {
      addEmptyCrateStack();
    }
  }

  int numOfStacks() { return m_stacks.size(); }

  char peekTopVal(int stack_idx) {
    auto &crate = m_stacks[stack_idx]->top();
    return crate.getVal();
  }

  void removeTopCrate(int stack_idx) {
    auto &stack = m_stacks[stack_idx];
    stack->pop();
  }

  void pushToStack(char val, int stack_idx) {
    Crate next_crate = Crate(val);
    m_stacks[stack_idx]->push(next_crate);
  }

  void moveTopFromStackToStack(int origin, int target, int amount) {
    // auto operating_crate = std::make_unique<crateStack>;
    std::cout << "debug --- 0\n";
    auto operating_crate = crateStack();
    for (int i{0}; i < amount; ++i) {
      std::cout << "debug --- 1\n";
      auto val{peekTopVal(origin)};
      std::cout << "debug --- 2\n";
      pushToStack(val, target);
      std::cout << "debug --- 3\n";
      removeTopCrate(origin);
    }
    std::cout << "operating crate size: " << operating_crate.size()
              << std::endl; // SIZE = 0 ?????
    for (int i{0}; i < amount; ++i) {
      std::cout << "debug --- 4\n";
      // NEXT LINE PROBABLY REASON FOR ERROR!
      auto val{(operating_crate.top()).getVal()};
      std::cout << "debug --- 5\n";
      std::cout << "push to stack: " << val << std::endl;
      std::cout << "debug --- 6\n";
      pushToStack(val, target);
      operating_crate.pop();
    }
  }

private:
  bool inStackIdxRange(int n) { return !((n < 0) || (n >= numOfStacks())); }
  // void throwAtStackIndexOutOfRange(int stack_idx) {
  //   std::ostream os;
  //   os << "INDEX ERROR: index " << stack_idx << " out of range!\n";
  //   throw std::out_of_range("Index ");
  // }
  std::vector<crateStackPtr> m_stacks{};
};
