#ifndef HEADER_GUARD_FUNCTIONS_H
#define HEADER_GUARD_FUNCTIONS_H

#define BAUD_RATE_2400                 416
#define BAUD_RATE_4800                 207
#define BAUD_RATE_9600                 103
#define BAUD_RATE_14400                 68
#define BAUD_RATE_19200                 51
#define BAUD_RATE_28800                 34
#define BAUD_RATE_38400                 25
#define BAUD_RATE_57600                 16
#define BAUD_RATE_76800                 12
#define BAUD_RATE_115200                 8
#define BAUD_RATE_230400                 3
#define BAUD_RATE_250000                 3
#define BAUD_RATE_500000                 1
#define BAUD_RATE_1000000                0

#define TIMER_START                      5

void serial_send(const char c);
void writeText(const char * s);
void writeLine(const char * s);

void serial_setup();
void initTimer();

void beginInternal(const int baudrate);
void printInternal(const char*);
void printlnInternal(const char*);

/// @brief Class for handling serial interface as Arduino libraries do
class SerialClass
{
private:
public:
    static void begin(const int baudrate);
    static void print(const char*);
    static void println(const char*);
    static void println(const unsigned long);
    static void println(const long);
    static void println(const unsigned int);
    static void println(const int);
    static void println(const unsigned char);
    static void println(const char);
    static void println(const unsigned short);
    static void println(const short);
    static void println(const double);
    static void println(const float);
};

extern SerialClass Serial;

/// @brief Function that returns amount of milliseconds since start of the program
/// @return returns amount of milliseconds since start/upload/reset of the program. 
///         Overflows after approximately 50 days
unsigned long millis();

/// @brief Sets up timer and interrupts for functions to be used
/// @param initSerial If set the Serial interface is set up with a Baud rate of 9600.
///                   Set to false by default
void initLibraries(bool initSerial = false);

#endif