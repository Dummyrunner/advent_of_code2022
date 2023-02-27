#include "vector_utils.hpp"
#include <iostream>
#include <sstream>
#include <string>

// build and run:
// g++ -I ./common ./day2/day2.cpp -o ./build/day2 && ./build/day2

std::pair<char, char> splitCharPairSeparatedBy(std::string str,
                                               char separator_char) {
  std::string first_char_as_string;
  std::string second_char_as_string;
  std::pair<char, char> res_pair;
  std::stringstream sstr(str);
  getline(sstr, first_char_as_string, separator_char);
  getline(sstr, second_char_as_string, separator_char);
  res_pair.first = first_char_as_string[0];
  res_pair.second = second_char_as_string[0];
  return res_pair;
}

enum RockPaperScissors { kRock = 0, kPaper, kScissors, kInvalid = 1000 };
enum Reward { kLoss = 0, kDraw = 3, kWin = 6 };

RockPaperScissors getMoveFromChar(const char &input_char) {
  try {
    if (input_char == 'A' || input_char == 'X') {
      return RockPaperScissors::kRock;
    } else if (input_char == 'B' || input_char == 'Y') {
      return RockPaperScissors::kPaper;
    } else if (input_char == 'C' || input_char == 'Z') {
      return RockPaperScissors::kScissors;
    } else {
      throw input_char;
    }
  } catch (char wrong_char) {
    std::cerr << "char is not valid: " << wrong_char;
    return RockPaperScissors::kInvalid;
  }
}

int rewardFromOwnMoveOpponentMove(RockPaperScissors own_move,
                                  RockPaperScissors opponent_move) {
  int reward_matrix[3][3] = {{4, 8, 3}, {1, 5, 9}, {7, 2, 6}};
  return reward_matrix[opponent_move][own_move];
}

int main() {
  std::string path = "./day2/input_test.txt";
  // std::string path = "./day2/input.txt";

  std::vector<std::string> lines = extractFileToLineVector(path);
  int total_score{0};
  for (std::string line : lines) {
    auto letter_pair = splitCharPairSeparatedBy(line, ' ');
    RockPaperScissors own_move = getMoveFromChar(letter_pair.second);
    RockPaperScissors opponent_move = getMoveFromChar(letter_pair.first);
    total_score += rewardFromOwnMoveOpponentMove(own_move, opponent_move);
  }
  std::cout << "EXC 1A:\t" << total_score << std::endl;
}
