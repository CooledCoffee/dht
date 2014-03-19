#include <8051.h>
#define DHT_DATA P2_1
#include "dht.h"

void main() {
    DhtResult result;
	dht_read(&result);
}
