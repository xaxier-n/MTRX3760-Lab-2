//-----------------------------------------------------------------------------
// polygon_plugins.cpp
//
// Square and Triangle are the tutorial's original example plugins, unchanged.
// House is the addition: modelled as a square base with an equilateral-
// triangle roof, where the roof's side length equals the base's side length,
// so a single side_length parameter still fully determines the whole shape.
// It's implemented by composing a Square and a Triangle member and summing
// their areas, rather than deriving a new closed-form formula, reusing logic
// that's already implemented and tested elsewhere in this file.
//-----------------------------------------------------------------------------
#include <polygon_base/regular_polygon.hpp>
#include <pluginlib/class_list_macros.hpp>
#include <cmath>

namespace polygon_plugins
{
  class Square : public polygon_base::RegularPolygon
  {
    public:
      void initialize(double side_length) override
      {
        side_length_ = side_length;
      }

      double area() override
      {
        return side_length_ * side_length_;
      }

    protected:
      double side_length_;
  };

  class Triangle : public polygon_base::RegularPolygon
  {
    public:
      void initialize(double side_length) override
      {
        side_length_ = side_length;
      }

      double area() override
      {
        return 0.5 * side_length_ * getHeight();
      }

      double getHeight()
      {
        return sqrt((side_length_ * side_length_) - ((side_length_ / 2) * (side_length_ / 2)));
      }

    protected:
      double side_length_;
  };

  class House : public polygon_base::RegularPolygon
  {
    public:
    void initialize(double side_length) override
    {
      square_.initialize(side_length);
      triangle_.initialize(side_length);
    }

    double area() override
    {
      return square_.area() + triangle_.area();
    }

    protected:
      Square square_;
      Triangle triangle_;
  };
}

PLUGINLIB_EXPORT_CLASS(polygon_plugins::Square, polygon_base::RegularPolygon)
PLUGINLIB_EXPORT_CLASS(polygon_plugins::Triangle, polygon_base::RegularPolygon)
PLUGINLIB_EXPORT_CLASS(polygon_plugins::House, polygon_base::RegularPolygon)
