#pragma once

struct Image {
  unsigned char *buf;
  int w, h;
  Image() { 
	  buf = nullptr; 
  }
  ~Image() {
    if (buf)
	  delete[]buf;
  }
};
