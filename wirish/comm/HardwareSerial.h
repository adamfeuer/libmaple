/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *****************************************************************************/

/**
 * @file HardwareSerial.h
 *
 * @brief Wirish interface to hardware serial communications.
 */

#ifndef _HARDWARESERIAL_H_
#define _HARDWARESERIAL_H_

#include "timers.h"

#include "Print.h"

/* NB: this class documented "by hand" (i.e., not using Doxygen) in:

     libmaple/docs/source/lang/serial.rst

   If you alter the public HardwareSerial interface, you must update
   the documentation accordingly. */

class HardwareSerial : public Print {
 private:
    uint8 usart_num;
    uint32 max_baud;
    GPIO_Port *gpio_port;
    uint8 tx_pin;
    uint8 rx_pin;
    timer_dev_num timer_num;
    uint8 compare_num;
 public:
    HardwareSerial(uint8 usart_num,
                   uint32 max_baud,
                   GPIO_Port *gpio_port,
                   uint8 tx_pin,
                   uint8 rx_pin,
                   timer_dev_num timer_num,
                   uint8 compare_num);
    void begin(uint32 baud);
    void end(void);
    uint32 available(void);
    uint8 read(void);
    void flush(void);
    virtual void write(unsigned char);
    using Print::write;
};
extern HardwareSerial Serial1;
extern HardwareSerial Serial2;
extern HardwareSerial Serial3;
// TODO: high density device ports
#endif

