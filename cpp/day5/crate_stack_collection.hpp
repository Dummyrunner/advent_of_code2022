#pragma once
#include "crate_stack_parser.hpp"
#include "helper_classes.hpp"
#include "vector_utils.hpp"
#include <iostream>
#include <memory>
#include <ostream>
#include <stack>
#include <string>
#include <vector>

using stringVector = std::vector<std::string>;

class CrateStackCollection {
public:
  CrateStackCollection() = default;
  /// @brief ctor, reads prep. init state vector, creates and fills stacks
  /// accordingly
  /// @param vec
  /// @param empty_crate_char
  CrateStackCollection(stringVector vec, char empty_crate_char = '_')
      : m_empty_crate_char{empty_crate_char} {
    auto size_of_first_line{vec[0].size()};
    addNEmptyCrateStacks(size_of_first_line);
    fillInitStateFromVector(vec);
  }
  /// @brief ctor, takes init state vec from parser, creates and fills stacks
  /// accordingly
  /// @param parser
  CrateStackCollection(CrateStackParser &parser) {
    setupEmptyInitStateFromParser(parser);
    fillInitStateFromParser(parser);
  }

  void fillInitStateFromParser(CrateStackParser &parser) {
    auto vec = parser.getPreprocessedInputStateVector();
    fillInitStateFromVector(vec);
  }

  void fillInitStateFromVector(stringVector vec) {
    size_t vecsize{vec.size()};
    for (int iline{(int)vecsize - 1}; iline >= 0; --iline) {
      const auto line{vec[iline]};
      for (std::string::size_type ichar{0}; ichar < line.size(); ++ichar) {
        if (line[ichar] != m_empty_crate_char) {
          char val_to_push{line[ichar]};
          pushToStack(val_to_push, ichar);
        }
      }
    }
  }

  void setupEmptyInitStateFromParser(CrateStackParser &parser) {
    auto vec = parser.getPreprocessedInputStateVector();
    auto vec_first_line{vec[0]};
    auto size_of_first_line{vec_first_line.size()};
    addNEmptyCrateStacks(size_of_first_line);
  }

  void addNEmptyCrateStacks(size_t n) {
    for (size_t i{0}; i < n; ++i) {
      addEmptyCrateStack();
    }
  }

  int numOfStacks() const { return m_stacks.size(); }

  char peekTopVal(const int &stack_idx) const {
    if (m_stacks[stack_idx]->empty()) {
      return m_empty_crate_char;
    }
    auto &crate = m_stacks[stack_idx]->top();
    return crate.getVal();
  }

  void removeTopCrate(const int &stack_idx) {
    if (!inStackIdxRange(stack_idx)) {
      throwAtStackIndexOutOfRange(stack_idx);
    }
    auto &stack = m_stacks[stack_idx];
    stack->pop();
  }

  void pushToStack(const char &val, const int &stack_idx) {
    if (!inStackIdxRange(stack_idx)) {
      throwAtStackIndexOutOfRange(stack_idx);
    }
    Crate next_crate = Crate(val);
    m_stacks[stack_idx]->push(next_crate);
  }

  void moveWholeSubstack(const MoveDirective &move) {
    moveWholeSubstack(move.origin, move.target, move.amount);
  }

  void moveOneByOne(const MoveDirective &move) {
    moveOneByOne(move.origin, move.target, move.amount);
  }

  void moveWholeSubstack(const int &origin, const int &target,
                         const int &amount) {
    if (!inStackIdxRange(origin) || !inStackIdxRange(target)) {
      throwAtStackIndexOutOfRange();
    }
    auto tmp_crate = crateStack();
    for (int i{0}; i < amount; ++i) {
      auto val{peekTopVal(origin)};
      tmp_crate.push(val);
      removeTopCrate(origin);
    }
    while (!tmp_crate.empty()) {
      auto val{(tmp_crate.top()).getVal()};
      pushToStack(val, target);
      tmp_crate.pop();
    }
  }

  void moveOneByOne(const int &origin, const int &target, const int &amount) {
    if (!inStackIdxRange(origin) || !inStackIdxRange(target)) {
      throwAtStackIndexOutOfRange();
    }
    for (int i{0}; i < amount; ++i) {
      moveSingleCrate(origin, target);
    }
  }

  void printTopCrates() {
    for (int i{0}; i < numOfStacks(); ++i) {
      std::cout << peekTopVal(i);
    }
  }

  std::string topCratesToString() {
    std::string str{};
    for (int i{0}; i < numOfStacks(); ++i) {
      str += peekTopVal(i);
    }
    return str;
  }

  void removeAllStacks() { m_stacks.clear(); }
  void removeAllCratesFromStacks() {
    for (auto &stack : m_stacks) {
      while (!stack->empty()) {
        stack->pop();
      }
    }
  }

  void addEmptyCrateStack() {
    std::unique_ptr<crateStack> new_stack = std::make_unique<crateStack>();
    m_stacks.push_back(std::move(new_stack));
  }

private:
  void moveSingleCrate(const int &origin, const int &target) {
    if (!inStackIdxRange(origin) || !inStackIdxRange(target)) {
      throwAtStackIndexOutOfRange();
    }
    auto val{peekTopVal(origin)};
    pushToStack(val, target);
    removeTopCrate(origin);
  }
  bool inStackIdxRange(const int &n) const {
    return !((n < 0) || (n >= numOfStacks()));
  }

  void throwAtStackIndexOutOfRange() {
    throw std::out_of_range("Index out of range:");
  }

  void throwAtStackIndexOutOfRange(int idx) {
    throw std::out_of_range("Index out of range: " + std::to_string(idx));
  }

  std::vector<crateStackPtr> m_stacks{};
  char m_empty_crate_char{'_'};
};
