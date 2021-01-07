#pragma once
#include "000_internal.h"

const uint8_t COMPRESSION_FLAGS = 0xC0;
const uint16_t COMPRESSION_MASK = 0x3FFF;

static int append(char *first, const char *second, size_t howmuch) {
  size_t s = strlen(first);
  if (s + howmuch < 255) {
    memcpy(first + s, second, howmuch);
    first[s + howmuch + 1] = '\0';
    return 0;
  }
  return 1;
}

static int is_compression_offset(size_t l) {
  return (l & COMPRESSION_FLAGS) == COMPRESSION_FLAGS;
}

static size_t get_compression_offset(uint16_t l) {
  return (l & COMPRESSION_MASK);
}

/* TODO: make inlineable and use in parse_txt */
static char *read_str(const uint8_t *data, size_t *offset, size_t length) {
  TRACE_START();
  char *str = NULL;

  if (*offset < length) {
    size_t l = read_uint8(data, offset);

    if (*offset + l < length) {
      str = calloc(l + 1, 1);
      if (str == NULL) return NULL;

      memcpy(str, &data[*offset], l);
      TRACE("Read string length 0x%02zx '%s'", l, str);
      *offset += l;
    } else {
      DEBUG(
          "read_str: string of length 0x%02zx extends to 0x%04zx, past end of "
          "record 0x%04zx",
          l, (*offset + l), length);
    }
  }

  return str;
}

static char *parse_name(const uint8_t *data, size_t *offset, size_t length) {
  TRACE_START();
  char name[MAX_DOMAINNAME_SZ + 1] = {0};

  size_t l = 0;
  size_t compress_offset = 0;

  while (*offset < length) {
    /* peek at first byte */
    l = data[*offset];
    TRACE("Parsing name segment 0x%02zx", l);

    if (l == 0) {
      *offset = *offset + 1;
      break;
    }

    if (is_compression_offset(l)) {
      compress_offset = get_compression_offset(read_uint16(data, offset));
      if (compress_offset >= *offset) {
        DEBUG(
            "Illegal recursion (offset 0x%04zx points forward) while "
            "decompressing domain name",
            compress_offset);
        return NULL;
      }

      TRACE("Expanding compressed domain name at 0x%04zx", *offset);
      char *rest = parse_name(data, &compress_offset, length);
      if (rest) {
        if (append(name, rest, strlen(rest)) == 0) {
          TRACE("Expanded domain name '%s'", name);
          free(rest);
        } else {
          DEBUG(
              "Name too long while decompressing pointer 0x%04zx at offset "
              "0x%04zx",
              compress_offset, *offset);
          free(rest);
          return NULL;
        }
      } else {
        DEBUG(
            "Name decompression error: failed to parse pointer 0x%04zx at "
            "offset 0x%04zx",
            compress_offset, *offset);
        return NULL;
      }
      break;
    } else if (l < 63) {
      if (append(name, (const char *)&data[*offset + 1], l) == 0 &&
          append(name, ".", 1) == 0) {
        TRACE("Added segment to name '%s' at 0x%04zx", name, *offset);
        *offset += l + 1;
      } else
        return NULL;
    } else {
      DEBUG("Encountered illegal length value 0x%02zx while parsing name", l);
      return NULL;
    }
  }

  if (*offset > length) {
    DEBUG("exceeded record length 0x%0zu while parsing name '%s'", length,
          name);
    return NULL;
  }

  /* remove final dot */
  l = strlen(name);
  if ((l > 0) && name[l - 1] == '.') name[l - 1] = '\0';

  return strdup((char *)name);
}

static char *parse_name_nocompression(const uint8_t *data, size_t *offset,
                                      size_t length) {
  TRACE_START();
  char name[MAX_DOMAINNAME_SZ + 1] = {0};

  size_t l = 0;

  while (*offset < length) {
    /* peek at first byte */
    l = data[*offset];
    TRACE("Parsing name segment 0x%02zx", l);

    if (l == 0) {
      *offset = *offset + 1;
      break;
    }

    if (is_compression_offset(l)) {
      DEBUG(
          "Compression not allowed at (offset 0x%04zx) while "
          "decompressing name",
          *offset);
      return NULL;
    } else if (l < 63) {
      if (append(name, (const char *)&data[*offset + 1], l) == 0 &&
          append(name, ".", 1) == 0) {
        TRACE("Added segment to name '%s' at 0x%04zx", name, *offset);
        *offset += l + 1;
      } else
        return NULL;
    } else {
      DEBUG("Encountered illegal length value 0x%02zx while parsing name", l);
      return NULL;
    }
  }

  if (*offset > length) {
    DEBUG("exceeded record length 0x%0zu while parsing name '%s'", length,
          name);
    return NULL;
  }

  /* remove final dot */
  l = strlen(name);
  if ((l > 0) && name[l - 1] == '.') name[l - 1] = '\0';

  return strdup((char *)name);
}
