/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 03NOV2025
 * Lab/Task: Hack06 - ColorUtils Tests
 *
 * Description:
 * JUnit tests for `ColorUtils`. Tests cover grayscale and sepia filters,
 * clamping behavior, and null-filter handling.
 */

package unl.soc;

import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class ColorUtilsTests {

    /** 
     * Tests grayscale conversion using equal RGB components.
     */
    @Test
    public void testGrayscaleUniform() {
        ColorUtils.RGB rgb = new ColorUtils.RGB(100, 100, 100);
        ColorUtils.applyFilter(rgb, ColorUtils.ColorFilter.GRAYSCALE);
        assertEquals(100, rgb.red);
        assertEquals(100, rgb.green);
        assertEquals(100, rgb.blue);
    }

    /** 
     * Tests grayscale conversion using distinct RGB components.
     */
    @Test
    public void testGrayscaleDistinct() {
        ColorUtils.RGB rgb = new ColorUtils.RGB(200, 100, 50);
        ColorUtils.applyFilter(rgb, ColorUtils.ColorFilter.GRAYSCALE);
        assertEquals(rgb.red, rgb.green);
        assertEquals(rgb.red, rgb.blue);
    }

    /** 
     * Tests sepia conversion with mid-range RGB values.
     */
    @Test
    public void testSepiaMidRange() {
        ColorUtils.RGB rgb = new ColorUtils.RGB(100, 50, 25);
        ColorUtils.applyFilter(rgb, ColorUtils.ColorFilter.SEPIA);
        assertTrue(rgb.red > rgb.green && rgb.green > rgb.blue);
    }

    /** 
     * Tests sepia conversion ensures values do not exceed 255.
     */
    @Test
    public void testSepiaClamping() {
        ColorUtils.RGB rgb = new ColorUtils.RGB(255, 255, 255);
        ColorUtils.applyFilter(rgb, ColorUtils.ColorFilter.SEPIA);
        assertTrue(rgb.red <= 255 && rgb.green <= 255 && rgb.blue <= 255);
    }

    /** 
     * Tests that no filter applied leaves RGB unchanged.
     */
    @Test
    public void testNullFilterNoChange() {
        ColorUtils.RGB rgb = new ColorUtils.RGB(100, 150, 200);
        ColorUtils.applyFilter(rgb, null);
        assertEquals(100, rgb.red);
        assertEquals(150, rgb.green);
        assertEquals(200, rgb.blue);
    }
}