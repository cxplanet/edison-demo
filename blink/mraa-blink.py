import mraa
import time

# Setup
led = mraa.Gpio(13)
led.dir(mraa.DIR_OUT)

# Loop
while True:
    led.write(1)
    time.sleep(0.5)
    led.write(0)
    time.sleep(0.5)

