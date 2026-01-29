package unl.soc;

import java.util.List;

/**
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 2025-11-10
 * Lab/Task: Hack10
 *
 * Simple visual tester for FileUtils methods. Demonstrates three
 * cases per method as requested by the assignment.
 */
public class FileUtilsTester {

  public static void main(String[] args) {
    String[] names = { "/tmp/jut_case1.txt", "/tmp/jut_case2.txt", "/tmp/jut_case3.txt" };

    try {
      java.nio.file.Files.write(java.nio.file.Paths.get(names[0]), new byte[0]);
      java.nio.file.Files.write(java.nio.file.Paths.get(names[1]), "alpha\nbeta\ngamma\n".getBytes());
      java.nio.file.Files.write(java.nio.file.Paths.get(names[2]), "one\r\n\r\nthree\r\n".getBytes());
    } catch (Exception e) {
      System.exit(1);
    }

    for (int i = 0; i < names.length; i++) {
      String contents = FileUtils.getFileContents(names[i]);
      List<String> lines = FileUtils.getFileLines(names[i]);

      System.out.println("--- Case " + (i+1) + ": file=" + names[i] + " ---");
      if (contents != null) {
        System.out.println("getFileContents length=" + contents.length());
        System.out.println("contents preview:\n" + (contents.isEmpty() ? "(empty)" : contents));
      } else {
        System.out.println("getFileContents: NULL");
      }
      if (lines != null) {
        System.out.println("getFileLines -> " + lines.size() + " lines");
        for (int j = 0; j < lines.size(); j++) {
          System.out.println("  [" + j + "] '" + lines.get(j) + "'");
        }
      } else {
        System.out.println("getFileLines: NULL");
      }
      System.out.println();
    }

    for (String n : names) {
      try { java.nio.file.Files.deleteIfExists(java.nio.file.Paths.get(n)); } catch (Exception e) {}
    }
    System.out.println("Java tests complete.");
  }

}
