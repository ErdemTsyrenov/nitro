#include <fstream>
#include <iostream>
#include "json.hpp"
#include "Rectangle.h"

void PrintOutput(const std::vector<RectangleIntersection>& intersections) {
  std::cout << "Intersections\n";
  for (const RectangleIntersection& item : intersections) {
    item.Print();
    std::cout << '\n';
  }
}

int main(int argc, char** argv) {
  using nlohmann::json;
  std::string json_path(argv[1]);
  std::fstream f(json_path);
  auto json_data = json::parse(f);
  std::vector<Rectangle> rectangles = ParseJson(json_data);
  std::vector<RectangleIntersection> intersections = GetAllIntersections(rectangles);
  PrintOutput(intersections);
}