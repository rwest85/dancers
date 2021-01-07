#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/dancers.h"

int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  dancers_packet *packet = NULL;

  int rc = dancers_packet_parse(Data, Size, &packet);

  if (rc == DE_SUCCESS && packet != NULL) {
    dancers_packet_print(stderr, packet);
    dancers_packet_free(packet);
  }
  return 0;  // Non-zero return values are reserved for future use.
}

int main(int argc, char **argv) {
  // The buffer we will pass to the library
  uint8_t buf[65536];

  size_t read_bytes = read(0, buf, sizeof(buf));

  LLVMFuzzerTestOneInput(buf, read_bytes);

  return 0;
}
