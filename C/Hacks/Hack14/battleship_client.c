/*
 * Name: Anthony Candelas
 * Email: tsallinger2@unl.edu
 * Date: 12Dec2025
 * Hack14 - Battleship Client (C)
 *
 * Description:
 * Text-based client for playing Battleship against the server via HTTP/JSON.
 * Uses libcurl for HTTP requests. Records moves and tracks game state.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <curl/curl.h>

#define BASE_URL "http://csce.unl.edu:8080/Battleship"
#define LOGIN "tsallinger2"

struct memory { char *data; size_t size; };

struct MoveResult {
  bool ok;
  bool hit;
  bool already;
  bool won;
  bool lost;
  int score;
};

static int board[10][10];

static void reset_board(void) {
  for(int y=0; y<10; y++) {
    for(int x=0; x<10; x++) {
      board[y][x] = -1;
    }
  }
}

struct TargetQueue {
  int xs[256];
  int ys[256];
  int head;
  int tail;
};

static void tq_init(struct TargetQueue *q) { q->head = q->tail = 0; }
static bool tq_empty(struct TargetQueue *q) { return q->head == q->tail; }
static void tq_push(struct TargetQueue *q, int x, int y) {
  int next = (q->tail + 1) % 256;
  if(next == q->head) return;
  q->xs[q->tail] = x; q->ys[q->tail] = y; q->tail = next;
}
static bool tq_pop(struct TargetQueue *q, int *x, int *y) {
  if(tq_empty(q)) return false;
  *x = q->xs[q->head];
  *y = q->ys[q->head];
  q->head = (q->head + 1) % 256;
  return true;
}

static size_t write_cb(void *contents, size_t sz, size_t nmemb, void *userp) {
  size_t realsize = sz * nmemb;
  struct memory *mem = (struct memory *)userp;
  char *ptr = realloc(mem->data, mem->size + realsize + 1);
  if(!ptr) return 0;
  mem->data = ptr;
  memcpy(&(mem->data[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->data[mem->size] = '\0';
  return realsize;
}

static int http_get(const char *url, struct memory *resp) {
  CURL *curl = curl_easy_init();
  if(!curl) return -1;
  resp->data = NULL; resp->size = 0;
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)resp);
  CURLcode res = curl_easy_perform(curl);
  long code = 0; curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
  curl_easy_cleanup(curl);
  return (res == CURLE_OK && code == 200) ? 0 : (int)code;
}

static int http_post_move(const char *url, const char *jsonPayload, struct memory *resp) {
  CURL *curl = curl_easy_init();
  if(!curl) return -1;
  resp->data = NULL; resp->size = 0;
  curl_easy_setopt(curl, CURLOPT_URL, url);
  char *form = NULL;
  size_t len = strlen(jsonPayload) + 6;
  form = malloc(len + 1);
  snprintf(form, len + 1, "move=%s", jsonPayload);
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, form);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)resp);
  CURLcode res = curl_easy_perform(curl);
  long code = 0; curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
  free(form);
  curl_easy_cleanup(curl);
  return (res == CURLE_OK && (code == 200 || code == 201)) ? 0 : (int)code;
}

static char game_id[64] = {0};

static int start_new_game(void) {
  char url[256];
  snprintf(url, sizeof(url), "%s/NewGame?login=%s", BASE_URL, LOGIN);
  struct memory resp; int rc = http_get(url, &resp);
  if(rc != 0) { fprintf(stderr, "NewGame failed: rc=%d\n", rc); return rc; }
  char *gid = strstr(resp.data, "\"game_id\":\"");
  if(!gid) { fprintf(stderr, "No game_id in response: %s\n", resp.data ? resp.data : "(null)"); free(resp.data); return -1; }
  gid += strlen("\"game_id\":\"");
  char *end = strchr(gid, '"');
  if(!end) { fprintf(stderr, "Malformed game_id JSON\n"); free(resp.data); return -1; }
  size_t len = (size_t)(end - gid);
  if(len >= sizeof(game_id)) len = sizeof(game_id) - 1;
  memcpy(game_id, gid, len); game_id[len] = '\0';
  printf("New game started. game_id=%s\n", game_id);
  free(resp.data);
  reset_board();
  return 0;
}

static struct MoveResult parse_result(const char *json) {
  struct MoveResult r = { .ok = true, .hit = false, .already = false, .won = false, .lost = false, .score = -1 };
  if(!json) { r.ok = false; return r; }
  if(strstr(json, "\"result\":\"HIT\"")) r.hit = true;
  else if(strstr(json, "\"result\":\"MISS\"")) r.hit = false;
  else if(strstr(json, "\"result\":\"ERROR\"")) r.ok = false;
  if(strstr(json, "already")) r.already = true;
  if(strstr(json, "\"game_status\":\"won\"")) r.won = true;
  if(strstr(json, "\"game_status\":\"lost\"")) r.lost = true;
  char *s = strstr(json, "\"score\":");
  if(s) {
    s += strlen("\"score\":");
    r.score = atoi(s);
  }
  return r;
}

static struct MoveResult make_move(int x, int y) {
  char url[256]; snprintf(url, sizeof(url), "%s/Move", BASE_URL);
  char payload[256];
  snprintf(payload, sizeof(payload), "{\"game_id\":\"%s\",\"login\":\"%s\",\"x\":%d,\"y\":%d}", game_id, LOGIN, x, y);
  struct memory resp; int rc = http_post_move(url, payload, &resp);
  if(rc != 0) {
    fprintf(stderr, "Move failed: rc=%d\n", rc);
    struct MoveResult err = { .ok = false, .score = -1 };
    return err;
  }
  struct MoveResult res = parse_result(resp.data);
  printf("[%2d,%2d] -> %s\n", x, y, resp.data ? resp.data : "(null)");
  free(resp.data);
  if(res.ok && !res.already) {
    board[y][x] = res.hit ? 1 : 0;
  }
  return res;
}

static void enqueue_neighbors(struct TargetQueue *q, int x, int y) {
  const int dx[4] = {1,-1,0,0};
  const int dy[4] = {0,0,1,-1};
  for(int i=0;i<4;i++) {
    int nx = x + dx[i], ny = y + dy[i];
    if(nx>=0 && nx<10 && ny>=0 && ny<10 && board[ny][nx]==-1) {
      tq_push(q,nx,ny);
    }
  }
}

static bool auto_play(void) {
  struct TargetQueue q; tq_init(&q);
  int parity = 0;
  int won = 0, lost = 0;

  while(!won && !lost) {
    int x = -1, y = -1;
    if(tq_pop(&q, &x, &y)) {
      if(board[y][x] != -1) continue;
    } else {
      bool found = false;
      for(int pass=0; pass<2 && !found; pass++) {
        for(int yy=0; yy<10 && !found; yy++) {
          for(int xx=0; xx<10; xx++) {
            if(((xx+yy)&1)!=((parity+pass)%2)) continue;
            if(board[yy][xx]==-1) { x=xx; y=yy; found=true; break; }
          }
        }
      }
      if(!found) {
        for(int yy=0; yy<10 && !found; yy++) {
          for(int xx=0; xx<10; xx++) {
            if(board[yy][xx]==-1) { x=xx; y=yy; found=true; break; }
          }
        }
      }
      if(!found) break;
    }

    struct MoveResult r = make_move(x,y);
    if(!r.ok) continue;
    if(r.hit) enqueue_neighbors(&q, x, y);
    if(r.won) won = 1;
    if(r.lost) lost = 1;
  }
  return won;
}

int main(int argc, char **argv) {
  if(curl_global_init(CURL_GLOBAL_DEFAULT) != 0) {
    fprintf(stderr, "curl init failed\n");
    return 1;
  }
  if(start_new_game() != 0) {
    curl_global_cleanup();
    return 2;
  }
  if(argc > 1 && strcmp(argv[1], "--auto") == 0) {
    printf("Auto-play engaged: aggressive hunt-target strategy.\n");
    auto_play();
  } else {
    printf("Enter moves as: x y (0-9). Ctrl+D to quit.\n");
    int x, y;
    while (printf("> "), fflush(stdout), scanf("%d %d", &x, &y) == 2) {
      if(x < 0 || x > 9 || y < 0 || y > 9) {
        fprintf(stderr, "Invalid coordinates. Use 0-9.\n");
        continue;
      }
      make_move(x, y);
    }
  }
  curl_global_cleanup();
  return 0;
}
