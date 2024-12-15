#include <cassert>
#include <iostream>
#include "Rectangle.h"

void test_subsets_gen() {
  SubsetGenerator gen(3);
  std::vector<std::vector<uint32>> expected = {
    {0,1,2}, {0,1}, {0,2}, {0}, {1,2}, {1}, {2}
  };
  std::vector<std::vector<uint32>> subsets = gen.Gen();
  assert(subsets == expected);
}

void test_rectangle() {
  { // Simple intersection
    Rectangle r1(0, 0, 10, 5);
    Rectangle r2(1, 2, 10, 5);
    Rectangle expected(1, 2, 9, 3);
    auto result_r1_r2 = r1.Overlap(r2);
    assert(result_r1_r2.has_value());
    assert(result_r1_r2.value() == expected);
    auto result_r2_r1 = r2.Overlap(r1);
    assert(result_r2_r1.has_value());
    assert(result_r2_r1.value() == expected); 
  }
  { // No intersection
    Rectangle r1(0, 0, 10, 5);
    Rectangle r2(10, 5, 10, 10);
    auto result_r1_r2 = r1.Overlap(r2);
    assert(!result_r1_r2.has_value()); 
    auto result_r2_r1 = r2.Overlap(r1);
    assert(!result_r2_r1.has_value());
  }
  { // First contains second
    Rectangle r1(0, 0, 10, 5);
    Rectangle r2(1, 1, 2, 2);
    Rectangle expected(1, 1, 2, 2);
    auto result_r1_r2 = r1.Overlap(r2);
    assert(result_r1_r2.has_value()); 
    assert(result_r1_r2.value() == expected);
  }
  { // Equal rectangles
    Rectangle r1(0, 0, 10, 5);
    Rectangle r2(0, 0, 10, 5);
    Rectangle expected(0, 0, 10, 5);
    auto result_r1_r2 = r1.Overlap(r2);
    assert(result_r1_r2.has_value()); 
    assert(result_r1_r2.value() == expected);
  }
}

void test_all_intersections() {
  { // Test from spec
    std::vector<Rectangle> rect{
      {100, 100, 250, 80},
      {120, 200, 250, 150},
      {140, 160, 250, 100},
      {160, 140, 350, 190},
    };
    std::vector<RectangleIntersection> expected{
      {{160, 160, 190, 20}, {0,2,3}},
      {{140, 160, 210, 20}, {0,2}},
      {{160, 140, 190, 40}, {0,3}},
      {{160, 200, 210, 60}, {1,2,3}},
      {{140, 200, 230, 60}, {1,2}},
      {{160, 200, 210, 130}, {1,3}},
      {{160, 160, 230, 100}, {2,3}},
    };
    assert(expected == GetAllIntersections(rect));
  }
  { // No intersections
    std::vector<Rectangle> rect{
      {100, 100, 250, 80},
      {0, 0, 50, 50},
      {70, 60, 25, 25},
      {100, 500, 350, 190},
    };
    std::vector<RectangleIntersection> expected{};
    assert(expected == GetAllIntersections(rect));
  }
  { // All rectangles have intersections
    std::vector<Rectangle> rect{
      {0, 0, 10, 5},
      {5, 2, 10, 5},
      {1, 4, 8, 15},
    };
    std::vector<RectangleIntersection> expected{
      {{5, 4, 4, 1}, {0,1,2}},
      {{5, 2, 5, 3}, {0,1}},
      {{1, 4, 8, 1}, {0,2}},
      {{5, 4, 4, 3}, {1,2}},
    };
    assert(expected == GetAllIntersections(rect));
  }
}

void test_parse_json() {
  using json = nlohmann::json;
  auto json_data = json::parse(R"({
    "rects": [
      {"x": 100, "y": 100, "w": 250, "h": 80 },
      {"x": 120, "y": 200, "w": 250, "h": 150 },
      {"x": 140, "y": 160, "w": 250, "h": 100 },
      {"x": 160, "y": 140, "w": 350, "h": 190 }
      ]
    })"
  );
  std::vector<Rectangle> expected{
    {100, 100, 250, 80},
    {120, 200, 250, 150},
    {140, 160, 250, 100},
    {160, 140, 350, 190},
  };
  assert(expected == ParseJson(json_data));
}

int main() {
  test_subsets_gen();
  test_rectangle();
  test_all_intersections();
  test_parse_json();
  std::cout << "Success!\n";
}