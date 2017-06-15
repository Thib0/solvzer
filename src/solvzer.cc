#include <cassert>
#include <iostream>
#include <cube/search.hh>
#include <detect/detector.hh>
#include <misc/display.hh>

int main(int argc, char** argv)
{
  SDL_Window *window = SDL_CreateWindow("SolvZer", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1280, 680, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  SDL_Renderer *renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  auto display = display::Display(window, renderer);
  //display.setup_background();

  SDL_Event event;
  auto rub = "UUUUUUUUU";
  display.draw_rubiks(rub);
  /*while (true)
  {
    SDL_WaitEvent(&event);
    if(event.window.event == SDL_WINDOWEVENT_CLOSE)
      break;*/
  //}
  SDL_Delay(10000);
  return 0;
  cube::Search search;

  /*auto face = cube::Face(init_state);

  std::cout << face << std::endl;

  auto solution = search.solution(init_state, DEPTH);

  if (!search.ack_solution(init_state, solution))
    std::cout << "Solution is wrong" << std::endl; */


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
