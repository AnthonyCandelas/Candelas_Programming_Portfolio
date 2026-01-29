
/**
 * TODO: provide documentation for your structure
 */
typedef struct {
  // TODO: define your structure here
} Rss;

/**
 * A factory function to create an empty RSS feed
 * with "default" values
 */
Rss* createEmptyRss();

/**
 * A factory function to create an Rss structure
 * with the given values
 */
Rss* createRss(const char* title,
               const char* link,
               const char* date,
               const char* description);

/**
 * An initialization function to initialize an RSS feed with the
 * given values.
 */
void initRss(Rss *feed,
             const char* title,
             const char* link,
             const char* date,
             const char* description);

/**
 * A function to construct a (human-readable) string representation
 * of the given RSS item.
 */
char *rssToString(const Rss *item);

/**
 * A function that prints the given Rss structure
 * to the standard output.
 */
void printRss(const Rss* item);
