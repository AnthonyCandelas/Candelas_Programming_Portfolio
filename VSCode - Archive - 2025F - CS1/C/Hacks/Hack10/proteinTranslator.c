/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 2025-11-10
 * Lab/Task: Hack10
 *
 * Translates a DNA sequence (from an input file) into a protein
 * sequence and writes the result to an output file. The program
 * ignores whitespace in the input, converts T->U to form RNA, then
 * translates codons using the provided rnaToProtein function.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "file_utils.h"
#include "protein_utils.h"

int main(int argc, char **argv) {
  if (argc != 3) {
    return 1;
  }

  const char *inPath = argv[1];
  const char *outPath = argv[2];

  char *contents = getFileContents(inPath);
  if (contents == NULL) {
    return 1;
  }

  /* Build RNA string by removing whitespace and converting T->U. */
  size_t len = strlen(contents);
  char *rna = (char *)malloc(len + 1);
  if (rna == NULL) { free(contents); return 1; }
  size_t rpos = 0;
  for (size_t i = 0; i < len; i++) {
    char c = contents[i];
    if (isspace((unsigned char)c)) continue;
    char up = (char)toupper((unsigned char)c);
    if (up == 'T') up = 'U';
    /* we only keep A, C, G, U characters */
    if (up == 'A' || up == 'C' || up == 'G' || up == 'U') {
      rna[rpos++] = up;
    } else {
      /* invalid character in DNA -- treat as error */
      free(contents);
      free(rna);
      return 1;
    }
  }
  rna[rpos] = '\0';

  /* Translate RNA into protein, codon-by-codon */
  size_t protein_cap = (rpos / 3) + 1;
  char *protein = (char *)malloc(protein_cap + 1);
  if (protein == NULL) { free(contents); free(rna); return 1; }
  size_t ppos = 0;

  for (size_t i = 0; i + 2 < rpos; i += 3) {
    char codon[4] = { rna[i], rna[i+1], rna[i+2], '\0' };
    char aa = rnaToProtein(codon);
    if (aa == 0) {
      free(contents);
      free(rna);
      free(protein);
      return 1;
    }
    if (aa == 'x') break; /* stop codon encountered */
    protein[ppos++] = aa;
  }
  protein[ppos] = '\0';

  /* Write protein to output file */
  FILE *out = fopen(outPath, "w");
  if (out == NULL) {
    free(contents);
    free(rna);
    free(protein);
    return 1;
  }
  fprintf(out, "%s\n", protein);
  fclose(out);

  free(contents);
  free(rna);
  free(protein);
  return 0;
}
