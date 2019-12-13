import smbus2
import RPi.GPIO as GPIO
from time import sleep
import i2cNavKeyLib


def Up_Button():
    print ('Button Up Pushed!')
    navkey.writeGP1(100)
    navkey.writeGP1(0)

    
def Down_Button():
    print ('Button Down Pushed!')
    navkey.writeGP1(100)
    navkey.writeGP1(0)

    
def Left_Button():
    print ('Button Left Pushed!')
    navkey.writeGP1(100)
    navkey.writeGP1(0)

    
def Right_Button():
    print ('Button Right Pushed!')
    navkey.writeGP1(100)
    navkey.writeGP1(0)

    
def Push_Button():
    print ('Central Pushed!')
    navkey.writeGP1(100)
    navkey.writeGP1(0)

    
def DoublePush_Button():
    print ('Central Double Pushed!')
    navkey.writeGP1(100)
    navkey.writeGP1(0)

    
def EncoderChange():
    print ('Ring Changed: %d' % (navkey.readCounter32()))
    navkey.writeGP2(100)
    navkey.writeGP2(0)

    
def EncoderMax():
    print ('Ring max!')
    navkey.writeGP3(100)
    navkey.writeGP3(0)

    
def EncoderMin():
    print ('Ring min!')
    navkey.writeGP3(100)
    navkey.writeGP3(0)

    
def NavKey_INT(self):
    navkey.updateStatus()


GPIO.setmode(GPIO.BCM)
bus = smbus2.SMBus(1)
INT_pin = 4
GPIO.setup(INT_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

navkey = i2cNavKeyLib.i2cNavKeyLib(bus, 0x10) # Write here the I2C address of the NavKey #

encconfig = (i2cNavKeyLib.INT_DATA | i2cNavKeyLib.WRAP_ENABLE | i2cNavKeyLib.DIRE_RIGHT | i2cNavKeyLib.IPUP_ENABLE)
navkey.begin(encconfig)

navkey.writeCounter(0)
navkey.writeMax(35)
navkey.writeMin(-20)
navkey.writeStep(1)
navkey.writeDoublePushPeriod(50)

navkey.writeGP1conf(i2cNavKeyLib.GP_PWM)
navkey.writeGP2conf(i2cNavKeyLib.GP_PWM)
navkey.writeGP3conf(i2cNavKeyLib.GP_PWM)

navkey.writeGammaGP1(i2cNavKeyLib.GAMMA_2)
navkey.writeGammaGP2(i2cNavKeyLib.GAMMA_2)
navkey.writeGammaGP3(i2cNavKeyLib.GAMMA_2)

navkey.onUpPush = Up_Button
navkey.onDownPush = Down_Button
navkey.onLeftPush = Left_Button
navkey.onRightPush = Right_Button
navkey.onCentralPush = Push_Button
navkey.onCentralDoublePush = DoublePush_Button
navkey.onChange = EncoderChange
navkey.onMax = EncoderMax
navkey.onMin = EncoderMin

navkey.autoconfigInterrupt()
print ('Board ID code: 0x%X' % (navkey.readIDCode()))
print ('Board Version: 0x%X' % (navkey.readVersion()))

navkey.writeGP1(100)
navkey.writeGP2(0)
navkey.writeGP3(0)
sleep(0.3)
navkey.writeGP1(0)
navkey.writeGP2(100)
navkey.writeGP3(0)
sleep(0.3)
navkey.writeGP1(0)
navkey.writeGP2(0)
navkey.writeGP3(100)
sleep(0.3)
navkey.writeGP1(0)
navkey.writeGP2(0)
navkey.writeGP3(0)


GPIO.add_event_detect(INT_pin, GPIO.FALLING, callback=NavKey_INT)

while True:
  #  if GPIO.input(INT_pin) == False: #
   #     NavKey_INT() #
    pass
