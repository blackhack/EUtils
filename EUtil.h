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

#ifndef EUtil_h__
#define EUtil_h__

#include "Arduino.h"

class ETimer
{
public:
    bool HasExpire();
    void Start(uint32_t duration, bool oneShot = true, bool microSeconds = false);
    void Stop() { _active = false; }
    uint32_t RemainingDuration();
    bool IsActive() { return _active; }

private:
    bool _active = false;
    bool _oneShot = true;
    bool _microSeconds = false;
    uint32_t _initialTime = 0;
    uint32_t _duration = 0;
};

class EButton
{
public:
    enum BUTTON_EVENT
    {
        BUTTON_STAND_BY,
        BUTTON_PUSHED,
        BUTTON_RELEASED,
        BUTTON_HOLDED,
    };

    typedef void (*button_callback_type)(void*, BUTTON_EVENT);

    void SetupButton(uint8_t pin, uint8_t input_mode, bool inverted_logic = false);
    void SetCallBack(button_callback_type callback, void* parameter = nullptr);
    void SetDebounceDuration(uint16_t debounce_duration) { _debounce_duration = debounce_duration; }
    void SetHoldDuration(uint16_t hold_duration) { _hold_duration = hold_duration; }
    BUTTON_EVENT Update();

    bool IsBeingPush();
    bool Pushed();
    bool Released();
    bool Holded();

private:
    uint16_t _debounce_duration = 50; // ms
    uint16_t _hold_duration = 1000; // ms

    uint8_t _pin;
    uint8_t _input_mode;
    bool _inverted_logic;
    int8_t _last_state;
    int8_t _last_debounce_state;
    button_callback_type _callback_function;
    void* _callback_parameter;

    ETimer _debounce_timer;
    ETimer _hold_timer;

    bool _was_pushed = false;
    bool _was_released = false;
    bool _was_holded = false;
};

#endif // EUtil_h__
