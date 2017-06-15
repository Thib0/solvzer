#include <cassert>
#include <iostream>
#include <cube/search.hh>
#include <detect/detector.hh>
#include <misc/display.hh>

int main(int argc, char** argv)
{
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_Event event;
  auto display = display::Display::Instance(&window, &renderer);

  cube::Search search;


  auto face = cube::Face(cube::Cube::solved_state_);
  std::cout << face << std::endl;

  //std::string moves =
  //  "L'D2R1F1R1F2L'F'D'F2L'F'R2B'D'F1D'R1D'F'R2B'F2B2U2L1D1B2U'L'";
  face.scramble();

  auto sol = search.solution(face, cube::Search::DEPTH);
  assert(search.ack_solution(face, sol));

  /*if (argc != 2)
  {
    std::cout << "Usage: ./solvzer path_to_cube" << std::endl;
    return 1;
  }
  detect::Detector d(argv[1]);*/

  return 0;
}
