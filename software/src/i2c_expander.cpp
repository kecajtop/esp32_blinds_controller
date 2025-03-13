#include "Arduino.h"
#include <Adafruit_MCP23008.h>
#include "Wire.h"
#include "macros.h"
#include "variables.h"
#include "i2c_expander.h"

#define IN_1 4
#define IN_2 5
#define IN_3 6
#define IN_4 7

#define OUT_1 2
#define OUT_2 3
#define OUT_3 0
#define OUT_4 1

extern int countOfI2cDevices;
extern int countOfI2cDevices;

Adafruit_MCP23008 
    gpio_exp[8];

bool _port[8] = {0,0,0,0,0,0,0,0};

void i2c_init(int *_result)
 {
  *_result = Wire.begin(SDApin,  SCLpin);

  Wire.setClock(I2C_CLKRATE);
  
  i2c_expander_scan();

  i2c_expander_gpio_set();

 }

void i2c_expander_scan(void)
{
    int _base_adr = 0;

    for (int i = 0;i < 8; i++)
    { 
        _base_adr = MCP23008_ADDRESS + i;

        if (!gpio_exp[i].begin(_base_adr, &Wire)) 
        {
            display_MCP23008_not_present(_base_adr);
            _port[i] = 0;
        }
        else
        {
            display_MCP23008_present(_base_adr);
            _port[i] = 1;
        }

    }
}

void i2c_expander_gpio_set(void)
{
    int _base_adr = 0;

    for (int i = 0;i < 8; i++)
    {
        if (i2c_get_expander_pesents(i))
        {
            gpio_exp[i].pinMode(IN_1, INPUT);
            gpio_exp[i].pullUp(IN_1, HIGH);
            
            gpio_exp[i].pinMode(IN_2, INPUT);
            gpio_exp[i].pullUp(IN_2, HIGH);
            
            gpio_exp[i].pinMode(IN_3, INPUT);
            gpio_exp[i].pullUp(IN_3, HIGH);

            gpio_exp[i].pinMode(IN_4, INPUT);
            gpio_exp[i].pullUp(IN_4, HIGH);

            gpio_exp[i].pinMode(OUT_1, OUTPUT);
            gpio_exp[i].digitalWrite(IN_1, LOW);
            
            gpio_exp[i].pinMode(OUT_2, OUTPUT);
            gpio_exp[i].digitalWrite(IN_2, LOW);
            
            gpio_exp[i].pinMode(OUT_3, OUTPUT);
            gpio_exp[i].digitalWrite(IN_3, LOW);

            gpio_exp[i].pinMode(OUT_4, OUTPUT);
            gpio_exp[i].digitalWrite(IN_4, LOW);
        }
    }
}

void i2c_expander_gpio_set_output_state(uint8_t _adr, uint8_t _pin, uint8_t _state)
{
    if (i2c_get_expander_pesents(_adr)) 
    {
        gpio_exp[_adr].digitalWrite(_pin,_state);
    }
}

uint8_t i2c_expander_gpio_get_input_state(uint8_t _adr, uint8_t _pin)
{
    if (i2c_get_expander_pesents(_adr)) 
    {
        return gpio_exp[_adr].digitalRead(_pin);
    }
    else
    {
        return 0;
    }
}

bool i2c_get_expander_pesents(uint8_t _id)
{
    return _port[_id];
}

void display_MCP23008_not_present(uint8_t _adr)
{
  char _buf[32];
  sprintf(_buf, "MCP23008 %02Xh NOT PRESENT", _adr);
  UsrLogln(_buf);
}

void display_MCP23008_present(uint8_t _adr)
{
  char _buf[32];
  sprintf(_buf, "MCP23008 %02Xh PRESENT", _adr);
  UsrLogln(_buf);
}

void motor::begin(uint8_t _adr)
{
    adr = _adr;
    motor_stop(1);
    motor_stop(2);
}

void motor::motor_stop(uint8_t _motor)
{
    if (_motor==1)
    {
        i2c_expander_gpio_set_output_state(adr,OUT_1,LOW);
        i2c_expander_gpio_set_output_state(adr,OUT_2,LOW);
    }
    else if (_motor==2)
    {
        i2c_expander_gpio_set_output_state(adr,OUT_3,LOW);
        i2c_expander_gpio_set_output_state(adr,OUT_4,LOW);
    }
}

void motor::motor_open(uint8_t _motor)
{
    if (_motor==1)
    {
        i2c_expander_gpio_set_output_state(adr,OUT_1,HIGH);
        i2c_expander_gpio_set_output_state(adr,OUT_2,LOW);
    }
    else if (_motor==2)
    {
        i2c_expander_gpio_set_output_state(adr,OUT_3,HIGH);
        i2c_expander_gpio_set_output_state(adr,OUT_4,LOW);
    }
}

void motor::motor_close(uint8_t _motor)
{
    if (_motor==1)
    {
        i2c_expander_gpio_set_output_state(adr,OUT_1,LOW);
        i2c_expander_gpio_set_output_state(adr,OUT_2,HIGH);
    }
    else if (_motor==2)
    {
        i2c_expander_gpio_set_output_state(adr,OUT_3,LOW);
        i2c_expander_gpio_set_output_state(adr,OUT_4,HIGH);
    }
}

uint8_t motor::read_gpio_1(void)
{
    return !i2c_expander_gpio_get_input_state(adr, IN_1);
}

uint8_t motor::read_gpio_2(void)
{
    return !i2c_expander_gpio_get_input_state(adr, IN_2);
}

uint8_t motor::read_gpio_3(void)
{
    return !i2c_expander_gpio_get_input_state(adr, IN_3);
}

uint8_t motor::read_gpio_4(void)
{
    return !i2c_expander_gpio_get_input_state(adr, IN_4);
}