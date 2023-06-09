#include "bufreader.h"

#include <libc.h>
#include <stdlib.h>

BufReader *new_bufreader(size_t fd, size_t buf_size) {
  BufReader *br = malloc(sizeof(BufReader));
  br->fd = fd;
  br->buf_size = buf_size;
  br->buf_pos = 0;
  br->buf_len = 0;
  br->buf = malloc(buf_size);
  return br;
}

void free_bufreader(BufReader *br) {
  free(br->buf);
  free(br);
}

size_t bufreader_read(BufReader *br, char *buf, size_t buf_size) {
  size_t bytes_read = 0;
  while (bytes_read < buf_size) {
    if (br->buf_pos == br->buf_len) {
      br->buf_pos = 0;
      br->buf_len = read(br->fd, br->buf, br->buf_size);
      if (br->buf_len == 0) {
        break;
      }
    }
    buf[bytes_read++] = br->buf[br->buf_pos++];
  }

  return bytes_read;
}

size_t bufreader_readline(BufReader *br, char *buf, size_t buf_size) {
  size_t bytes_read = 0;
  while (bytes_read < buf_size) {
    if (br->buf_pos == br->buf_len) {
      br->buf_pos = 0;
      br->buf_len = read(br->fd, br->buf, br->buf_size);
      if (br->buf_len == 0) {
        break;
      }
    }
    char c = br->buf[br->buf_pos++];
    buf[bytes_read++] = c;
    if (c == '\n') {
      break;
    }
  }

  return bytes_read;
}

size_t bufreader_readuntil(BufReader *br, char *buf, size_t buf_size,
                           char delim) {
  size_t bytes_read = 0;
  while (bytes_read < buf_size) {
    if (br->buf_pos == br->buf_len) {
      br->buf_pos = 0;
      br->buf_len = read(br->fd, br->buf, br->buf_size);
      if (br->buf_len == 0) {
        break;
      }
    }
    char c = br->buf[br->buf_pos++];
    buf[bytes_read++] = c;
    if (c == delim) {
      break;
    }
  }

  return bytes_read;
}

size_t bufreader_readstr(BufReader *br, char *buf, size_t buf_size) {
  size_t bytes_read = 0;
  while (bytes_read < buf_size) {
    if (br->buf_pos == br->buf_len) {
      br->buf_pos = 0;
      br->buf_len = read(br->fd, br->buf, br->buf_size);
      if (br->buf_len == 0) {
        break;
      }
    }
    char c = br->buf[br->buf_pos++];
    buf[bytes_read++] = c;
    if (c == '\0') {
      break;
    }
  }

  return bytes_read;
}

size_t bufreader_readu8(BufReader *br, uint8_t *buf) {
  if (br->buf_pos == br->buf_len) {
    br->buf_pos = 0;
    br->buf_len = read(br->fd, br->buf, br->buf_size);
    if (br->buf_len == 0) {
      return 0;
    }
  }
  *buf = br->buf[br->buf_pos++];
  return 1;
}
