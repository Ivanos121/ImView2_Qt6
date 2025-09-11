#ifndef CREATE_MOMENT_SIGNAL_BUILDER_H
#define CREATE_MOMENT_SIGNAL_BUILDER_H

#include <vector>
#include <algorithm>

class Create_moment_signal_builder
{
public:
    Create_moment_signal_builder();
    struct Point
    {
        double time;
        double value;
    };

    void addPoint(double time, double value)
    {
        points.push_back({time, value});
        std::sort(points.begin(), points.end(), [](const Point& a, const Point& b)
                  {
                      return a.time < b.time;
                  });
    }

    void clear()
    {
        points.clear();
    }

    double getValue(double t) const
    {
        if (points.empty()) return 0.0;
        if (t <= points.front().time) return points.front().value;
        if (t >= points.back().time) return points.back().value;

        for (size_t i = 0; i + 1 < points.size(); ++i)
        {
            if (t >= points[i].time && t <= points[i+1].time)
            {
                double t0 = points[i].time;
                double t1 = points[i+1].time;
                double v0 = points[i].value;
                double v1 = points[i+1].value;
                double alpha = (t - t0) / (t1 - t0);
                return v0 + alpha*(v1 - v0);
            }
        }
        return 0.0;
    }

    const std::vector<Point>& getPoints() const
    {
        return points;
    }

private:
    std::vector<Point> points;

};

#endif // CREATE_MOMENT_SIGNAL_BUILDER_H
