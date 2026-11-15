#pragma once

struct Pose {
  float x, y, th;
};

struct GridNode {
    Pose pose;
    int idx;
};

struct PathNode {
    Pose pose;
    int idx;
};