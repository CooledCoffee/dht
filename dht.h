#ifndef __DHT_H__
#define __DHT_H__

#ifndef __BOOLEAN__
#define __BOOLEAN__
typedef char bool;
#define TRUE 1
#define FALSE 0
#endif

#ifndef __NOPS__
#define __NOPS__
#define NOP \
    __asm     \
        nop   \
    __endasm;
#define NOP2 NOP NOP
#define NOP4 NOP2 NOP2
#define NOP8 NOP4 NOP4
#define NOP16 NOP8 NOP8
#define NOP32 NOP16 NOP16
#endif

#define WAIT_FOR_HIGH(x) {while (!x) ;}
#define WAIT_FOR_LOW(x) {while (x) ;}

typedef struct {
    char temperature;
    char humidity;
} DhtResult;

bool dht_read(DhtResult* p_result);
char _dht_read_byte();
void _dht_sleep(int millis);

bool dht_read(DhtResult* p_result) {
    char i;
    char buffer[5];

    // init
    DHT_DATA = 0;
    _dht_sleep(30);
    DHT_DATA = 1;
    WAIT_FOR_LOW(DHT_DATA);
    WAIT_FOR_HIGH(DHT_DATA);
    WAIT_FOR_LOW(DHT_DATA);

    // read buffer
    buffer[0] = _dht_read_byte();
    buffer[1] = _dht_read_byte();
    buffer[2] = _dht_read_byte();
    buffer[3] = _dht_read_byte();
    buffer[4] = _dht_read_byte();
    for (i = 0; i < 4; i++)
        buffer[4] -= buffer[i];
    p_result->temperature = buffer[2];
    p_result->humidity = buffer[0];
    return buffer[4] == 0;
}

char _dht_read_byte() {
    char i;
    char result = 0;
    for (i = 0; i < 8; i++) {
        WAIT_FOR_HIGH(DHT_DATA);
        NOP32 // 45us
        NOP8
        result <<= 1;
        if (DHT_DATA)
            result++;
        WAIT_FOR_LOW(DHT_DATA);
    }
    return result;
}

void _dht_sleep(int millis) {
    /*
    We use the form "for (i = 0; i < 100; i++)" instead of "for (i = 100; i--;)".
    Because the 1st form is actually twice fast as the 2nd form after SDCC optimization.
    Note that this is compiler dependent.
    
    Also note that the 1st milli takes less loops because we have to take account of
    the overhead of the function call.
    This function takes 6 NOPs for entering and another 6 NOPs for return (the times
    may be different for other functions).
    */
    char i;
    for (i = 0; i < 100; i++) ;
    for (i = 0; i < 100; i++) ;
    for (i = 0; i < 100; i++) ;
    for (i = 0; i < 100; i++) ;
    for (i = 0; i < 85; i++) ;
    millis--;
    while (millis--) {
        for (i = 0; i < 100; i++) ;
        for (i = 0; i < 100; i++) ;
        for (i = 0; i < 100; i++) ;
        for (i = 0; i < 100; i++) ;
        for (i = 0; i < 91; i++) ;
    }
}

#endif
