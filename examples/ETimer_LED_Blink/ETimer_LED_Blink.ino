/*
    EUtil - This library provides a mix of utilities classes for use in Arduino projects or anything compatible.
    Copyright(C) 2021 Blackhack <davidaristi.0504@gmail.com>

    This library is free software; you can redistribute itand /or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110 - 1301
    USA
 */

#include <EUtil.h>

const uint8_t led_pin = 13;
ETimer led_timer;

void setup()
{
    Serial.begin(115200);
    pinMode(led_pin, OUTPUT);

    //.Start(duration, oneShot, microSeconds)
    led_timer.Start(1000, false);
}

void loop()
{
    if (led_timer.HasExpire())
    {
        if (digitalRead(led_pin) == HIGH)
            digitalWrite(led_pin, LOW);
        else
            digitalWrite(led_pin, HIGH);
    }
}
