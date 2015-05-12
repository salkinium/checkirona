// coding: utf-8
// ----------------------------------------------------------------------------

#include "hardware.hpp"

#undef	XPCC_LOG_LEVEL
#define	XPCC_LOG_LEVEL xpcc::log::DEBUG

using namespace Hardware;

// ----------------------------------------------------------------------------
int main(void)
{
	systemClock::enable();
	xpcc::cortex::SysTickTimer::enable();

	GpioOutputA2::connect(Uart::Tx);
	Uart::initialize<systemClock, Uart::B115200>(10);

	LedOrange::setOutput(xpcc::Gpio::Low);
	LedRed::setOutput(xpcc::Gpio::Low);
	LedBlue::setOutput(xpcc::Gpio::Low);
	LedGreen::setOutput(xpcc::Gpio::Low);

	XPCC_LOG_DEBUG << "\n\nRESTART\n\n";
	LedGreen::setOutput(xpcc::Gpio::High);

	for (NamedGpio gpio : gpios)
	{
		gpio.gpio->setInput(Gpio::InputType::Floating);
	}

	for (int ii=0; ii < NumberOfPins; ii++)
	{
		LedOrange::toggle();
		gpios[ii].gpio->setOutput(xpcc::Gpio::High);

		uint32_t valueUp = 0;
		for (int jj=0; jj < NumberOfPins; jj++)
		{
			if (jj == ii) continue;

			gpios[jj].gpio->configure(Gpio::InputType::PullDown);
			xpcc::delayMilliseconds(1);
			// if pin j is high, it is connected to pin i
			valueUp |= ((gpios[jj].gpio->read() ? 1 : 0) << jj);
			gpios[jj].gpio->configure(Gpio::InputType::Floating);
		}

		gpios[ii].gpio->setOutput(xpcc::Gpio::Low);

		uint32_t valueDown = 0;
		for (int jj=0; jj < NumberOfPins; jj++)
		{
			if (jj == ii) continue;

			gpios[jj].gpio->configure(Gpio::InputType::PullUp);
			xpcc::delayMilliseconds(1);
			// if pin j is high, it is _not_ connected to pin i
			valueDown |= ((gpios[jj].gpio->read() ? 0 : 1) << jj);
			gpios[jj].gpio->configure(Gpio::InputType::Floating);
		}

		gpios[ii].gpio->setInput(Gpio::InputType::Floating);

		connectionMatrix[ii] = valueDown & valueUp;
	}

	LedOrange::reset();
	LedGreen::reset();

	bool isEmpty = true;

	for (uint32_t value : connectionMatrix)
	{
		if (value != 0) isEmpty = false;
	}

	if (isEmpty)	LedBlue::set();
	else			LedRed::set();

	while (1)
		;

	return 0;
}
