/*
 * COPYRIGHT 2013 Alexandre Bique <bique.alexandre@gmail.com>
 */

#define _USE_MATH_DEFINES
#include <math.h>

#include <complex>
#include <iostream>

typedef long double scalar;
typedef std::complex<scalar> point;

const scalar GOLD = 1.6180339887;
const scalar PI = M_PI;
const scalar R1 = 0;
const scalar S1 = 220;
const scalar S2 = 220;
const scalar L1 = 120;
const scalar L2 = 72;
const scalar L3 = 44;
const scalar L4 = 24;
const scalar L5 = 21;
const scalar L6 = 32;
const scalar L7 = 16;
const scalar L8 = 5;
const point  A(217, 235);

point polar(scalar r, scalar teta)
{
  return std::polar<scalar>(r, teta);
}

void sym_rotate_print(bool sym, point p, scalar angle, scalar scale)
{
  angle += PI;

  if (sym)
    p = point(2 * A.real() - p.real(), p.imag());
  p = (p - A) * scale * polar(1, angle) + A;
  std::cout << p.real() << "," << p.imag() << " ";
}

static const char *colors[] = {
  "red",
  "orange",
  "yellow",
  "green",
  "blue",
  "indigo",
  "purple"
};

int main(int argc, char **argv)
{
  point b = A + point(0, R1);
  point c = b + polar(L1, PI / 6);
  point d = c + polar(L2, 5 * PI / 6);
  point e = d + polar(L3, 7 * PI / 6);
  point f = e + polar(L4, 3 * PI / 2);
  point g = f + polar(L5, 11 * PI / 6);
  point h = g + polar(L6, PI / 6);
  point i = h + polar(L7, 5 * PI / 6);
  point j = i + polar(L8, 7 * PI / 6);

  point l0 = A + point(0, S1);
  point l1 = c + polar(L2 / 5, 5 * PI / 6);
  point l2 = l1 + (l0 - l1) * polar(1.0 / 4, 0) + (l0 - l1) * polar(1.0 / 3, - PI / 2);
  point l3 = l1 + (l0 - l1) * polar(3.0 / 4, 0) + (l0 - l1) * polar(1.0 / 6, PI / 2);

  point l4 = A + polar(S2, PI / 6);

  std::cout << "<?xml version=\"1.0\"?>\n"
    "<svg width=\"1000\" height=\"1000\" viewPort=\"0 0 120 120\""
    " version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n"
    "<rect x=\"0\" y=\"0\" width=\"500\" height=\"500\" fill=\"black\"/>";

  int offset = 0;
  for (double scale = 1 / GOLD / GOLD / GOLD / GOLD / GOLD / GOLD;
       scale <= 1; scale *= 1.6, ++offset) {
    for (int x = 0; x < 3; ++x) {
      for (int y = 0; y < 2; ++y) {

        // std::cout << "  <polyline fill=\"none\" stroke=\"black\""
        //   " points=\"";
        // sym_rotate_print(y, b, x * 2 * PI / 3, scale);
        // sym_rotate_print(y, c, x * 2 * PI / 3, scale);
        // sym_rotate_print(y, d, x * 2 * PI / 3, scale);
        // sym_rotate_print(y, e, x * 2 * PI / 3, scale);
        // sym_rotate_print(y, f, x * 2 * PI / 3, scale);
        // sym_rotate_print(y, g, x * 2 * PI / 3, scale);
        // sym_rotate_print(y, h, x * 2 * PI / 3, scale);
        // sym_rotate_print(y, i, x * 2 * PI / 3, scale);
        // sym_rotate_print(y, j, x * 2 * PI / 3, scale);
        // std::cout << "\"/>\n";

        std::cout << "  <path fill=\"none\" stroke=\"" << colors[offset] << "\""
          " stroke-width=\"" << (offset + 1) / GOLD << "\" d=\"M ";
        sym_rotate_print(y, l1, x * 2 * PI / 3, scale);
        std::cout << " C ";
        sym_rotate_print(y, l2, x * 2 * PI / 3, scale);
        sym_rotate_print(y, l3, x * 2 * PI / 3, scale);
        sym_rotate_print(y, l0, x * 2 * PI / 3, scale);
        std::cout << "\"/>\n";

        std::cout << "  <path fill=\"none\" stroke=\"" << colors[6 - offset] << "\""
          " stroke-width=\"" << (offset + 1) / 2.0 << "\" d=\"M ";
        sym_rotate_print(y, l1, x * 2 * PI / 3 + PI / 3, scale);
        std::cout << " C ";
        sym_rotate_print(y, l2, x * 2 * PI / 3 + PI / 3, scale);
        sym_rotate_print(y, l3, x * 2 * PI / 3 + PI / 3, scale);
        sym_rotate_print(y, l0, x * 2 * PI / 3 + PI / 3, scale);
        std::cout << "\"/>\n";
      }
    }
  }
  std::cout << "</svg>";

  return 0;
}
