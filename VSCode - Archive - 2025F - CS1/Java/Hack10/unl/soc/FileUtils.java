package unl.soc;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;

/**
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 2025-11-10
 * Lab/Task: Hack10
 *
 * Utility methods for file operations used by the Hack10 Java
 * exercises. Methods are conservative about error handling and
 * return null on failure so callers can detect errors via null
 * checks and exit codes.
 */
public class FileUtils {

  /**
   * Read the entire contents of a file and return it as a String.
   * Newline characters are preserved. Returns null on error.
   */
  public static String getFileContents(String filePath) {
    if (filePath == null) return null;
    try {
      byte[] bytes = Files.readAllBytes(Paths.get(filePath));
      return new String(bytes, StandardCharsets.UTF_8);
    } catch (IOException e) {
      return null;
    }
  }

  /**
   * Read the lines of a file and return them as a List of Strings.
   * Trailing newline characters are not included. Returns null on error.
   */
  public static List<String> getFileLines(String filePath) {
    if (filePath == null) return null;
    List<String> lines = new ArrayList<>();
    try (BufferedReader rdr = Files.newBufferedReader(Paths.get(filePath), StandardCharsets.UTF_8)) {
      String line;
      while ((line = rdr.readLine()) != null) {
        lines.add(line);
      }
      return lines;
    } catch (IOException e) {
      return null;
    }
  }

}
