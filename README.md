## Wiring DHT11
<p align="center"><img width="506" height="698" src="doc/dht11_wiring.png"></p>

Check data definition:
8bit Humidity integer data + 8bit Humidity fraction data + 8bit Temperature integer data + 8bit Temperature fraction data”.The 8 bit check bit is equal to the last 8 bits of the result.

The received 40 bits of data are：
Humidity_High + Humidity_Low + Temperature_High + Temperature_Low = Check_Sum