#include "controller.hh"
#include "cube/cube.hh"
#include "cube/move.hh"
#include "cube/search.hh"
#include "misc/display.hh"
#include "misc/state.hh"

namespace controller
{
  namespace
  {
    void reset_state()
    {
       auto& state = state::State::Instance();
       auto& display = display::Display::Instance();

       state.clear_vector();
       state.compute_time_set(0);
       display.toggle_enable("resolve", true);
       display.toggle_enable("step_by_step", false);
       display.toggle_enable("previous", false);
       display.toggle_enable("next", false);
       display.repaint();
    }

    void
    scramble()
    {
      auto& state = state::State::Instance();
      auto& display = display::Display::Instance();

      reset_state();
      state.draw_ = true;
      state.waiting_time_ = 2000;
      auto& face = state.face_get();
      face.scramble();
      display.toggle_enable("resolve", true);
      display.toggle_enable("step_by_step", true);
      display.repaint();
    }

    void
    resolve()
    {
       auto& state = state::State::Instance();

       state.draw_ = true;
       state.waiting_time_ = 3000;
       auto sol =
         state.search_get().solution(state.face_get(), cube::Search::DEPTH);
       const auto& ret = cube::move::make_moves(state.face_str_get(), sol);
       state.face_str_set(ret);
       reset_state();
    }

    static bool step_by_step_activated = false;

    void
    step_by_step()
    {
      step_by_step_activated = true;
      auto& display = display::Display::Instance();
      display.toggle_enable("next", true);
      display.toggle_enable("resolve", false);
      display.repaint();
    }

    void
    next()
    {
      auto& state = state::State::Instance();
      auto& display = display::Display::Instance();

      if (state.face_str_get() == cube::Cube::solved_state_)
      {
         reset_state();
         return;
      }

      state.draw_ = true;
      state.waiting_time_ = 0;

      if (step_by_step_activated)
      {
        state.sol_set(state.search_get().solution(state.face_get(),
                                                  cube::Search::DEPTH));
        step_by_step_activated = false;
      }

      auto next = state.next_move_get();

      std::cout << "Next move: ";
      const auto& move = cube::move::parse_move(next);
      state.next_move_incr();
      state.next_move_incr();
      if (move.second > 1)
        state.next_move_incr();
      const auto& new_state =
        cube::move::make_move(state.face_str_get(), move);
      state.face_str_set(new_state);
      display.toggle_enable("next", true);
      display.toggle_enable("previous", true);
      display.repaint();
    }

    void
    previous()
    {
      auto& state = state::State::Instance();
      auto& display = display::Display::Instance();

      state.draw_ = true;
      state.waiting_time_ = 0;
      const char* last_move = state.moves_get().back().c_str();
      std::cout << "Previous move: ";
      const auto& move = cube::move::parse_move(last_move);

      unsigned int end = move.second == 2 ? 1 : 3;
      for (unsigned int i = 0; i < end; ++i)
      {
        state.draw_ = false;
        auto new_state = cube::move::make_move(state.face_str_get(), move);
        state.face_str_set(new_state.c_str());
      }
      state.draw_ = true;
      state.moves_get().pop_back();
      state.next_move_decr();
      state.next_move_decr();
      if (move.second > 1)
        state.next_move_decr();

      display.toggle_enable("next", true);
      if (state.moves_get().size() > 0)
       display.toggle_enable("previous", true);
      else
       display.toggle_enable("previous", false);
      display.repaint();
    }
  } // namespace

  void
  start_controller(SDL_Event *event)
  {
    bool done = false;
    while (!done)
    {
      if(SDL_PollEvent(event))
      {
        switch(event->type)
        {
          case SDL_QUIT:
            done = true;
            break;
          case SDL_WINDOWEVENT:
            if(event->window.event == SDL_WINDOWEVENT_RESIZED)
              display::Display::Instance().repaint();
            break;
          case SDL_MOUSEBUTTONUP:
            const auto& check_button =
              display::Display::Instance().is_intersect(event->button.x,
                                                        event->button.y);
            if (check_button == "")
              break;
            else if (check_button.find("scramble") != std::string::npos)
              scramble();
            else if (check_button.find("resolve") != std::string::npos)
              resolve();
            else if (check_button.find("step_by_step") != std::string::npos)
              step_by_step();
            else if (check_button.find("next") != std::string::npos)
              next();
            else if (check_button.find("previous") != std::string::npos)
              previous();
            break;
        }
      }
      SDL_Delay(5);
    }
  }
} // namespace controller
