/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 03NOV2025
 * Lab/Task: Hack06 - Color Utilities
 *
 * Description:
 * Color utility methods for applying grayscale and sepia filters to RGB pixel
 * values. Functions operate on RGB objects and document behavior in the header.
 */

package unl.soc;

public class ColorUtils {

    /**
     * Enumeration representing available color filter types.
     */
    public enum ColorFilter {
        GRAYSCALE,
        SEPIA
    }

    /**
     * Represents an RGB color with public fields for red, green, and blue.
     * Values are expected to be in the range [0, 255].
     */
    public static class RGB {
        public int red;
        public int green;
        public int blue;

        /**
         * Constructs a new RGB object with the specified color components.
         *
         * @param red   red component (0–255)
         * @param green green component (0–255)
         * @param blue  blue component (0–255)
         */
        public RGB(int red, int green, int blue) {
            this.red = red;
            this.green = green;
            this.blue = blue;
        }
    }

    /**
     * Applies a specified color filter to the given RGB color.
     * The transformation is done in place (pass-by-reference).
     *
     * @param rgb     RGB color object to be modified
     * @param filter  color filter to apply (GRAYSCALE or SEPIA)
     */
    public static void applyFilter(RGB rgb, ColorFilter filter) {
        if (rgb == null || filter == null) {
            return;
        }

        switch (filter) {
            case GRAYSCALE:
                applyGrayscale(rgb);
                break;
            case SEPIA:
                applySepia(rgb);
                break;
        }
    }

    /**
     * Converts the given RGB color to grayscale using a weighted average formula.
     *
     * @param rgb RGB color object to convert to grayscale
     */
    public static void applyGrayscale(RGB rgb) {
        int gray = (int) Math.round(rgb.red * 0.299 + rgb.green * 0.587 + rgb.blue * 0.114);
        rgb.red = gray;
        rgb.green = gray;
        rgb.blue = gray;
    }

    /**
     * Converts the given RGB color to sepia tone using the standard sepia formula.
     *
     * @param rgb RGB color object to convert to sepia
     */
    public static void applySepia(RGB rgb) {
        int originalRed = rgb.red;
        int originalGreen = rgb.green;
        int originalBlue = rgb.blue;

        rgb.red = clamp((int) Math.round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue));
        rgb.green = clamp((int) Math.round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue));
        rgb.blue = clamp((int) Math.round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue));
    }

    /**
     * Ensures that a color value stays within the valid RGB range [0, 255].
     *
     * @param value the color component value
     * @return the clamped value
     */
    public static int clamp(int value) {
        return Math.min(255, Math.max(0, value));
    }
}