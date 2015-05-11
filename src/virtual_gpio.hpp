// coding: utf-8

#ifndef XPCC_STM32_VIRTUAL_GPIO_HPP
#define XPCC_STM32_VIRTUAL_GPIO_HPP

#include <xpcc/architecture/interface/gpio.hpp>
#include "stm32f4_discovery.hpp"

namespace xpcc
{

namespace stm32
{

class VirtualGpio : public Gpio, public xpcc::GpioIO
{
public:
	virtual void
	configure(OutputType type, OutputSpeed speed = OutputSpeed::MHz50) = 0;

	virtual void
	configure(InputType type) = 0;

public:
	VirtualGpio() : isInverted(false) {}

	/// configure pin as input
	virtual void
	setInput() = 0;

	void
	setInput(InputType type)
	{
		configure(type);
		setInput();
	}

	/// read input
	virtual bool
	read() = 0;

public:
	/// configure pin as output
	virtual void
	setOutput() = 0;

	/// configure pin as output and set high or low
	void
	setOutput(bool value)
	{
		set(value);
		setOutput();
	}

	void
	setOutput(OutputType type, OutputSpeed speed = OutputSpeed::MHz50)
	{
		configure(type, speed);
		setOutput();
	}

	/// set output to high level
	virtual void
	set() = 0;

	/// set output to high or low level
	void
	set(bool value)
	{
		if (value) set();
		else reset();
	}

	/// set output to low level
	virtual void
	reset() = 0;

	/// returns if the pin is logically set
	virtual bool
	isSet() = 0;

	/// toggle output level
	void
	toggle()
	{
		if (isSet()) reset();
		else set();
	}

public:
	virtual xpcc::Gpio::Direction
	getDirection() = 0;

	void
	setInverted(bool inverted = true)
	{
		isInverted = inverted;
	}

protected:
	bool isInverted;
};

template< class Pin >
class VirtualGpioWrapper : public VirtualGpio
{
public:
	void
	configure(OutputType type, OutputSpeed speed = OutputSpeed::MHz50) override
	{
		Pin::configure(type, speed);
	}

	void
	configure(InputType type) override
	{
		Pin::configure(type);
	}

public:
	using VirtualGpio::setInput;

	void
	setInput() override
	{
		Pin::setInput();
	}

	bool
	read() override
	{
		bool value =  Pin::read();
		return isInverted ? !value : value;
	}

public:
	using VirtualGpio::setOutput;
	using VirtualGpio::set;
	using VirtualGpio::toggle;

	void
	setOutput() override
	{
		Pin::setOutput();
	}

	void
	set() override
	{
		// "normal" = !(isInverted == false) -> true
		Pin::set(!isInverted);
	}

	void
	reset() override
	{
		// "normal" = (isInverted == false) -> false
		Pin::set(isInverted);
	}

	bool
	isSet() override
	{
		bool value = Pin::isSet();
		return isInverted ? !value : value;
	}

public:
	Direction
	getDirection() override
	{
		return Pin::getDirection();
	}

	using VirtualGpio::setInverted;
};

}	// namespace stm32

}	// namespace xpcc

#endif	// XPCC_STM32_VIRTUAL_GPIO_HPP
