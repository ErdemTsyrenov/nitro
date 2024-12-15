#include "Rectangle.h"

std::pair<uint32, uint32> GetMaxWidthHeight(const std::vector<Rectangle>& rects) {
  uint32 max_w = 0;
  uint32 max_h = 0;
  for (auto r : rects) {
    max_w = std::max(r.GetX() + r.GetW(), max_w);
    max_w = std::max(r.GetY() + r.GetH(), max_h);
  }
  return {max_w, max_h};
}

int main() {
  Json json = {
      {{"x", 120}, {"y", 200}, {"w", 250}, {"h", 150} },
      {{"x", 140}, {"y", 160}, {"w", 250}, {"h", 100} },
      {{"x", 160}, {"y", 140}, {"w", 350}, {"h", 190} }
  };
  std::vector<Rectangle> rects = parse_json(json);
  auto[max_w, max_h] = GetMaxWidthHeight(rects);
  Table f(max_w, max_h);
  f.Fill(rects);
}