#include <cassert>
#include <iostream>
#include <cube/cube.hh>
#include <cube/search.hh>
#include <detect/detector.hh>
#include <misc/display.hh>
#include <misc/controller.hh>
#include <misc/state.hh>

// temp
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include "detect/displayer.hh"

detect::Displayer displayer("solvzer");

#define DRAW
int main(int argc, char** argv)
{
  //cube::Search search;
  SDL_Window *window = SDL_CreateWindow("SolvZer", SDL_WINDOWPOS_CENTERED,
      SDL_WINDOWPOS_CENTERED,
      1280, 680, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  SDL_Renderer *renderer =  SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  auto display = display::Display(window, renderer);
  //display.setup_background();

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;
  SDL_Event event;

  auto& dis = display::Display::Instance(&window, &renderer);
  auto face = cube::Face(cube::Cube::solved_state_);
  state::State::Instance().face_set(face);
  dis.setup_background();
  dis.draw_rubiks(state::State::Instance().face_str_get());
  dis.setup_ui();
  dis.refresh();
  controller::start_controller(&event);
  return 0;
  cube::Search search;

  /*auto face = cube::Face(cube::Cube::solved_state_);
  std::cout << face << std::endl;

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

  SDL_Delay(5000);
  return 0;
}
