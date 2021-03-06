#pragma once

#include <vector>

#include "cube/face.hh"
#include "cube/search.hh"
#include "resolve/resolve.hh"

namespace state
{
  class State
  {
    public:
      ~State();

      // Delete copy constructor and assignment constructor because we
      // are using Singleton Design Pattern
      State(const State& s) = delete;
      State& operator =(const State& s) = delete;

      // Getters & setters
      cube::Search& search_get();
      void search_set(cube::Search& s);
      cube::Face& face_get();
      void face_set(cube::Face& s);
      const std::string& face_str_get() const;
      void face_str_set(const std::string& state);
      double compute_time_get() const;
      void compute_time_set(const double d);
      std::string move_get();

      // Get the Singleton
      static State& Instance();

      // Draw on the screen few informations
      void draw_text_data() const;

      // Add a move in the vector (used when draw_ = true)
      void push_move(std::string move);

      // Remove all elements in moves_
      void clear_vector();

      // Get the vector
      std::vector<std::string>& moves_get();

      void sol_set(const std::string& sol);
      void next_move_incr();
      void next_move_decr();
      const char* next_move_get();

    private:
      // Making default constructor private to ensure the Singleton
      State();

    private:
      cube::Search search_;
      cube::Face face_;
      double compute_time_;
      std::vector<std::string> moves_;
      const char* solution_;
      int next_move_;

    public:
      // Enable or disable the drawing of the Rubik's Cube when executing moves
      bool draw_;
      unsigned int waiting_time_;
  };

  // Draw the moves with little animation
  void draw_moves(const std::vector<std::string>& moves,
                  const std::pair<int, int>& size);

} // namespace state
