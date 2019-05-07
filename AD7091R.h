#ifndef AD7091R_H
#define AD7091R_H

#include <stdint.h>

#define OUT_OF_RANGE_PIN_NUMBER 99


class AD7091R {
    public:
        AD7091R();
        AD7091R(uint8_t convstPin, uint8_t csPin, uint8_t clkPin, uint8_t dataPin);
        ~AD7091R();

        void convstPin(uint8_t pin);
        void csPin(uint8_t pin);
        void clkPin(uint8_t pin);
        void dataPin(uint8_t pin);

        uint8_t convstPin();
        uint8_t csPin();
        uint8_t clkPin();
        uint8_t dataPin();

        bool begin();

        void reset();
        uint16_t data();

    private:
        uint8_t m_convstPin;
        uint8_t m_csPin;
        uint8_t m_clkPin;
        uint8_t m_dataPin;
};
#endif
