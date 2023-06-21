#ifndef BUFREADER_BUFREADER_H
#define BUFREADER_BUFREADER_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

typedef struct {
  size_t fd;
  size_t buf_size;
  size_t buf_pos;
  ssize_t buf_len;
  char *buf;
} BufReader;

/**
 * @brief Create a new BufReader object
 *
 * @param fd the file descriptor to read from
 * @param buf_size the size of the buffer
 *
 * @return
 */
BufReader *new_bufreader(size_t fd, size_t buf_size);

/**
 * @brief Free a BufReader object
 *
 * @param br the BufReader object
 */
void free_bufreader(BufReader *br);

/**
 * @brief Read from a BufReader object
 *
 * @param br the BufReader object
 * @param buf the buffer to read into
 * @param buf_size the size of the buffer
 *
 * @return the number of bytes read
 */
size_t bufreader_read(BufReader *br, char *buf, size_t buf_size);

/**
 * @brief Read a line from a BufReader object
 *
 * @param br the BufReader object
 * @param buf the buffer to read into
 * @param buf_size the size of the buffer
 *
 * @return the number of bytes read
 */
size_t bufreader_readline(BufReader *br, char *buf, size_t buf_size);

/**
 * @brief Read until a delimiter from a BufReader object
 *
 * @param br the BufReader object
 * @param buf the buffer to read into
 * @param buf_size the size of the buffer
 * @param delim the delimiter to read until
 *
 * @return the number of bytes read
 */
size_t bufreader_readuntil(BufReader *br, char *buf, size_t buf_size,
                           char delim);

/**
 * @brief Read a string from a BufReader object
 *
 * @param br the BufReader object
 * @param buf the buffer to read into
 * @param buf_size the size of the buffer
 *
 * @return the number of bytes read
 */
size_t bufreader_readstr(BufReader *br, char *buf, size_t buf_size);

/**
 * @brief Read a uint8_t from a BufReader object
 *
 * @param br the BufReader object
 * @param buf the buffer to read into
 *
 * @return the number of bytes read
 */
size_t bufreader_readu8(BufReader *br, uint8_t *buf);

#endif // BUFREADER_BUFREADER_H
