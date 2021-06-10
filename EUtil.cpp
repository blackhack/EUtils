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

#include "EUtil.h"

bool ETimer::HasExpire()
{
    if (!_active)
        return false;

    uint32_t currentTime = (_microSeconds ? micros() : millis());

    if (currentTime - _initialTime >= _duration)
    {
        if (_oneShot)
            _active = false;
        else
            _initialTime = currentTime;

        return true;
    }

    return false;
}

void ETimer::Start(uint32_t duration, bool oneShot, bool microSeconds)
{
    _active = true;
    _oneShot = oneShot;
    _microSeconds = microSeconds;
    _duration = duration;
    _initialTime = (_microSeconds ? micros() : millis());
}

uint32_t ETimer::RemainingDuration()
{
    uint32_t currentTime = (_microSeconds ? micros() : millis());

    return _duration - (currentTime - _initialTime);
}

void EButton::SetupButton(uint8_t pin, uint8_t input_mode, bool inverted_logic)
{
    pinMode(pin, input_mode);
    _pin = pin;
    _input_mode = input_mode;
    _inverted_logic = inverted_logic;
    _callback_function = nullptr;
    _callback_parameter = nullptr;

    if (_input_mode == INPUT_PULLUP)
        _last_state = _inverted_logic ? LOW : HIGH;
    else
        _last_state = _inverted_logic ? HIGH : LOW;

    _last_debounce_state = _last_state;
}

void EButton::SetCallBack(button_callback_type callback, void* parameter /*= nullptr*/)
{
    _callback_function = callback;
    _callback_parameter = parameter;
}

bool EButton::Update()
{
    bool state_change = false;
    int8_t state = digitalRead(_pin);

    if (_last_debounce_state != state && !_debounce_timer.IsActive())
    {
        _last_state = digitalRead(_pin);
        _debounce_timer.Start(_debounce_duration);
    }
    else if (_debounce_timer.HasExpire() && _last_state == state)
    {
        _last_debounce_state = state;

        if (IsBeingPush())
        {
            _hold_timer.Start(_hold_duration);
            _was_pushed = true;
            state_change = true;

            if (_callback_function)
                _callback_function(_callback_parameter, BUTTON_PUSHED);
        }
        else
        {
            _hold_timer.Stop();
            _was_released = true;
            state_change = true;

            if (_callback_function)
                _callback_function(_callback_parameter, BUTTON_RELEASED);
        }
    }

    if (IsBeingPush() && _hold_timer.HasExpire())
    {
        _was_holded = true;
        state_change = true;

        if (_callback_function)
            _callback_function(_callback_parameter, BUTTON_HOLDED);
    }

    return state_change;
}

bool EButton::IsBeingPush()
{
    if (_last_debounce_state == HIGH)
    {
        if (_input_mode == INPUT_PULLUP)
            return _inverted_logic ? true : false;
        else
            return _inverted_logic ? false : true;
    }
    else if (_last_debounce_state == LOW)
    {
        if (_input_mode == INPUT_PULLUP)
            return _inverted_logic ? false : true;
        else
            return _inverted_logic ? true : false;
    }
    else
        return false;
}

bool EButton::Pushed()
{
    if (_was_pushed)
    {
        _was_pushed = false;
        return true;
    }

    return false;
}

bool EButton::Released()
{
    if (_was_released)
    {
        _was_released = false;
        return true;
    }

    return false;
}

bool EButton::Holded()
{
    if (_was_holded)
    {
        _was_holded = false;
        return true;
    }

    return false;
}
