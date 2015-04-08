/* motor_speed_up.c
*  A program to control a stepper motor(speed up ) through the GPIO on Raspberry Pi.
*
*  Auther: Darran Zhang
*  Rewrite: Tiger
*/

#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define CLOCKWISE 1
#define COUNTER_CLOCKWISE 2

void delayMS(int x);
void rotate(int* pins, int direction, int delay);
void stop(int* pins);

int main(int argc, char const *argv[])
{
	/* code */
	if (argc < 4)
	{
		/* code */
		printf("Usage example: ./motor 0 1 2 3 \n");
		return 1;
	}



	/* number of the pins which connected to the stepper motor driver board */
	int pinA = atoi(argv[1]);
	int pinB = atoi(argv[2]);
	int pinC = atoi(argv[3]);
	int pinD = atoi(argv[4]);

	int pins[4] = {pinA, pinB, pinC, pinD};

	if (-1 == wiringPiSetup())
	{
		/* code */
		printf("Setup wiringPi failed! \n");
		return 1;
	}


	/* set mode to output */
	pinMode(pinA, OUTPUT);
	pinMode(pinB, OUTPUT);
	pinMode(pinC, OUTPUT);
	pinMode(pinD, OUTPUT);


	delayMS(50);	// wait for a stable status
	int delay = 25;
	while (true)
	{
		for (int i = 0; i < 10; ++i)
		{
			/* code */
			rotate(pins, CLOCKWISE, delay);
		}
		delay--;
		if (delay < 4)
		{
			/* code */
			delay = 25;
			stop(pins);
			delayMS(500);
		}
	}


	return 0;
}

/* Suspend execution for x milliseconds intervals.
*  @param ms Milliseconds to sleep.
*/

void delayMS(int x)
{
	usleep(x * 1000);
}

/* Rotate the motor
*  @param pins    A pointer which points to the pins number array.
*  @param direction    CLOCKWISE for clockwise rotation, COUNTER_CLOCKWISE for counter clockwise rotation.
*  @param delay    The time intervals (in ms) to delay, and if the value is samller, the motor rotates faster.
*/
void rotate(int* pins, int direction, int delay)
{
	for (int i = 0; i < 4; ++i)
	{
		/* code */
		if (CLOCKWISE == direction)
		{
			/* code */
			for (int j = 0; j < 4; ++j)
			{
				/* code */
				if (j == i)
				{
					/* code */
					digitalWrite(pins[3 - j], 1);  // output a high level
				} else
				{
					digitalWrite(pins[3 - j], 0);  // output a low level
				}
			}
		} else if (COUNTER_CLOCKWISE == direction)
		{
			/* code */
			for (int j = 0; j < 4; ++j)
			{
				/* code */
				if (j == i)
				{
					/* code */
					digitalWrite(pins[j], 1);  // output a high level
				} else
				{
					digitalWrite(pins[j], 0);  // output a low level
				}
			}
		}
		delayMS(delay);
	}
}

/* Stop the motor.
*  @param pins     A pointer which points to the pins number array.
*/
void stop(int* pins)
{
	for (int i = 0; i < 4; ++i)
	{
		/* code */
		digitalWrite(pins[i], 0);  // output a low level
	}
}