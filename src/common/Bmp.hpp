#pragma once
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <vector>

#include "Vector.hpp"

struct RGBColor {
  uint8_t b, g, r;
  RGBColor &operator=(const Vector &other) {
    r = other.x;
    g = other.y;
    b = other.z;
    return *this;
  }
};

struct Bitmap {
  std::vector<std::vector<RGBColor>> rgb_;
  std::vector<RGBColor> &operator[](int index) { return rgb_[index]; }
  void Resize(const int height, const int width) {
    auto old_height = rgb_.size();
    rgb_.resize(height);
    for (int32_t i = old_height; i < height; i++) rgb_[i].resize(width);
  }
};

struct BMPHeader {
  uint32_t size, reserved, offbits;
  void write(std::ofstream &file) const {
    const uint8_t type[2] = {0x42, 0x4D};
    file.write((char *)&type, sizeof(type[0]) * 2);
    file.write((char *)this, sizeof(BMPHeader));
  }
};

struct DIBHeader {
  int32_t width, height;
  uint16_t planes, bit_count;
  uint32_t compression, size_image;
  int32_t x_pels_per_meter, y_pels_per_meter;  // in ppm
  uint32_t clr_used, clr_important;
  int32_t width_abs, height_abs;
  void write(std::ofstream &file) const {
    const uint32_t size = 40;
    file.write((char *)&size, sizeof(size));
    file.write((char *)&width, size - sizeof(size));
  }
};

// bottom-left is the origin
class BMP {
  BMPHeader bmp_header_;
  DIBHeader dib_header_;
  // std::vector<RGBColor> palette_;
  Bitmap bitmap_;

 public:
  BMP() {
    memset(&bmp_header_, 0, sizeof(bmp_header_));
    memset(&dib_header_, 0, sizeof(dib_header_));
  }
  ~BMP() {}

  Bitmap &bitmap() { return bitmap_; }

  void write(const std::string &filename) {
    std::ofstream file(filename, std::ios_base::binary);
    if (!file) throw std::runtime_error("Cannot open the image file.");

    dib_header_.bit_count = 24;
    dib_header_.size_image =
        dib_header_.bit_count / 8 * dib_header_.height_abs *
        (dib_header_.width_abs % 4 + dib_header_.width_abs);
    bmp_header_.size = 54 + dib_header_.size_image;
    bmp_header_.reserved = 0x0000;
    bmp_header_.offbits = 54;
    bmp_header_.write(file);

    dib_header_.width = dib_header_.width_abs;
    dib_header_.height = dib_header_.height_abs;
    dib_header_.planes = 1;
    dib_header_.compression = 0;
    dib_header_.x_pels_per_meter = 10000;  // TODO: choose a reasonable value
    dib_header_.y_pels_per_meter = 10000;  // TODO: choose a reasonable value
    dib_header_.clr_used = 0;
    dib_header_.clr_important = 0;
    dib_header_.write(file);

    // write image data
    const size_t line_size = dib_header_.width_abs * dib_header_.bit_count / 8;
    const size_t padding_size = (4 - line_size % 4) % 4;
    uint8_t *padding = new uint8_t[padding_size];
    memset(padding, 0, padding_size);
    file.seekp(bmp_header_.offbits);
    for (int i = 0; i < dib_header_.height_abs; i++) {
      file.write((char *)bitmap_[i].data(), line_size);
      file.write((char *)padding, padding_size);
    }
    delete padding;

    file.close();
  }

  void Resize(const int32_t height, const int32_t width) {
    dib_header_.height_abs = height;
    dib_header_.width_abs = width;
    bitmap_.Resize(height, width);
  }
};

void WriteBmp(const std::string &filename, const int32_t &height,
              const int32_t &width, const Vector *const bitmap) {
  BMP image;
  image.Resize(height, width);
  auto &bmp_bitmap = image.bitmap();
  for (int32_t i = 0; i < height; i++) {
    for (int32_t j = 0; j < width; j++)
      bmp_bitmap[height - 1 - i][j] = bitmap[i * width + j];
  }
  image.write(filename);
}
