/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 03NOV2025
 * Lab/Task: Hack07 - RGB
 *
 * Description:
 * Represents an RGB color with red, green, and blue components. Provides
 * basic getters and equality checks for pixel color data.
 */

package unl.soc;

public class RGB {

    private int red;
    private int green;
    private int blue;

    public RGB(int red, int green, int blue) {
        this.red = red;
        this.green = green;
        this.blue = blue;
    }

    public int getRed() {
        return red;
    }

    public int getGreen() {
        return green;
    }

    public int getBlue() {
        return blue;
    }

    public String toString() {
        return "(" + this.red + ", " + this.green + ", " + this.blue + ")";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 1;
        result = prime * result + blue;
        result = prime * result + green;
        result = prime * result + red;
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null || getClass() != obj.getClass())
            return false;
        RGB other = (RGB) obj;
        return red == other.red && green == other.green && blue == other.blue;
    }
}