#ifndef GPIO_H
#define GPIO_H

class GPIO
{
	// File descriptor
	int fd;

public:

	/**
	 * Class constructor.
	 *
	 * @param number
	 *	Port number for GPIO.
	 */
	GPIO(int number);

	/**
	 * Class destructor.
	 */
	~GPIO();

	/**
	 * Generate a PWM signal, blocking the caller while the signal is being
	 * generated.
	 *
	 * @param period
	 *	PWM period in microseconds.
	 *
	 * @param pulse
	 *	Duration of the pulse in microseconds.
	 *
	 * @param num_periods
	 *	Number of periods to generate.
	 */
	void GeneratePWM(int period, int pulse, int num_periods);

        void GenerateVariablePWM(int period, int first_pulse, int last_pulse, int num_periods);
};

#endif

