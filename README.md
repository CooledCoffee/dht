Introduction
============

DHT library for DHT11 module on C51.

Usage
=====

	#include <8051.h>
	#define DHT_DATA P2_1
	#include "dht.h"
	
	void main() {
    	DhtResult result;
    	dht_read(&result);
	}
	
Replace "P2_1" with your actual pin.

Compatibility
=============

This library is tested against STC89C52RC2 @11.0952MHz.
If you mcu is different from this configuration, you will need to replace the \_dht\_sleep function with your own implementation.

Author
======

Mengchen LEE: <a href="https://plus.google.com/117704742936410336204" target="_blank">Google Plus</a>, <a href="https://cn.linkedin.com/pub/mengchen-lee/30/8/23a" target="_blank">LinkedIn</a>

