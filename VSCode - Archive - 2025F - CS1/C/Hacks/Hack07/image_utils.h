/*
* Author: Anthony Candelas
* Date: 20OCT2025
* Email: tsallinger2@unl.edu
*
* Description: Header for image manipulation utilities used in Hack7.
* Declares functions to load/save images (wrappers provided), copy images,
* flip horizontally/vertically, and rotate clockwise. Pixel is an RGB struct
* with integer components in [0,255].
*/

#ifndef IMAGE_UTILS_H
#define IMAGE_UTILS_H

#include <stdlib.h>

/**
 * A structure that represents a single pixel value using
 * the RGB (red-blue-green) color model.  Each integer
 * value is in the range [0, 255].
 */
typedef struct {
  int red;
  int green;
  int blue;
} Pixel;

/**
 * Loads an image file specified by the given file path/name.
 * The height and width are indicated in the two pass-by-reference variables.
 * The image is returned as a two-dimensional array of Pixel values
 * of dimension (height x width) where the pixel at [0][0] corresponds to
 * the top-left most pixel value.
 *
 * Note: This wrapper expects the stb_image-based loader already linked.
 *
 * @param filePath input path
 * @param height output pointer for image height (rows)
 * @param width output pointer for image width (cols)
 * @return dynamically allocated Pixel** with contiguous rows (caller must free)
 */
Pixel **loadImage(const char *filePath, int *height, int *width);

/**
 * Saves the given image (height x width) to filePath. This function will
 * write an RGB JPEG (ignores alpha) and the caller is responsible for
 * ensuring the image data is in 0..255.
 *
 * @param filePath destination path
 * @param image Pixel** image (height x width)
 * @param height number of rows
 * @param width number of cols
 */
void saveImage(const char *filePath, Pixel **image, int height, int width);

/**
 * Creates and returns a deep copy of the given (height x width) image.
 * The returned image is a newly allocated Pixel** with contiguous pixel data.
 *
 * @param image source image (may not be NULL if height*width > 0)
 * @param height rows of image
 * @param width cols of image
 * @return newly allocated deep copy or NULL on error
 */
Pixel ** copyImage(Pixel **image, int height, int width);

/**
 * Flips the image horizontally in-place (mirror on vertical axis).
 *
 * @param image image to flip (modified in-place)
 * @param height rows
 * @param width cols
 */
void flipHorizontal(Pixel **image, int height, int width);

/**
 * Flips the image vertically in-place (mirror on horizontal axis).
 *
 * @param image image to flip (modified in-place)
 * @param height rows
 * @param width cols
 */
void flipVertical(Pixel **image, int height, int width);

/**
 * Returns a newly allocated image that is the clockwise 90-degree rotation
 * of the input. The dimensions of the returned image are (width x height).
 *
 * @param image source image
 * @param height rows of source
 * @param width cols of source
 * @return new rotated image or NULL on error
 */
Pixel ** rotateClockwise(Pixel **image, int height, int width);

#endif
