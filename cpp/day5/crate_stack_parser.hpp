#pragma once

#include "crate_stack_collection.hpp"
#include "helper_classes.hpp"
#include "vector_utils.hpp"
#include <regex>
#include <string>
#include <vector>

using stringVector = std::vector<std::string>;

class CrateStackParser {
public:
  CrateStackParser(const std::string &path,
                   const std::string &empty_crate_char = "_")
      : m_filepath_to_parse{path}, m_empty_crate_char{empty_crate_char} {}

  void prepareInitStateInput() {
    std::vector<std::string> all_lines =
        utils::extractFileToLineVector(m_filepath_to_parse);
    auto two_input_sections = splitStringVectorAtEmptyLine(all_lines);
    auto init_state_input_lines = two_input_sections[0];

    std::string enum_line = init_state_input_lines.back();
    // remove last line enumerating stacks
    init_state_input_lines.erase(init_state_input_lines.end() - 1);

    for (auto &line : init_state_input_lines) {
      replaceCharsInString(' ', '#', line);
      replaceQuadrupleSharp(line);
      replaceSubstring(line, "###", "[" + m_empty_crate_char + "]");
      removeCharFromString('#', line);
      removeBracketsFromString(line);
    }
    m_preprocessed_input_state_vector = init_state_input_lines;
    m_raw_move_vector = two_input_sections[1];
  }

  stringVector getPreprocessedInputStateVector() const {
    return m_preprocessed_input_state_vector;
  }

  void dropFirstNCharsOfString(std::string &str, int n) {
    str.replace(str.begin(), str.begin() + n, "");
  }

  std::vector<int> extractIntegersFromString(const std::string &str) const {
    std::vector<int> res{};
    for (std::size_t i{0}; i < str.size(); ++i) {
      auto current_char{str[i]};
      if (std::isdigit(current_char)) {
        int integer_length{1};
        while (integer_length + i < str.size() &&
               std::isdigit(str[i + integer_length])) {
          ++integer_length;
        }
        auto complete_int_substring = str.substr(i, integer_length);
        auto complete_integer = stoi(complete_int_substring);
        res.push_back(complete_integer);
        i += integer_length - 1;
      }
    }
    return res;
  }

  MoveDirective createMoveDirectiveFromInputLine(const std::string &str) {
    auto integer_vec{extractIntegersFromString(str)};
    int amount = integer_vec[0];
    // textual move input starts counting stacks at 1
    // crate_stack_collection starts counting stacks at 0
    int origin = integer_vec[1] - 1;
    int target = integer_vec[2] - 1;

    MoveDirective res = MoveDirective(target, origin, amount);
    return res;
  }

  std::vector<MoveDirective> getMoveDirectivesVector() {
    fillMoveDirectiveVector(m_raw_move_vector);
    return m_move_directives;
  }

private:
  void fillMoveDirectiveVector(stringVector strvec) {
    for (std::vector<std::string>::size_type iline{0}; iline < strvec.size();
         ++iline) {
      auto next_move_directive{createMoveDirectiveFromInputLine(strvec[iline])};
      m_move_directives.push_back(next_move_directive);
    }
  }

  int charAsInt(const char c) {
    int res = c - '0';
    return res;
  }

  std::vector<stringVector>
  splitStringVectorAtEmptyLine(const stringVector &str_vec) const {
    std::vector<stringVector> res;
    stringVector current_vec_to_fill;
    for (size_t i{0}; i < str_vec.size(); ++i) {
      auto current_string = str_vec[i];
      if (current_string == "") {
        res.push_back(current_vec_to_fill);
        current_vec_to_fill.clear();
      } else {
        current_vec_to_fill.push_back(current_string);
      }
    }
    res.push_back(current_vec_to_fill);
    return res;
  }

  void replaceCharsInString(const char &old_char, const char &new_char,
                            std::string &str) {
    for (std::string::size_type i{0}; i < str.size(); ++i) {
      if (str[i] == old_char) {
        str[i] = new_char;
      }
    }
  }

  void removeCharFromString(const char &char_to_remove, std::string &str) {
    str.erase(std::remove(str.begin(), str.end(), char_to_remove), str.end());
  }

  void removeBracketsFromString(std::string &str) {
    removeCharFromString('[', str);
    removeCharFromString(']', str);
  }

  void replaceSubstring(std::string &str, const std::string &str_to_be_replaced,
                        const std::string &replacement_str) {
    str = std::regex_replace(str, std::regex(str_to_be_replaced),
                             replacement_str);
  }

  /// @brief replace all occurences of "####" in str with "#[_]"
  /// @param str string to process
  void replaceQuadrupleSharp(std::string &str) {
    std::string string_to_be_replaced{"####"};
    std::string replacement_str{"#[_]"};
    auto string_to_be_replaced_len{string_to_be_replaced.size()};
    auto quadruple_hashtag_pos{str.find(string_to_be_replaced)};
    while (quadruple_hashtag_pos != std::string::npos) {
      str.replace(quadruple_hashtag_pos, string_to_be_replaced_len,
                  replacement_str);
      quadruple_hashtag_pos = str.find(string_to_be_replaced);
    }
  }

  std::string m_filepath_to_parse{};
  std::string m_empty_crate_char{};
  std::vector<MoveDirective> m_move_directives{};
  stringVector m_raw_input_state_vector{};
  stringVector m_raw_move_vector{};
  stringVector m_preprocessed_input_state_vector{};
};
