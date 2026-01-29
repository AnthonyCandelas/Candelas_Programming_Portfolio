#include <stdio.h>
#include <stdlib.h>

/*
 * Author: Anthony Candelas
 * Date: 09OCT2025
 * Email: tsallinger2@unl.edu
 *
 * Description: Header file defining RGB structure, ColorType enumeration,
 * and function prototypes for color transformations, including grayscale,
 * sepia, and RGB↔CMYK conversions using pass-by-reference.
 */

#ifndef COLORUTILS_H
#define COLORUTILS_H

typedef enum {
    GRAYSCALE,
    SEPIA
} ColorType;

typedef struct {
    int red;
    int green;
    int blue;
} RGB;

/**
 * Converts an RGB color to CMYK representation.
 *
 * @param r Red component (0–255)
 * @param g Green component (0–255)
 * @param b Blue component (0–255)
 * @param c Pointer to store cyan value (0–1)
 * @param m Pointer to store magenta value (0–1)
 * @param y Pointer to store yellow value (0–1)
 * @param k Pointer to store black key value (0–1)
 * @return 0 if successful, non-zero for errors
 */
int rgbToCMYK(int r, int g, int b, double *c, double *m, double *y, double *k);

/**
 * Converts a CMYK color to RGB representation.
 *
 * @param c Cyan component (0–1)
 * @param m Magenta component (0–1)
 * @param y Yellow component (0–1)
 * @param k Black key component (0–1)
 * @param r Pointer to store red value (0–255)
 * @param g Pointer to store green value (0–255)
 * @param b Pointer to store blue value (0–255)
 * @return 0 if successful, non-zero for errors
 */
int cmykToRGB(double c, double m, double y, double k, int *r, int *g, int *b);

void applyColorFilter(RGB *color, ColorType type);
void applyGrayscale(RGB *color);
void applySepia(RGB *color);

#endif
