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
    // int num_of_stacks = vec[0].size();

    // for (int i{0}; i < num_of_stacks; ++i) {
    //   auto new_stack_to_add = std::make_unique<crateStack>();
    //   m_stacks.push_back(new_stack_to_add);
    // }
    std::cout << "------------------------" << std::endl;
    utils::printAllVectorEntries(vec);
    std::cout << "------------------" << std::endl;
    size_t vecsize{vec.size()};
    // std::cout << "constr. of cratelist\n";
    for (int iline{vecsize - 1}; iline >= 0; --iline) {
      const auto line{vec[iline]};
      // std::cout << line << std::endl;
      std::cout << "next line: ( i = " << iline << ") " << line << std::endl;
      for (int ichar{0}; ichar < line.size(); ++ichar) {
        if (line[ichar] != empty_crate_char) {
          char val_to_push{line[ichar]};
          std::cout << "val to push: " << val_to_push << std::endl;
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

  void pushToStack(char val, int stack_idx) {
    Crate next_crate = Crate(val);
    m_stacks[stack_idx]->push(next_crate);
  }

private:
  std::vector<crateStackPtr> m_stacks{};
};
