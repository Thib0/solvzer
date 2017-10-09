#include <detect/cube_detector.hh>

/* This class handles all the Detectors to recreate the cube from the camera
 * visions. The cameras are created in this order:
 *    Camera t1: TOP 1- Left is Green, Right is Red
 *    Camera t2: TOP 2- Left is Blue, Right is Orange
 *    Camera b1: BOTTOM 1- Left is Orange, Right is Green
 *    Camera b2: BOTTOM 2- Left is Red, Right is Blue
 *
 *  The top facelet is always White, the bottom one is always Yellow.
 *
 *  The Top cameras see the facelets in this order:
 *
 *               3         4
 *              14  1   2   8
 *                 12 0  6
 *                  10 5
 *                  11 7
 *                  13 9
 *
 *  The bottom cameras see the facelets in this order:
 *
 *                  12 3
 *                  11 1
 *                   9 0
 *                10  4  2
 *                 6     5
 *              8          7
 *
 * The cameras see a total of 56 faces, the following are duplicates:
 *    b1 7  - b2 8
 *    b1 8  - b2 7
 *    t1 3  - t2 4
 *    t1 4  - t2 3
 *    b1 3  - t1 14
 *    b1 12 - t2 8
 *    b2 3  - t2 14
 *    b2 12 - t1 8
 */

namespace detect
{
  CubeDetector::CubeDetector()
    : t1_(displayer_, CameraPosition::TOP, START_CHANNEL)
      , t2_(displayer_, CameraPosition::TOP, START_CHANNEL + 1)
      , b1_(displayer_, CameraPosition::BOTTOM, START_CHANNEL + 2)
      , b2_(displayer_, CameraPosition::BOTTOM, START_CHANNEL + 3)
  { }

  std::string CubeDetector::detect_cube()
  {
    std::string result;
    std::vector<int[6]> values(54);

    for (size_t i = 0; i < 10; i++)
    {
      std::cout << "run " << i << "..." << std::endl;
      t1_.update();
      t2_.update();
      b1_.update();
      b2_.update();

      displayer_.display();

      constexpr std::array<int, 54> indexes =
      {
        9, 7, 5, 6, -1 , 6 , 5, 7, 9,
        4, 2, 0, 1, -1, 1, 0, 2, 3,
        10, 11, 13, 12, -1, 11, 14, 10, 9,
        8, 6, 4, 5, -1, 5, 4, 6, 8,
        4, 2, 0, 1, -1, 1, 0, 2, 3,
        10, 11, 13, 12, -1, 11, 14, 10, 9,
      };

      std::vector<Detector*> detectors =
      {
        &t2_, &t2_, &t2_, &t1_, nullptr, &t2_, &t1_, &t1_, &t1_,
        &t2_, &t2_, &t2_, &b2_, nullptr, &t2_, &b2_, &b2_, &t2_,
        &t1_, &t1_, &t1_, &t1_, nullptr, &b2_, &t1_, &b2_, &b2_,
        &b2_, &b2_, &b2_, &b1_, nullptr, &b2_, &b1_, &b1_, &b1_,
        &t1_, &t1_, &t1_, &b1_, nullptr, &t1_, &b1_, &b1_, &t1_,
        &t2_, &t2_, &t2_, &t2_, nullptr, &b1_, &t2_, &b1_, &b1_
      };

      int counter = 0;
      for (size_t i = 0; i < 54; i++)
      {
        if (detectors[i] == nullptr)
          values[i][counter++]++;
        else
          values[i][ detectors[i]->getColors()[ indexes[i] ] ]++;
      }
    }

    std::vector<std::string> c = { "blanc", "bleu", "rouge", "jaune", "vert", "orange" };

    for (size_t i = 0; i < 54; i++)
    {
      std::cout << i << ": ";
      for (size_t j = 0; j < 6; j++)
        std::cout << c[j] << " = " << values[i][j] << ",";
      std::cout << std::endl;
    }

    for (size_t i = 0; i < 54; i++)
    {
      int maxIndex = 0;
      for (size_t j = 1; j < 6; j++)
      {
        if (values[i][j] > values[i][maxIndex])
          maxIndex = j;
      }
      result += cube::get_char_from_color((cube::color)maxIndex);
    }

    return result;
  }
}
