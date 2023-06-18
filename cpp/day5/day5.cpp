// #include "catch_include.hpp"
#include "crate_stack_collection.hpp"
#include "crate_stack_parser.hpp"
#include "helper_classes.hpp"
#include "vector_utils.hpp"
#include <iostream>
#include <string>
#include <vector>

// build and run
// make clean && make && ../build/day5

class SolverDay5 {

public:
  SolverDay5() = delete;
  SolverDay5(const std::string &input_file_path)
      : m_input_file_path{input_file_path} {
    m_parser = std::make_shared<CrateStackParser>(m_input_file_path);
    m_parser->prepareInitStateInput();
    m_cscA = std::make_unique<CrateStackCollection>(*m_parser);
    m_cscB = std::make_unique<CrateStackCollection>(*m_parser);
  }
  std::string solveA() {
    auto preprocessedInitStateStringVec =
        m_parser->getPreprocessedInputStateVector();

    auto moveDirectivesVector{m_parser->getMoveDirectivesVector()};
    for (std::vector<MoveDirective>::size_type i = 0;
         i < moveDirectivesVector.size(); ++i) {
      m_cscA->moveOneByOne(moveDirectivesVector[i]);
    }
    return m_cscA->topCratesToString();
  }

  std::string solveB() {
    auto preprocessedInitStateStringVec =
        m_parser->getPreprocessedInputStateVector();

    auto moveDirectivesVector{m_parser->getMoveDirectivesVector()};
    for (std::vector<MoveDirective>::size_type i = 0;
         i < moveDirectivesVector.size(); ++i) {
      m_cscB->moveWholeSubstack(moveDirectivesVector[i]);
    }
    return m_cscB->topCratesToString();
  }

private:
  std::shared_ptr<CrateStackParser> m_parser = nullptr;
  std::unique_ptr<CrateStackCollection> m_cscA = nullptr;
  std::unique_ptr<CrateStackCollection> m_cscB = nullptr;
  std::string m_input_file_path{};
};

int main() {
  // const std::string path = "./input_test.txt";
  const std::string path = "./input.txt";

  std::string final_tops_A{};
  std::string final_tops_B{};
  SolverDay5 solver = SolverDay5(path);
  std::cout << "------------------------------\n";
  auto solverSolA{solver.solveA()};
  auto solverSolB{solver.solveB()};
  std::cout << solverSolA << std::endl;
  std::cout << solverSolB << std::endl;
  std::cout << "------------------------------\n";

  CrateStackParser parser = CrateStackParser(path);

  parser.prepareInitStateInput();
  auto preprocessedInitStateStringVec =
      parser.getPreprocessedInputStateVector();

  CrateStackCollection cscA =
      CrateStackCollection(preprocessedInitStateStringVec);
  auto moveDirectivesVector{parser.getMoveDirectivesVector()};

  for (std::vector<MoveDirective>::size_type i = 0;
       i < moveDirectivesVector.size(); ++i) {
    cscA.moveOneByOne(moveDirectivesVector[i]);
  }

  CrateStackCollection cscB =
      CrateStackCollection(preprocessedInitStateStringVec);
  for (std::vector<MoveDirective>::size_type i = 0;
       i < moveDirectivesVector.size(); ++i) {
    cscB.moveWholeSubstack(moveDirectivesVector[i]);
  }

  final_tops_A = cscA.topCratesToString();
  final_tops_B = cscB.topCratesToString();

  std::cout << "EXC 4A:\t" << solverSolA << std::endl;
  std::cout << "EXC 4B:\t" << final_tops_B << std::endl;
}
