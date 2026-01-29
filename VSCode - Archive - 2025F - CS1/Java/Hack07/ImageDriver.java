/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 03NOV2025
 * Lab/Task: Hack07 - Image Driver
 *
 * Description:
 * Simple driver to demonstrate ImageUtils. Adjust file paths to point to an
 * image in your project (for example: images/pointers.png).
 */

package unl.soc;

public class ImageDriver {

    public static void main(String[] args) {

        String inputPath = "images/pointers.png";
        String outRotated = "images/rotated.jpg";
        String outFlippedH = "images/flipped_h.jpg";
        String outFlippedV = "images/flipped_v.jpg";

        RGB[][] original = ImageUtils.loadImage(inputPath);

        RGB[][] rotated = ImageUtils.rotateClockwise(original);
        ImageUtils.saveImage(outRotated, rotated);

        RGB[][] copyH = ImageUtils.copyImage(original);
        ImageUtils.flipHorizontal(copyH);
        ImageUtils.saveImage(outFlippedH, copyH);

        RGB[][] copyV = ImageUtils.copyImage(original);
        ImageUtils.flipVertical(copyV);
        ImageUtils.saveImage(outFlippedV, copyV);

        System.out.println("Images written: " + outRotated + ", " + outFlippedH + ", " + outFlippedV);
    }
}