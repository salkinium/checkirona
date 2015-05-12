// coding: utf-8
/* Copyright (c) 2013, Roboterclub Aachen e.V.
* All Rights Reserved.
*
* The file is part of the xpcc library and is released under the 3-clause BSD
* license. See the file `LICENSE` for the full license governing this code.
*/
// ----------------------------------------------------------------------------

//
// STM32F4DISCOVERY
// Discovery kit for STM32F407/417 lines
// http://www.st.com/web/en/catalog/tools/FM116/SC959/SS1532/PF252419
//

#ifndef CORONA_STM32_HARDWARE_HPP
#define CORONA_STM32_HARDWARE_HPP

#include "stm32f4_discovery.hpp"
#include <xpcc/debug/logger.hpp>
#include <xpcc/processing.hpp>

#include "virtual_gpio.hpp"

namespace Hardware
{

// --- --- --- --- --- --- --- Communication  --- --- --- --- --- --- ---
typedef Usart2 Uart;
// --- --- --- --- --- --- --- Communication  --- --- --- --- --- --- ---


// --- --- --- --- --- --- --- ---  GPIO  --- --- --- --- --- --- --- ---
static constexpr uint8_t NumberOfPins = 30;

struct NamedGpio
{
	xpcc::stm32::VirtualGpio *const gpio;
	const char *name;
};

// Index is of 30 pin connector starting with GND, Audio GND, Line Out R!
// array of constant pointers to virtual gpios
extern NamedGpio const gpios[NumberOfPins];

static uint32_t connectionMatrix[NumberOfPins];

// --- --- --- --- --- --- --- ---  GPIO  --- --- --- --- --- --- --- ---

}	// namespace Hardware

#endif	// CORONA_STM32_HARDWARE_HPP
