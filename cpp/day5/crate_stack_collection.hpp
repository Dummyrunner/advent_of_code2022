#pragma once

#include "vector_utils.hpp"
#include <iostream>
#include <memory>
#include <ostream>
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
  CrateStackCollection(stringVector vec, char empty_crate_char)
      : m_empty_crate_char{empty_crate_char} {
    addNEmptyCrateStacks(vec.size());
    size_t vecsize{vec.size()};
    for (int iline{vecsize - 1}; iline >= 0; --iline) {
      const auto line{vec[iline]};
      for (int ichar{0}; ichar < line.size(); ++ichar) {
        if (line[ichar] != m_empty_crate_char) {
          char val_to_push{line[ichar]};
          pushToStack(val_to_push, ichar);
        }
      }
    }
  }

  CrateStackCollection(stringVector vec) {
    addNEmptyCrateStacks(vec.size());
    size_t vecsize{vec.size()};
    for (int iline{vecsize - 1}; iline >= 0; --iline) {
      const auto line{vec[iline]};
      for (int ichar{0}; ichar < line.size(); ++ichar) {
        if (line[ichar] != m_empty_crate_char) {
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

  char peekTopVal(const int &stack_idx) const {
    if (m_stacks[stack_idx]->empty()) {
      return m_empty_crate_char;
    }
    auto &crate = m_stacks[stack_idx]->top();
    return crate.getVal();
  }

  void removeTopCrate(const int &stack_idx) {
    auto &stack = m_stacks[stack_idx];
    stack->pop();
  }

  void pushToStack(const char &val, const int &stack_idx) {
    Crate next_crate = Crate(val);
    m_stacks[stack_idx]->push(next_crate);
  }
  void moveTopFromStackToStack(const MoveDirective &move) {
    moveTopFromStackToStack(move.origin, move.target, move.amount);
  }

  void moveTopFromStackToStack(const int &origin, const int &target,
                               const int &amount) {
    auto operating_crate = crateStack();
    for (int i{0}; i < amount; ++i) {
      auto val{peekTopVal(origin)};
      operating_crate.push(val);
      removeTopCrate(origin);
    }
    while (!operating_crate.empty()) {
      auto val{(operating_crate.top()).getVal()};
      pushToStack(val, target);
      operating_crate.pop();
    }
  }

private:
  // bool inStackIdxRange(const int &n) const {
  //   return !((n < 0) || (n >= numOfStacks()));
  // }
  // void throwAtStackIndexOutOfRange(int stack_idx = 0) {
  //   // std::ostream os;
  //   // os << "INDEX ERROR: index " << stack_idx << " out of range!\n";
  //   throw std::out_of_range("Index out of range");
  // }
  std::vector<crateStackPtr> m_stacks{};
  char m_empty_crate_char{'_'};
};
