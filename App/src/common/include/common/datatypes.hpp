#pragma once

struct Pose {
  float x, y, th;
};

struct GridNode {
    float x, y, theta;
    float dist;
    int idx;
};