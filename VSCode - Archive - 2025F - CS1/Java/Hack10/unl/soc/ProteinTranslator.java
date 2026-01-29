package unl.soc;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Locale;

/**
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 2025-11-10
 * Lab/Task: Hack10
 *
 * Command-line wrapper that reads a DNA file, converts to RNA,
 * translates to protein using ProteinTranslator.proteinMap, and
 * writes the protein string to the output file. On any error the
 * program exits with a non-zero status (no extra prints).
 */
public class ProteinTranslator {
  /**
   * Trigram RNA to protein map. Lower-case 'x' marks stop codons.
   */
  public static final java.util.Map<String, Character> proteinMap = new java.util.HashMap<>();

  static {
    proteinMap.put("AAA", 'K');
    proteinMap.put("AAC", 'N');
    proteinMap.put("AAG", 'K');
    proteinMap.put("AAU", 'N');
    proteinMap.put("ACA", 'T');
    proteinMap.put("ACC", 'T');
    proteinMap.put("ACG", 'T');
    proteinMap.put("ACU", 'T');
    proteinMap.put("AGA", 'R');
    proteinMap.put("AGC", 'S');
    proteinMap.put("AGG", 'R');
    proteinMap.put("AGU", 'S');
    proteinMap.put("AUA", 'I');
    proteinMap.put("AUC", 'I');
    proteinMap.put("AUG", 'M');
    proteinMap.put("AUU", 'I');
    proteinMap.put("CAA", 'Q');
    proteinMap.put("CAC", 'H');
    proteinMap.put("CAG", 'Q');
    proteinMap.put("CAU", 'H');
    proteinMap.put("CCA", 'P');
    proteinMap.put("CCC", 'P');
    proteinMap.put("CCG", 'P');
    proteinMap.put("CCU", 'P');
    proteinMap.put("CGA", 'R');
    proteinMap.put("CGC", 'R');
    proteinMap.put("CGG", 'R');
    proteinMap.put("CGU", 'R');
    proteinMap.put("CUA", 'L');
    proteinMap.put("CUC", 'L');
    proteinMap.put("CUG", 'L');
    proteinMap.put("CUU", 'L');
    proteinMap.put("GAA", 'E');
    proteinMap.put("GAC", 'D');
    proteinMap.put("GAG", 'E');
    proteinMap.put("GAU", 'D');
    proteinMap.put("GCA", 'A');
    proteinMap.put("GCC", 'A');
    proteinMap.put("GCG", 'A');
    proteinMap.put("GCU", 'A');
    proteinMap.put("GGA", 'G');
    proteinMap.put("GGC", 'G');
    proteinMap.put("GGG", 'G');
    proteinMap.put("GGU", 'G');
    proteinMap.put("GUA", 'V');
    proteinMap.put("GUC", 'V');
    proteinMap.put("GUG", 'V');
    proteinMap.put("GUU", 'V');
    proteinMap.put("UAA", 'x');
    proteinMap.put("UAC", 'Y');
    proteinMap.put("UAG", 'x');
    proteinMap.put("UAU", 'Y');
    proteinMap.put("UCA", 'S');
    proteinMap.put("UCC", 'S');
    proteinMap.put("UCG", 'S');
    proteinMap.put("UCU", 'S');
    proteinMap.put("UGA", 'x');
    proteinMap.put("UGC", 'C');
    proteinMap.put("UGG", 'W');
    proteinMap.put("UGU", 'C');
    proteinMap.put("UUA", 'L');
    proteinMap.put("UUC", 'F');
    proteinMap.put("UUG", 'L');
    proteinMap.put("UUU", 'F');
  }

  public static void main(String[] args) {
    if (args == null || args.length != 2) {
      System.exit(1);
    }
    String inPath = args[0];
    String outPath = args[1];

    String contents = FileUtils.getFileContents(inPath);
    if (contents == null) System.exit(1);

    StringBuilder rna = new StringBuilder(contents.length());
    for (int i = 0; i < contents.length(); i++) {
      char c = contents.charAt(i);
      if (Character.isWhitespace(c)) continue;
      char up = Character.toUpperCase(c);
      if (up == 'T') up = 'U';
      if (up == 'A' || up == 'C' || up == 'G' || up == 'U') {
        rna.append(up);
      } else {
        System.exit(1);
      }
    }

    StringBuilder protein = new StringBuilder(rna.length() / 3 + 1);
    for (int i = 0; i + 2 < rna.length(); i += 3) {
      String codon = rna.substring(i, i+3).toUpperCase(Locale.ROOT);
      Character aa = ProteinTranslator.proteinMap.get(codon);
      if (aa == null) System.exit(1);
      if (aa == 'x') break;
      protein.append(aa.charValue());
    }

    try {
      Files.write(Paths.get(outPath), (protein.toString() + System.lineSeparator()).getBytes(StandardCharsets.UTF_8));
    } catch (IOException e) {
      System.exit(1);
    }
    System.exit(0);
  }

}
