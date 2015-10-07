This is a control program for the scientific payload for the One Month project in UAH's Space Hardware Club. It calculates altitude using pressure and temperature sensors.

From the altitude, the payload infers its flight state, and changes LED frequency and duty cycle. The LEDs stay on for the entire flight, as does transmission of telemetry data.
After reaching (~30 + initial altitude) feet altitude, it will assume it has been launched.
After breaching APOGEE_RELEASE (~670 feet), it is to light up a resistor, lovingly referred to as the hotwire, for 3 seconds. This melts the anchor line, detaching itself from the balloon.
It will descend back to earth using a parachute.
In the event of a total stop in altitude changes (the assumption is landing after descent if it measures 3 consecutive altitudes within 10 feet of each other), blare an audible beacon for retrieval.
It broadcasts flight data using an XBee radio back to a home station.
