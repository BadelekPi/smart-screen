#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#define MAXTIMINGS	85
#define DHTPIN		7
int dht11_dat[5] = { 0, 0, 0, 0, 0 };
float	f; 
struct receiveData {
	int humidity_high, humidity_low, temperature_high, temperature_low;
};

struct receiveData read_dht11_dat()
{	
	struct receiveData S;
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	// float	f; 
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;

	pinMode( DHTPIN, OUTPUT );
	digitalWrite( DHTPIN, LOW );
	delay( 18 );
	digitalWrite( DHTPIN, HIGH );
	delayMicroseconds( 40 );
	pinMode( DHTPIN, INPUT );
 
	for ( i = 0; i < MAXTIMINGS; i++ )
	{
		counter = 0;
		while ( digitalRead( DHTPIN ) == laststate )
		{
			counter++;
			delayMicroseconds( 1.5 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead( DHTPIN );
 
		if ( counter == 255 )
			break;
 
		if ( (i >= 4) && (i % 2 == 0) )
		{
			dht11_dat[j / 8] <<= 1;
			if ( counter > 16 )
				dht11_dat[j / 8] |= 1;
			j++;
		}
	}
 
	if ( (j >= 40) &&
	     (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
	{
		f = dht11_dat[2] * 9. / 5. + 32;
		
		if ( dht11_dat[4] != 0 )
			S.humidity_high = dht11_dat[0];
			S.humidity_low = dht11_dat[1];
			S.temperature_high = dht11_dat[2];
			S.temperature_low = dht11_dat[3];
			// printf( "Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n",
			// S.humidity_high, S.humidity_low, S.temperature_high, S.temperature_low, f );
			return S;
	}
}
 
int main( void )
{	
	struct receiveData R;
	printf( "Raspberry Pi wiringPi DHT11 Temperature test program\n" );
	if ( wiringPiSetup() == -1 )
		exit( 1 );
 
	while ( 1 )
	{
		R = read_dht11_dat();
		f = dht11_dat[2] * 9. / 5. + 32;
		printf( "Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n",
			R.humidity_high, R.humidity_low, R.temperature_high, R.temperature_low, f );
		delay( 1000 ); 
	}
 
	return(0);
}
