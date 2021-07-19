#pragma once

#include <memory>

struct Image {
  std::unique_ptr<unsigned char[]> buf;
  int w, h;
};
