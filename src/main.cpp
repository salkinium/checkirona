// coding: utf-8
// ----------------------------------------------------------------------------

#include "hardware.hpp"

using namespace Hardware;

void
print30pins(uint8_t id, uint32_t value)
{
	for (int ii=0; ii < NumberOfPins; ii++)
	{
		if (id == ii) {
			serial << "X ";
		} else {
			serial << ((value & (1 << ii)) ? "1 " : "  ");
		}
	}
}

void
printPin(uint8_t id)
{
	serial.printf("Pin %2d: ", (id+1));
	print30pins(id, connectionMatrix[id]);
	serial << "  " << gpios[id].name << "\n";

	// print30pins(id, down);
}

void
printConnector()
{
	for (int ii=0; ii < NumberOfPins; ii++)
	{
		serial.printf("%2d  ", ii+1);
	}
	serial << "\n";
	for (int ii=0; ii < NumberOfPins; ii++)
	{
		serial << " |  ";
	}
	serial << "\n";
}

constexpr uint8_t lines = 30;
constexpr uint8_t colums = 4*NumberOfPins;
uint32_t flattened[lines];
char scratch[lines][colums+1];
bool too_many = false;

void
printIntoScratch(uint8_t line, uint8_t pos, const char *string)
{
	while(pos < colums and *string != '\0')
	{
		scratch[line][pos++] = *string++;
	}
}

void
printConnection(uint8_t from, uint8_t to)
{
	uint32_t flat = 0;
	for (int ii=from+1; ii <= to; ii++)
	{
		flat |= (1 << ii);
	}
	int line = 0;
	while (line < lines and flattened[line] & flat) {
		line++;
	}
	if (line >= lines) {
		too_many = true;
		return;
	}
	flattened[line] |= flat;

	printIntoScratch(line, from*4+2, "\\_");
	for (int ii=from+1; ii < to; ii++)
	{
		printIntoScratch(line, ii*4, "____");
	}
	printIntoScratch(line, to*4, "/");
}

void
printAllConnections()
{
	for (int ii=0; ii < lines; ii++)
	{
		if (flattened[ii])
		{
			serial << scratch[ii] << "\n";
		}
	}

	if (too_many)
		serial << "\nThere were more connections than could be visualized!";
}

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

	LedGreen::setOutput(xpcc::Gpio::High);

	std::memset(&flattened, 0, lines * 4);
	// fill with spaces
	std::memset(scratch, ' ', lines * (colums+1));
	// but the last one must be zero
	for (int ii=0; ii < lines; ii++)
	{
		scratch[ii][colums] = 0;
	}

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
			xpcc::delayMicroseconds(400);
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
			xpcc::delayMicroseconds(400);
			// if pin j is high, it is _not_ connected to pin i
			valueDown |= ((gpios[jj].gpio->read() ? 0 : 1) << jj);
			gpios[jj].gpio->configure(Gpio::InputType::Floating);
		}

		gpios[ii].gpio->setInput(Gpio::InputType::Floating);

		connectionMatrix[ii] = valueDown & valueUp;
	}

	LedOrange::reset();
	LedGreen::reset();

	// ANALYSIS

	// Magic ANSI escape codes clear the screen
	serial << "\033[2J\033[1;1H";

	uint32_t allConnections = 0;
	// this magic number contains the desired ("vetted") connections.
	static constexpr uint32_t correctConnections = 0b110000000001101100010000000011;

	// print connection matrix
	serial << "Adjacency Matrix:\n";
	for (int ii=0; ii < NumberOfPins; ii++)
	{
		allConnections |= connectionMatrix[ii];
		printPin(ii);
	}

	// print flattened connectors
	serial << "\nConnector View:\n";
	printConnector();

	for (int ii=0; ii < NumberOfPins; ii++)
	{
		if (allConnections & (1 << ii))
		{
			for (int jj=ii+1; jj < NumberOfPins; jj++)
			{
				if (allConnections & (1 << jj)) {
					printConnection(ii, jj);
					ii = jj-1;
					break;
				}
			}
		}
	}

	printAllConnections();

	bool ok = (allConnections == correctConnections);

	if (ok)	{
		LedBlue::set();
		serial << "\n\nThis connector is ok!" << xpcc::endl;
	} else {
		LedRed::set();
		serial << "\n\n#### This connector is _NOT_ ok! ####" << xpcc::endl;
	}


	while (1)
		;

	return 0;
}
