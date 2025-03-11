#ifndef i2c_expander_h
#define i2c_expander_h

#include "Arduino.h"

void i2c_init(int *_result);

void display_MCP23008_present(uint8_t _adr);

void display_MCP23008_not_present(uint8_t _adr);

void i2c_expander_scan(void);

void i2c_expander_gpio_set(void);

bool i2c_get_expander_pesents(uint8_t _id);

uint8_t i2c_expander_gpio_get_input_state(uint8_t _adr, uint8_t _pin);

void i2c_expander_gpio_set_output_state(uint8_t _adr, uint8_t _pin, uint8_t _state);

class motor 
{
    public:
        void begin(uint8_t _adr);
        void motor_stop(uint8_t _motor);
        void motor_close(uint8_t _motor);
        void motor_open(uint8_t _motor);
        uint8_t read_gpio_1(void);
        uint8_t read_gpio_2(void);
        uint8_t read_gpio_3(void);
        uint8_t read_gpio_4(void);
    private:
        uint8_t adr;
};

#endif