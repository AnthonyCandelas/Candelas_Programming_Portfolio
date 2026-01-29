#include "colorUtils.h"
#include <math.h>

/*
 * Author: Anthony Candelas
 * Date: 09OCT2025
 * Email: tsallinger2@unl.edu
 *
 * Description: Implements color transformation functions including
 * grayscale, sepia, and RGB↔CMYK conversions. Handles pass-by-reference
 * operations, pointer validation, and error conditions.
 */

int rgbToCMYK(int r, int g, int b, double *c, double *m, double *y, double *k) {
    if (!c || !m || !y || !k) return 1; // Null pointer error
    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255) return 2; // Out-of-range error

    double rPrime = r / 255.0;
    double gPrime = g / 255.0;
    double bPrime = b / 255.0;

    *k = 1.0 - fmax(fmax(rPrime, gPrime), bPrime);

    if (*k == 1.0) { // black edge case
        *c = *m = *y = 0.0;
        return 0;
    }

    *c = (1.0 - rPrime - *k) / (1.0 - *k);
    *m = (1.0 - gPrime - *k) / (1.0 - *k);
    *y = (1.0 - bPrime - *k) / (1.0 - *k);

    return 0;
}

int cmykToRGB(double c, double m, double y, double k, int *r, int *g, int *b) {
    if (!r || !g || !b) return 1; // Null pointer error
    if (c < 0 || c > 1 || m < 0 || m > 1 || y < 0 || y > 1 || k < 0 || k > 1) return 2; // Out-of-range error

    *r = (int)round(255.0 * (1.0 - c) * (1.0 - k));
    *g = (int)round(255.0 * (1.0 - m) * (1.0 - k));
    *b = (int)round(255.0 * (1.0 - y) * (1.0 - k));

    return 0;
}

void applyGrayscale(RGB *color) {
    if (color == NULL) return;

    int gray = (int)(0.3 * color->red + 0.59 * color->green + 0.11 * color->blue);
    color->red = gray;
    color->green = gray;
    color->blue = gray;
}

void applySepia(RGB *color) {
    if (color == NULL) return;

    int originalRed = color->red;
    int originalGreen = color->green;
    int originalBlue = color->blue;

    int sepiaRed = (int)(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
    int sepiaGreen = (int)(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
    int sepiaBlue = (int)(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

    color->red = sepiaRed > 255 ? 255 : sepiaRed;
    color->green = sepiaGreen > 255 ? 255 : sepiaGreen;
    color->blue = sepiaBlue > 255 ? 255 : sepiaBlue;
}

void applyColorFilter(RGB *color, ColorType type) {
    if (color == NULL) return;

    switch (type) {
        case GRAYSCALE:
            applyGrayscale(color);
            break;
        case SEPIA:
            applySepia(color);
            break;
        default:
            break;
    }
}
