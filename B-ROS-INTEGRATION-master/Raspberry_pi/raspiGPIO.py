#blink with RPi.GPIO library
import RPi.GPIO as GPIO
import time
ledPin = 16
GPIO.setmode(GPIO.BOARD) 
GPIO.setwarnings(False)
GPIO.setup(ledPin,GPIO.OUT)

while True:
    GPIO.output(ledPin, GPIO.HIGH)
    print('LED ON')
    time.sleep(1)
    GPIO.output(ledPin, GPIO.LOW)
    print('LED OFF')
    time.sleep(1)
