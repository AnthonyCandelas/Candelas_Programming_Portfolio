
/**
 * Types of supported RSS Feeds
 */
typedef enum {
  RSS2,
  ATOM1
} Version;

/**
 * Data associated with an RSS Service
 */
typedef struct {
  char *name;
  char *url;
  Version type;
} RssService;

/**
 * RSS feed for the School of Computing's weekly
 * Bits and Bytes newsletter
 */
static const RssService cseBitsAndBytes = {
    "SoC Bits and Bytes",
    "https://newsroom.unl.edu/announce/cse/?format=rss",
    RSS2
};

/**
 * RSS feed for the University of Nebraska-Omaha
 */
static const RssService unlNews = {
    "University of Nebraska-Lincoln",
    "https://events.unl.edu/upcoming/?format=rss",
    ATOM1
};

/**
 * An RSS feed of Reddit's front page.
 */
static const RssService reddit = {
  "Reddit",
  "https://www.reddit.com/.rss",
  ATOM1
};

/**
 * An RSS feed of Pintrest's front page.
 */
static const RssService pintrest = {
  "Pintrest",
  "https://newsroom.pinterest.com/en/feed/news.xml",
	RSS2
};


/**
 * A utility function to parse an XML feed from an RSS feed
 */
void parseRssXml(xmlNode *rootNode);

/**
 * A utility function to parse an XML feed from an Atom feed
 */
void parseAtomXml(xmlNode *rootNode);
