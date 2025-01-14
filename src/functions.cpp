#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#include "functions.h"

volatile unsigned long timer0_millis = 0;

SerialClass Serial;
bool timerSet = false;

unsigned long millis() {
     if (!timerSet)
        initTimer();

    unsigned long m;
	uint8_t oldSREG = SREG;

	// disable interrupts while we read timer0_millis or we might get an
	// inconsistent value (e.g. in the middle of a write to timer0_millis)
	cli();
	m = timer0_millis;
	SREG = oldSREG;

	return m;
}

// -> Timer Start value is 5 in order to limit 8-Bit Timer to 250 values
// -> 64*250 cycles per Interrupt = 16000
// -> 16MHz / 1M = 16 Cycles/µs
// -> 16000 / 16 = 1000µs per Interrupt
ISR(TIMER0_OVF_vect) {
    TCNT0 = TIMER_START;
    timer0_millis++;
}

void initLibraries(bool initSerial = false) {
    if (initSerial)
        Serial.begin(9600);
    initTimer();

    sei();
}

void initTimer() {
    if (timerSet)
        return;

    timerSet = true;

    TIMSK0 = (1 << TOIE0);
    TCCR0B = (1 << CS00) | (1 << CS01);
    TCNT0 = TIMER_START;
}

void serial_setup() {
    beginInternal(9600);
}

void serial_send(const char c)
{
     while ((UCSR0A & (1<<UDRE0))==0);  // wait as long, as the last sending is finished!
     UDR0 = c;
}

void beginInternal(const int baudrate) {

    UCSR0B = (1 << RXCIE0) | (1 << RXEN0)  | (1 << TXEN0); // frame format: 8 data, 
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Use 8-bit character sizes
    UBRR0H = 0;

    switch (baudrate)
    {
    case BAUD_RATE_1000000:
        UBRR0L = BAUD_RATE_1000000;
        break;
    case BAUD_RATE_500000:
        UBRR0L = BAUD_RATE_500000;
        break;
    case BAUD_RATE_250000:
        UBRR0L = BAUD_RATE_250000;
        break;
    /*case BAUD_RATE_230400:
        UBRR0L = BAUD_RATE_230400;
        break;*/
    case BAUD_RATE_115200:
        UBRR0L = BAUD_RATE_115200;
        break;
    case BAUD_RATE_76800:
        UBRR0L = BAUD_RATE_76800;
        break;
    case BAUD_RATE_57600:
        UBRR0L = BAUD_RATE_57600;
        break;
    case BAUD_RATE_38400:
        UBRR0L = BAUD_RATE_38400;
        break;
    case BAUD_RATE_28800:
        UBRR0L = BAUD_RATE_28800;
        break;
    case BAUD_RATE_19200:
        UBRR0L = BAUD_RATE_19200;
        break;
    case BAUD_RATE_14400:
        UBRR0L = BAUD_RATE_14400;
        break;
    case BAUD_RATE_9600:
        UBRR0L = BAUD_RATE_9600;
        break;
    case BAUD_RATE_4800:
        UBRR0L = BAUD_RATE_4800;
        break;
    case BAUD_RATE_2400: {
        UBRR0H = (unsigned char)(((unsigned int)baudrate) >> 8);
        UBRR0L = (unsigned char)((unsigned int)baudrate);
    }   break;
    default:
        UBRR0L = BAUD_RATE_9600;
    }
}

void printInternal(const char* s) {
    const char * p = s; 

    while (*p != '\0') 
    {
        serial_send(*p);
        p++;
    }
}

void printlnInternal(const char* s) {
    printInternal(s);
    serial_send('\n');
}

void SerialClass::begin(const int baudrate) {
    beginInternal(baudrate);
}

void SerialClass::print(const char* txt) {
    printInternal(txt);
}

void SerialClass::println(const char* txt) {
    printlnInternal(txt);
}

void SerialClass::println(const unsigned long val) {
    //TODO change size and refactor to nicer way
    char txt[81];
    sprintf(txt, "%ld", val);

    printlnInternal(txt);
}


void SerialClass::println(const long val) {
    //TODO change size and refactor to nicer way
    char txt[81];
    sprintf(txt, "%ld", val);

    printlnInternal(txt);
}

void SerialClass::println(const unsigned int val) {
    //TODO change size and refactor to nicer way
    char txt[81];
    sprintf(txt, "%d", val);

    printlnInternal(txt);
}
void SerialClass::println(const int val) {
    //TODO change size and refactor to nicer way
    char txt[81];
    sprintf(txt, "%d", val);

    printlnInternal(txt);
}

void SerialClass::println(const unsigned char val) {
    //TODO change size and refactor to nicer way
    char txt[81];
    sprintf(txt, "%c", val);

    printlnInternal(txt);
}

void SerialClass::println(const char val) {
    //TODO change size and refactor to nicer way
    char txt[81];
    sprintf(txt, "%c", val);

    printlnInternal(txt);
}

void SerialClass::println(const unsigned short val) {
    //TODO change size and refactor to nicer way
    char txt[81];
    sprintf(txt, "%d", val);

    printlnInternal(txt);
}

void SerialClass::println(const short val) {
    //TODO change size and refactor to nicer way
    char txt[81];
    sprintf(txt, "%d", val);

    printlnInternal(txt);
}

//TODO fix -> not working
void SerialClass::println(const double val) {
    //TODO change size and refactor to nicer way
    char txt[81];
    sprintf(txt, "%lf", val);

    printlnInternal(txt);
}

/*//TODO fix -> not working
void SerialClass::println(const float val) {
    //TODO change size and refactor to nicer way
    char txt[81];
    sprintf(txt, "%f", val);

    printlnInternal(txt);
}*/