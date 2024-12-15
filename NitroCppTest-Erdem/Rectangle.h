#ifndef RECTANGLE_H
#define RECTANGLE_H
#include <vector>
#include <string>
#include <optional>
#include <sstream>
#include <iostream>
#include "json.hpp"

using uint32 = unsigned;

struct Rectangle {
  Rectangle() = default;
  Rectangle(uint32 x, uint32 y, uint32 w, uint32 h) 
  : x_begin(x), y_begin(y), x_end(x + w), y_end(y + h) {
  }

  std::optional<Rectangle> Overlap(const Rectangle& other) {
    uint32 new_x_begin = std::max(x_begin, other.x_begin);
    uint32 new_x_end = std::min(x_end, other.x_end);
    if (new_x_end <= new_x_begin) {
      return std::nullopt;
    }
    uint32 new_y_begin = std::max(y_begin, other.y_begin);
    uint32 new_y_end = std::min(y_end, other.y_end);
    if (new_y_end <= new_y_begin) {
      return std::nullopt;
    }
    return Rectangle(new_x_begin, new_y_begin, new_x_end - new_x_begin, new_y_end - new_y_begin);
  }

  bool operator==(const Rectangle& other) const {
    return x_begin == other.x_begin
          && x_end == other.x_end
          && y_begin == other.y_begin
          && y_end == other.y_end; 
  }

  uint32 x_begin, y_begin, x_end, y_end;
};

class SubsetGenerator {
 public:
  SubsetGenerator(uint32 set_size) : set_size_(set_size) {
  }

  void Walk(uint32 rect_idx = 0, const std::vector<uint32>& sub = {}) {
    if (rect_idx == set_size_) {
      if (!sub.empty())
        subsets_.push_back(sub);
      return;
    }
    std::vector<uint32> contains_current(sub);
    contains_current.push_back(rect_idx);
    Walk(rect_idx+1, contains_current);
    Walk(rect_idx+1, sub);
  }

  const std::vector<std::vector<uint32>>& Gen() {
    Walk();
    return subsets_;
  }; 

 private:
  uint32 set_size_ = 10;
  std::vector<std::vector<uint32>> subsets_;
};

class RectangleIntersection {
 public:
  RectangleIntersection(const Rectangle& intersect, const std::vector<uint32>& rects)
  : intersection(intersect), rectangles(rects) {}

  bool operator==(const RectangleIntersection& other) const {
    return intersection == other.intersection 
           && rectangles == other.rectangles;
  };
  void Print() const {
    auto VecToStr = [] (const std::vector<uint32>& rects) {
      std::stringstream s;
      for (uint32 idx : rects) {
        s << idx+1 << " ";
      }
      return s.str();
    };
    auto RectToStr = [] (const Rectangle& rect) {
      std::stringstream s;
      s << "(" << rect.x_begin << "," << rect.y_begin << "), ";
      s << "w=" << rect.x_end - rect.x_begin << ", ";
      s << "h=" << rect.y_end - rect.y_begin << ", ";
      return s.str();
    };
    std::cout << "Between " << VecToStr(rectangles) << "at " << RectToStr(intersection);
  }
 private:
  Rectangle intersection;
  std::vector<uint32> rectangles;
};

std::vector<RectangleIntersection> GetAllIntersections(const std::vector<Rectangle>& rects) {
  std::vector<RectangleIntersection> all_intersections;
  SubsetGenerator gen(rects.size());
  for (auto subset : gen.Gen()) {
    if (subset.size() <= 1) {
      continue;  // Skip if subset contains only one or zero elements
    }
    Rectangle current_intersection = rects[subset[0]];
    bool has_intersection = true;
    for (uint32 i = 1; i < subset.size(); i++) {
      uint32 rect_idx = subset[i];
      auto intersection = current_intersection.Overlap(rects[rect_idx]);
      if (!intersection.has_value()) {
        has_intersection = false;
        break;  // this set of rectangles doesn't intersect
      } 
      current_intersection = intersection.value();
    }
    if (has_intersection) {
      all_intersections.push_back({current_intersection, subset});
    }
  }
  return all_intersections;
}

std::vector<Rectangle> ParseJson(const nlohmann::json& json_data) {
  // using json = nlohmann::json;
  // std::ifstream f(json_path);
  // json json_data = json::parse(f);
  const uint32 max_num_rect = 10;
  std::vector<Rectangle> rectangles;
  uint32 i = 0;
  for (auto rect : json_data["rects"]) {
    uint32 x = rect.at("x").template get<uint32>();
    uint32 y = rect.at("y").template get<uint32>();
    uint32 w = rect.at("w").template get<uint32>();
    uint32 h = rect.at("h").template get<uint32>();
    rectangles.push_back({x, y, w, h});
    i++;
    if (i == max_num_rect) {
      break;
    }
  }
  return rectangles;
}


#endif