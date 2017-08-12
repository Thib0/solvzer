#include <cassert>
#include <iostream>
#include <cube/cube.hh>
#include <cube/search.hh>
#include <detect/detector.hh>
#include <misc/display.hh>
#include <misc/controller.hh>
#include <misc/state.hh>

#define DRAW
int main(int argc, char** argv)
{
  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_Event event;

  auto& dis = display::Display::Instance(&window, &renderer);
  auto face = cube::Face(cube::Cube::solved_state_);
  state::State::Instance().face_set(face);
  dis.set_window_icon();
  dis.repaint();
  controller::start_controller(&event);
  return 0;
  cube::Search search;

  /*auto face = cube::Face(cube::Cube::solved_state_);
  std::cout << face << std::endl;

  //std::string moves =
  //  "L'D2R1F1R1F2L'F'D'F2L'F'R2B'D'F1D'R1D'F'R2B'F2B2U2L1D1B2U'L'";
  face.scramble();

  auto sol = search.solution(face, cube::Search::DEPTH);
  assert(search.ack_solution(face, sol));

  if (argc != 2)
  {
    std::cout << "Usage: ./solvzer path_to_cube" << std::endl;
    return 1;
  }
  detect::Detector d(argv[1]);*/

  SDL_Delay(5000);
  return 0;
}
