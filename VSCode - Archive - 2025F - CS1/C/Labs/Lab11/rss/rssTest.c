/**
 * A stand alone test utility for your rss functions.
 *
 */
#include <stdlib.h>
#include <stdio.h>

#include "rss.h"

int main(int argc, char **argv) {

  Rss *empty  = createEmptyRss();

  Rss test01;
  initRss(&test01,
          "RSS TEST 001 - Title",
          "RSS TEST 001 - Link",
          "RSS TEST 001 - Date",
          "RSS TEST 001 - Description");
  Rss *test02 = createRss(
    "RSS TEST 002 - Title",
    "RSS TEST 002 - Link",
    "RSS TEST 002 - Date",
    "RSS TEST 002 - Description");

  printRss(&test01);
  printRss(test02);

  return 0;
}
