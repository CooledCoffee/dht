#include <8051.h>
#define P_DHT P2_1
#include "dht.h"

void main() {
    DhtResult result;
	dht_read(&result);
}
