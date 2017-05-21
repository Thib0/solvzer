#pragma once

#include <cube/coord.hh>
#include <cube/cube.hh>
#include <cube/face.hh>

namespace cube
{

  void init_statics();

  class Search
  {
    public:
      Search();

      /// \param facelets   cube definition string
      /// \param max_depth  maximal allowed maneuver length
      std::string solution(std::string facelets, int max_depth);

    private:
      int total_depth(int depth_phase1, int max_depth);
      std::string solution_to_string(int length);

      std::array<int, 31> axis_;
      std::array<int, 31> power_;
      std::array<int, 31> flip_;
      std::array<int, 31> twist_;
      std::array<int, 31> slice_;
      std::array<int, 31> parity_;
      std::array<int, 31> URF_to_DLF_;
      std::array<int, 31> FR_to_BR_;
      std::array<int, 31> UR_to_UL_;
      std::array<int, 31> UB_to_DF_;
      std::array<int, 31> UR_to_DF_;
      std::array<int, 31> min_depth_phase1_;
      std::array<int, 31> min_depth_phase2_;
  };

} // namespace cube
