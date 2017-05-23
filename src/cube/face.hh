#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <map>

#include <cube/color.hh>
#include <cube/corner.hh>
#include <cube/edge.hh>
#include <cube/facelet.hh>
#include <misc/contract.hh>

namespace cube
{

  class Face
  {
    public:
      Face() = default;
      Face(const std::string& cube);

      std::string scramble();

      void face_set(const std::string& state);

      std::ostream& dump_row(std::ostream& o, int i, int j, int x) const;

      /// Map the corner positions to the facelet poisitions.
      /// Example: corner_facelet[URF][0] gives the facelet position in
      /// the `URF` corner.
      static constexpr facelet corner_facelet_[8][3] =
      {
        { U9, R1, F3 }, { U7, F1, L3 }, { U1, L1, B3 }, { U3, B1, R3 },
        { D3, F9, R7 }, { D1, L9, F7 }, { D7, B9, L7 }, { D9, R9, B7 }
      };

      /// Map the edge positions to the facelet positions.
      /// Example: edge_facelet[UR][0] gives the facelet position in the
      /// `UR` edge.
      static constexpr facelet edge_facelet_[12][2] =
      {
        { U6, R2 }, { U8, F2 }, { U4, L2 }, { U2, B2 }, { D6, R8 }, { D2, F8 },
        { D4, L8 }, { D8, B8 }, { F6, R4 }, { F4, L6 }, { B6, L4 }, { B4, R6 }
      };

      /// Map the corner positions to the facelet colors.
      static constexpr color corner_color_[8][3] =
      {
        { U, R, F }, { U, F, L }, { U, L, B }, { U, B, R },
        { D, F, R }, { D, L, F }, { D, B, L }, { D, R, B }
      };

      /// Map the edge positions to the facelet colors.
      static constexpr color edge_color_[12][2] =
      {
        { U, R }, { U, F }, { U, L }, { U, B }, { D, R }, { D, F },
        { D, L }, { D, B }, { F, R }, { F, L }, { B, L }, { B, R }
      };

      std::array<color, 54> face_ =
      {{
         U, U, U, U, U, U, U, U, U,
         R, R, R, R, R, R, R, R, R,
         F, F, F, F, F, F, F, F, F,
         D, D, D, D, D, D, D, D, D,
         L, L, L, L, L, L, L, L, L,
         B, B, B, B, B, B, B, B, B
      }};

      const std::string& face_str_get() const;
      void face_str_set(const std::string& state);

    private:
      std::string face_str_;
  };

  std::ostream& operator<<(std::ostream& o, const Face& f);
  char clr_to_chr(color c);

} // namespace cube

#include <cube/face.hxx>
