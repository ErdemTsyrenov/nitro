#include <fstream>
#include <iostream>
#include "json.hpp"
#include "Rectangle.h"

void PrintOutput(const std::vector<RectangleIntersection>& intersections) {
  std::cout << "Intersections:\n";
  for (const RectangleIntersection& item : intersections) {
    item.Print();
    std::cout << '\n';
  }
}

int main(int argc, char** argv) {
  using nlohmann::json;
  if (argc == 1) {
    std::cerr << "Please, specify path to json\n";
    return 0;
  }
  std::string json_path(argv[1]);
  // Read json
  std::fstream f(json_path);
  json json_data;
  try {
    json_data = json::parse(f);
  }
  catch (json::parse_error& ex) {  // json format is wrong (e.g. missing comma)
      std::cerr << "Json parse error: " << ex.what() << '\n';
      return 0;
  }
  // Extract rectangles from json
  std::vector<Rectangle> rectangles;
  try {
    rectangles = ParseJson(json_data);
  } catch (json::out_of_range& ex) {  // json key is illegal (e.g 'x' coordinate is missing)
    std::cerr << "Json parse error: " << ex.what() << '\n';
    return 0;
  }
  // Calculate intersections
  std::vector<RectangleIntersection> intersections = GetAllIntersections(rectangles);
  PrintOutput(intersections);
}