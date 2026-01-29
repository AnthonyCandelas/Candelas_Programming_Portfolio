/*
* Author: Anthony Candelas
* Date: 20OCT2025
* Email: tsallinger2@unl.edu
*
* Description: Image utilities implementation for Hack7. Implements deep copy,
* horizontal/vertical flips, and clockwise rotation. Uses contiguous memory
* layout for returned images so the provided loader/writer conventions remain
* compatible.
*/

#include <stdlib.h>
#include <stdio.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include "image_utils.h"

Pixel **loadImage(const char *filePath, int *height, int *width) {
  int x,y,n;
  unsigned char *data = stbi_load(filePath, &x, &y, &n, 4); //4 = RGBA forced
  *height = y;
  *width = x;

  Pixel **image = (Pixel **)malloc(sizeof(Pixel *) * y);
  image[0] = (Pixel *)malloc(sizeof(Pixel) * (y * x));
  for(int i=1; i<y; i++) {
    image[i] = (*image + (x * i));
  }

  int rowIndex = 0;
  int colIndex = 0;
  for(int i=0; i<(x * y * 4); i+=4) {
      image[rowIndex][colIndex].red   = data[i+0];
      image[rowIndex][colIndex].green = data[i+1];
      image[rowIndex][colIndex].blue  = data[i+2];
      colIndex++;
      if(colIndex == x) {
        rowIndex++;
        colIndex=0;
      }
  }
  stbi_image_free(data);
  return image;
}

void saveImage(const char *fileName, Pixel **image, int height, int width) {

  unsigned char *data = (unsigned char *) malloc((size_t)height * (size_t)width * 3);
  int x = 0;
  for(int i=0; i<height; i++) {
    for(int j=0; j<width; j++) {
      data[x+0] = (unsigned char) image[i][j].red;
      data[x+1] = (unsigned char) image[i][j].green;
      data[x+2] = (unsigned char) image[i][j].blue;
      x+=3;
    }
  }
  stbi_write_jpg(fileName, width, height, 3, data, 100);
  free(data);
  return;
}

Pixel ** copyImage(Pixel **image, int height, int width) {
  if (height <= 0 || width <= 0) return NULL;
  if (image == NULL) return NULL;

  Pixel **out = (Pixel **) malloc(sizeof(Pixel *) * (size_t)height);
  if (out == NULL) return NULL;
  out[0] = (Pixel *) malloc(sizeof(Pixel) * (size_t)height * (size_t)width);
  if (out[0] == NULL) {
    free(out);
    return NULL;
  }
  for (int r = 1; r < height; r++) out[r] = out[0] + (r * width);

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      out[i][j] = image[i][j];
    }
  }
  return out;
}

void flipHorizontal(Pixel **image, int height, int width) {
  if (height <= 0 || width <= 0) return;
  if (image == NULL) return;

  for (int r = 0; r < height; r++) {
    for (int c = 0, d = width - 1; c < d; c++, d--) {
      Pixel tmp = image[r][c];
      image[r][c] = image[r][d];
      image[r][d] = tmp;
    }
  }
  return;
}

void flipVertical(Pixel **image, int height, int width) {
  if (height <= 0 || width <= 0) return;
  if (image == NULL) return;

  for (int r = 0, s = height - 1; r < s; r++, s--) {
    Pixel *tmp = image[r];
    image[r] = image[s];
    image[s] = tmp;
  }
  return;
}

Pixel ** rotateClockwise(Pixel **image, int height, int width) {
  if (height <= 0 || width <= 0) return NULL;
  if (image == NULL) return NULL;

  Pixel **out = (Pixel **) malloc(sizeof(Pixel *) * (size_t)width);
  if (out == NULL) return NULL;
  out[0] = (Pixel *) malloc(sizeof(Pixel) * (size_t)width * (size_t)height);
  if (out[0] == NULL) {
    free(out);
    return NULL;
  }
  for (int r = 1; r < width; r++) out[r] = out[0] + (r * height);

  for (int r = 0; r < height; r++) {
    for (int c = 0; c < width; c++) {
      int nr = c;
      int nc = (height - 1) - r;
      out[nr][nc] = image[r][c];
    }
  }

  return out;
}
