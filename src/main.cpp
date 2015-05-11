// coding: utf-8
// ----------------------------------------------------------------------------

#include "hardware.hpp"

#undef	XPCC_LOG_LEVEL
#define	XPCC_LOG_LEVEL xpcc::log::DEBUG


// ----------------------------------------------------------------------------
int main(void)
{
	systemClock::enable();
	xpcc::cortex::SysTickTimer::enable();

	GpioOutputA2::connect(Hardware::Uart::Tx);
	Hardware::Uart::initialize<systemClock, Hardware::Uart::B115200>(10);

	LedOrange::setOutput(xpcc::Gpio::Low);
	LedRed::setOutput(xpcc::Gpio::Low);
	LedBlue::setOutput(xpcc::Gpio::Low);
	LedGreen::setOutput(xpcc::Gpio::Low);

	XPCC_LOG_DEBUG << "\n\nRESTART\n\n";

	xpcc::PeriodicTimer aliveTimer(200);

	while (1)
	{
		if (aliveTimer.execute())
		{
			LedBlue::toggle();
		}
	}

	return 0;
}
