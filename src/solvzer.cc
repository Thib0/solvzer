#include <cassert>
#include <iostream>

#include <cube/search.hh>
#include <detect/detector.hh>


// temp
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "detect/displayer.hh"

detect::Displayer displayer("solvzer");

int main(int argc, char** argv)
{
  //cube::Search search;
  /*auto face = cube::Face(init_state);

  std::cout << face << std::endl;

  auto solution = search.solution(init_state, DEPTH);

  if (!search.ack_solution(init_state, solution))
    std::cout << "Solution is wrong" << std::endl; */


  //auto face = cube::Face(cube::Cube::solved_state_);
  //std::cout << face << std::endl;

  //std::string moves =
  //  "L'D2R1F1R1F2L'F'D'F2L'F'R2B'D'F1D'R1D'F'R2B'F2B2U2L1D1B2U'L'";
  //face.scramble();

  //auto sol = search.solution(face, cube::Search::DEPTH);
  //assert(search.ack_solution(face, sol));

  detect::Detector d(displayer, detect::CameraPosition::TOP);
  while (true)
  {
    d.update();
    displayer.display();
  }

  return 0;
}
