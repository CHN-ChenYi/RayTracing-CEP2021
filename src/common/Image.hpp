#pragma once

struct Image {
  unsigned char *buf;
  int w, h;
  ~Image() {
	  delete[]buf;
  }
};
