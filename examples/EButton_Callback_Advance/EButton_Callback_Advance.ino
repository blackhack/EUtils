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

class TestClass
{
public:
    TestClass() {}

    static void CallBackWrapper(void* parameter, EButton::BUTTON_EVENT event)
    {
        static_cast<TestClass*>(parameter)->CallBackMember(event);
    }

private:
    void CallBackMember(EButton::BUTTON_EVENT event)
    {
        switch (event)
        {
        case EButton::BUTTON_PUSHED:
            Serial.println("The button has been pushed");
            break;
        case EButton::BUTTON_RELEASED:
            Serial.println("The button has been released");
            break;
        case EButton::BUTTON_HOLDED:
            Serial.println("The button has been holded");
            break;
        }
    }
};

TestClass TestInstance;

void setup()
{
    Serial.begin(115200);

    happy_button.SetupButton(happy_button_pin, INPUT_PULLUP);
    happy_button.SetCallBack(TestClass::CallBackWrapper, &TestInstance);
}

void loop()
{
    happy_button.Update();
}
