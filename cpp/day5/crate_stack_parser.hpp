#pragma once
#include "helper_classes.hpp"
#include "vector_utils.hpp"
#include <string>
#include <vector>

using stringVector = std::vector<std::string>;

class CrateStackParser {
public:
  CrateStackParser(const std::string &path,
                   const std::string &empty_crate_char = "_")
      : m_filepath_to_parse{path}, m_empty_crate_char{empty_crate_char} {
    assignRawInputs();
    doParsing();
    // utils::printAllVectorEntries(m_move_directives);
  }
  CrateStackParser() = delete;

  void preprocessInitStateInput() {
    // std::vector<std::string> all_lines =
    //     utils::extractFileToLineVector(m_filepath_to_parse);
    // auto two_input_sections = splitStringVectorAtEmptyLine(all_lines);
    // auto init_state_input_lines = two_input_sections[0];

    // std::string enum_line = init_state_input_lines.back();
    // // remove last line enumerating stacks
    // init_state_input_lines.erase(init_state_input_lines.end() - 1);
    // assignRawInputs();
    auto init_state_vec{m_raw_input_state_vector};
    for (auto &line : init_state_vec) {
      replaceCharsInString(' ', '#', line);
      replaceQuadrupleSharp(line);
      replaceSubstring(line, "###", "[" + m_empty_crate_char + "]");
      removeCharFromString('#', line);
      removeBracketsFromString(line);
    }
    // std::cout << "kadsdasdfh\n";
    // utils::printAllVectorEntries(init_state_vec);
    m_preprocessed_input_state_vector = init_state_vec;
  }

  void assignRawInputs() {
    std::vector<std::string> all_lines =
        utils::extractFileToLineVector(m_filepath_to_parse);
    auto two_input_sections = splitStringVectorAtEmptyLine(all_lines);
    std::cout << "huddldi" << std::endl;
    m_raw_input_state_vector = two_input_sections[0];
    m_raw_input_state_vector.erase(m_raw_input_state_vector.end() - 1);
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

  std::vector<MoveDirective> fillMoveDirectivesVector() {
    clearMoveDirectiveVector();
    fillMoveDirectiveVector(m_raw_move_vector);
    return m_move_directives;
  }

  void doParsing() {
    fillMoveDirectivesVector();
    preprocessInitStateInput();
  }
  std::vector<MoveDirective> getMoveDirectivesVector() {
    return m_move_directives;
  }

private:
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

  void fillMoveDirectiveVector(stringVector strvec) {
    for (std::vector<std::string>::size_type iline{0}; iline < strvec.size();
         ++iline) {
      auto next_move_directive{createMoveDirectiveFromInputLine(strvec[iline])};
      m_move_directives.push_back(next_move_directive);
    }
  }

  void clearMoveDirectiveVector() { m_move_directives.clear(); }

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
    auto str_to_be_replaced_len{str_to_be_replaced.size()};
    auto str_to_be_replaced_pos{str.find(str_to_be_replaced)};
    while (str_to_be_replaced_pos != std::string::npos) {
      str.replace(str_to_be_replaced_pos, str_to_be_replaced_len,
                  replacement_str);
      str_to_be_replaced_pos = str.find(str_to_be_replaced);
    }
  }

  /// @brief replace all occurences of "####" in str with "#[_]", to align empty
  /// spaces with filled ones
  /// @param str string to be processed
  void replaceQuadrupleSharp(std::string &str) {
    std::string str_to_be_replaced{"####"};
    std::string replacement_str{"#[_]"};
    replaceSubstring(str, str_to_be_replaced, replacement_str);
  }

  std::string m_filepath_to_parse{};
  std::string m_empty_crate_char{};
  std::vector<MoveDirective> m_move_directives{};
  stringVector m_raw_input_state_vector{};
  stringVector m_raw_move_vector{};
  stringVector m_preprocessed_input_state_vector{};
};
