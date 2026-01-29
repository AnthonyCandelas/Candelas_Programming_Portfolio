/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 03NOV2025
 * Lab/Task: Hack07 - Image Utilities
 *
 * Description:
 * Utilities for loading, saving, and manipulating images represented as RGB[][].
 *
 * NOTE: None. Functions that allocate a return value document ownership where
 * applicable.
 */

package unl.soc;

import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import javax.imageio.ImageIO;

public class ImageUtils {

    /**
     * Loads an image from disk into an RGB[][] pixel matrix.
     *
     * @param filePath path to file
     * @return matrix height x width (rows x cols) of RGB
     * @throws RuntimeException on IO error
     */
    public static RGB[][] loadImage(String filePath) {
        File file = new File(filePath);
        BufferedImage img;
        try {
            img = ImageIO.read(file);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

        RGB[][] pixels = new RGB[img.getHeight()][img.getWidth()];
        for (int y = 0; y < img.getHeight(); y++) {
            for (int x = 0; x < img.getWidth(); x++) {
                int p = img.getRGB(x, y);
                int r = (p >> 16) & 0xff;
                int g = (p >> 8) & 0xff;
                int b = p & 0xff;
                pixels[y][x] = new RGB(r, g, b);
            }
        }
        return pixels;
    }

    /**
     * Saves an RGB[][] image to disk. File extension determines format.
     *
     * @param filePath path to save (extension like jpg, png)
     * @param image    2D RGB array (height x width)
     * @throws RuntimeException on IO error
     */
    public static void saveImage(String filePath, RGB[][] image) {
        String extension = filePath.substring(filePath.lastIndexOf(".") + 1);
        BufferedImage newImg = new BufferedImage(image[0].length, image.length, BufferedImage.TYPE_INT_RGB);
        for (int y = 0; y < newImg.getHeight(); y++) {
            for (int x = 0; x < newImg.getWidth(); x++) {
                RGB px = image[y][x];
                int p = (px.getRed() << 16) + (px.getGreen() << 8) + px.getBlue();
                newImg.setRGB(x, y, p);
            }
        }
        File f = new File(filePath);
        try {
            ImageIO.write(newImg, extension, f);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }

    /**
     * Deep copy of an image (allocates new matrix and new RGB instances).
     */
    public static RGB[][] copyImage(RGB[][] image) {
        if (image == null) return null;
        int h = image.length;
        if (h == 0) return new RGB[0][0];
        int w = image[0].length;
        RGB[][] out = new RGB[h][w];
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                RGB p = image[y][x];
                out[y][x] = new RGB(p.getRed(), p.getGreen(), p.getBlue());
            }
        }
        return out;
    }

    /**
     * Flip the image horizontally in-place (mirror left-right).
     */
    public static void flipHorizontal(RGB[][] image) {
        if (image == null || image.length == 0) return;
        int h = image.length;
        int w = image[0].length;
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w / 2; x++) {
                RGB tmp = image[y][x];
                image[y][x] = image[y][w - 1 - x];
                image[y][w - 1 - x] = tmp;
            }
        }
    }

    /**
     * Flip the image vertically in-place (mirror top-bottom).
     */
    public static void flipVertical(RGB[][] image) {
        if (image == null || image.length == 0) return;
        int h = image.length;
        for (int y = 0; y < h / 2; y++) {
            RGB[] tmpRow = image[y];
            image[y] = image[h - 1 - y];
            image[h - 1 - y] = tmpRow;
        }
    }

    /**
     * Returns a new image rotated 90 degrees clockwise.
     */
    public static RGB[][] rotateClockwise(RGB[][] image) {
        if (image == null) return null;
        int h = image.length;
        if (h == 0) return new RGB[0][0];
        int w = image[0].length;
        RGB[][] rotated = new RGB[w][h];
        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                RGB src = image[y][x];
                rotated[x][h - 1 - y] = new RGB(src.getRed(), src.getGreen(), src.getBlue());
            }
        }
        return rotated;
    }
}