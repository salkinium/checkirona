// coding: utf-8

#include "hardware.hpp"

// --- --- --- --- --- --- --- Communication  --- --- --- --- --- --- ---
xpcc::IODeviceWrapper<Hardware::Uart, xpcc::IOBuffer::BlockIfFull> outputDevice;
xpcc::IOStream Hardware::serial(outputDevice);

using namespace xpcc::stm32;

// a list of all possible Gpios
// Only those that are in the `gpios` array, will actually be linked into the code!

// --- --- --- --- --- --- --- ---  GPIO  --- --- --- --- --- --- --- ---

// Port A
VirtualGpioWrapper<GpioA0> gpioA0;
VirtualGpioWrapper<GpioA1> gpioA1;
VirtualGpioWrapper<GpioA2> gpioA2;
VirtualGpioWrapper<GpioA3> gpioA3;
VirtualGpioWrapper<GpioA4> gpioA4;
VirtualGpioWrapper<GpioA5> gpioA5;
VirtualGpioWrapper<GpioA6> gpioA6;
VirtualGpioWrapper<GpioA7> gpioA7;
VirtualGpioWrapper<GpioA8> gpioA8;
VirtualGpioWrapper<GpioA9> gpioA9;
VirtualGpioWrapper<GpioA10> gpioA10;
VirtualGpioWrapper<GpioA11> gpioA11;
VirtualGpioWrapper<GpioA12> gpioA12;
VirtualGpioWrapper<GpioA13> gpioA13;
VirtualGpioWrapper<GpioA14> gpioA14;
VirtualGpioWrapper<GpioA15> gpioA15;

// Port B
VirtualGpioWrapper<GpioB0> gpioB0;
VirtualGpioWrapper<GpioB1> gpioB1;
VirtualGpioWrapper<GpioB2> gpioB2;
VirtualGpioWrapper<GpioB3> gpioB3;
VirtualGpioWrapper<GpioB4> gpioB4;
VirtualGpioWrapper<GpioB5> gpioB5;
VirtualGpioWrapper<GpioB6> gpioB6;
VirtualGpioWrapper<GpioB7> gpioB7;
VirtualGpioWrapper<GpioB8> gpioB8;
VirtualGpioWrapper<GpioB9> gpioB9;
VirtualGpioWrapper<GpioB10> gpioB10;
VirtualGpioWrapper<GpioB11> gpioB11;
VirtualGpioWrapper<GpioB12> gpioB12;
VirtualGpioWrapper<GpioB13> gpioB13;
VirtualGpioWrapper<GpioB14> gpioB14;
VirtualGpioWrapper<GpioB15> gpioB15;

// Port C
VirtualGpioWrapper<GpioC0> gpioC0;
VirtualGpioWrapper<GpioC1> gpioC1;
VirtualGpioWrapper<GpioC2> gpioC2;
VirtualGpioWrapper<GpioC3> gpioC3;
VirtualGpioWrapper<GpioC4> gpioC4;
VirtualGpioWrapper<GpioC5> gpioC5;
VirtualGpioWrapper<GpioC6> gpioC6;
VirtualGpioWrapper<GpioC7> gpioC7;
VirtualGpioWrapper<GpioC8> gpioC8;
VirtualGpioWrapper<GpioC9> gpioC9;
VirtualGpioWrapper<GpioC10> gpioC10;
VirtualGpioWrapper<GpioC11> gpioC11;
VirtualGpioWrapper<GpioC12> gpioC12;
VirtualGpioWrapper<GpioC13> gpioC13;
VirtualGpioWrapper<GpioC14> gpioC14;
VirtualGpioWrapper<GpioC15> gpioC15;

// Port D
VirtualGpioWrapper<GpioD0> gpioD0;
VirtualGpioWrapper<GpioD1> gpioD1;
VirtualGpioWrapper<GpioD2> gpioD2;
VirtualGpioWrapper<GpioD3> gpioD3;
VirtualGpioWrapper<GpioD4> gpioD4;
VirtualGpioWrapper<GpioD5> gpioD5;
VirtualGpioWrapper<GpioD6> gpioD6;
VirtualGpioWrapper<GpioD7> gpioD7;
VirtualGpioWrapper<GpioD8> gpioD8;
VirtualGpioWrapper<GpioD9> gpioD9;
VirtualGpioWrapper<GpioD10> gpioD10;
VirtualGpioWrapper<GpioD11> gpioD11;
VirtualGpioWrapper<GpioD12> gpioD12;
VirtualGpioWrapper<GpioD13> gpioD13;
VirtualGpioWrapper<GpioD14> gpioD14;
VirtualGpioWrapper<GpioD15> gpioD15;

// Port E
VirtualGpioWrapper<GpioE0> gpioE0;
VirtualGpioWrapper<GpioE1> gpioE1;
VirtualGpioWrapper<GpioE2> gpioE2;
VirtualGpioWrapper<GpioE3> gpioE3;
VirtualGpioWrapper<GpioE4> gpioE4;
VirtualGpioWrapper<GpioE5> gpioE5;
VirtualGpioWrapper<GpioE6> gpioE6;
VirtualGpioWrapper<GpioE7> gpioE7;
VirtualGpioWrapper<GpioE8> gpioE8;
VirtualGpioWrapper<GpioE9> gpioE9;
VirtualGpioWrapper<GpioE10> gpioE10;
VirtualGpioWrapper<GpioE11> gpioE11;
VirtualGpioWrapper<GpioE12> gpioE12;
VirtualGpioWrapper<GpioE13> gpioE13;
VirtualGpioWrapper<GpioE14> gpioE14;
VirtualGpioWrapper<GpioE15> gpioE15;

// Port H
//VirtualGpioWrapper<GpioH0> gpioH0;
//VirtualGpioWrapper<GpioH1> gpioH1;

namespace Hardware
{

// initialize the array of GPIOs
// we only construct those who are FreeIO on the STM32F407 Discovery Board
// others are null pointers and therefore invalid
NamedGpio const gpios[NumberOfPins] =
{
	{&gpioD3, "GND"},
	{&gpioD6, "GND (Audio)"},
	{&gpioD7, "Line Out R"},
	{&gpioB5, "Line Out L"},
	{&gpioB4, "Line In R"},

	{&gpioB7, "Line In L"},
	{&gpioB8, "N/C (Remote Sense)"},
	{&gpioE3, "Composite Video Out"},
	{&gpioD2, "S-Video Chrominance Output"},
	{&gpioC11, "S-Video Luminance Output"},

	{&gpioA15, "Audio Switch"},
	{&gpioA8, "Tx (to iPod)"},
	{&gpioC8, "Rx (from iPod)"},
	{&gpioC9, "N/C"},
	{&gpioC6, "GND (Digital)"},

	{&gpioD11, "USB GND"},
	{&gpioD10, "N/C"},
	{&gpioB15, "+3V3"},
	{&gpioB13, "+12V"},
	{&gpioB14, "+12V"},

	{&gpioB11, "Accessory Detect"},
	{&gpioB12, "Data A- (FireWire)"},
	{&gpioE7, "+5V (USB)"},
	{&gpioE10, "Data A+ (FireWire)"},
	{&gpioE9, "Data Minus (USB)"},

	{&gpioE12, "Data B- (FireWire)"},
	{&gpioE11, "Data Plus (USB)"},
	{&gpioE14, "Data B+ (FireWire)"},
	{&gpioE13, "GND"},
	{&gpioE15, "GND"},
};

}	// namespace Hardware
