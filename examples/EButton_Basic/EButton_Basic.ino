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

const uint8_t happy_button_pin = 12;
EButton happy_button;

void setup()
{
    Serial.begin(115200);

    // .SetupButton(pin, input_mode, inverted_logic), inverted_logic is false by default
    happy_button.SetupButton(happy_button_pin, INPUT_PULLUP, true);

    // Callback is disable by default, you can enable it with .SetCallBack(CallBackFunction, optional void* parameter)
    happy_button.SetCallBack(CallBack);

    // If the button output flickers, you can try increasing the debounce delay (50ms by default)
    //happy_button.SetDebounceDuration(100);
}

void loop()
{
    // .Update() need to be called always before checking the button state
    happy_button.Update();

    // You can change the hold period with happy_button.SetHoldDuration(ms)
    if (happy_button.Holded())
        Serial.println("The button has been holded for 1000 ms");

    if (happy_button.Pushed())
        Serial.println("The button has been pushed");

    if (happy_button.Released())
        Serial.println("The button has been released");
}

void CallBack(void* /*optional_parameter*/, EButton::BUTTON_EVENT event)
{
    switch (event)
    {
    case EButton::BUTTON_PUSHED:
        Serial.println("The button has been pushed - This was called from the callback!");
        break;
    case EButton::BUTTON_RELEASED:
        Serial.println("The button has been released - This was called from the callback!");
        break;
    case EButton::BUTTON_HOLDED:
        Serial.println("The button has been holded - This was called from the callback!");
        break;
    }
}
