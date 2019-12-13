# I2C NavKey Python library 
--------------------------------------------------------------------------------

## Introduction

Here you can find the library and some examples for Raspberry Pi.
For more details of the functionality of the board please read the [Datasheet](../I2CNavKey_v1.4.pdf) 

## Installation

The installation is very simple:

* Download the file [**i2cNavKeyLib.py** ](Source/i2cNavKeyLib.py) 
* Put the file in the folder where you have the source files.
* Import the library in your source files
``` python
import i2cNavKeyLib
```


## Initialization

The library makes available the class **i2cNavKeyLib**
For initialize the library you have to declare an instance of the class **i2cNavKeyLib** for each navkeys.
In the instance you have to declare the I2C address of the board
For example:

``` python
import smbus2
import i2cNavKeyLib

bus = smbus2.SMBus(1)
navkey = i2cNavKeyLib.i2cNavKeyLib(bus, 0x12)
```
In this example the I2C address is 0x12: jumpers A1 is soldered

## Callback Configuration

This library support the callback functionality.
There is the possibility to link a function to a specific interrupt of the I2C Encoder V2, in this way the function is automatically called when the I2C Encoder V2 generates an interrupts.

A callback function must be declared as the following:

```python
def NAME_OF_THE_FUNCTION():
```
There are 26 possible events:

| Event   | Description   |
|:-----------:|:----------------------------------|
| onArrowsPush | One of the 4 direction keys is pressed |
| onArrowsRelese	| One of the 4 direction keys is released |
| onUpPush | Arrow up is pressed |
| onUpRelease | Arrow up is released |
| onDownPush | Arrow down is pressed |
| onDownRelease | Arrow down is released |
| onRightPush | Arrow right is pressed |
| onRightRelease | Arrow right is released |
| onLeftPush | Arrow left is pressed |
| onLeftRelease | Arrow left is released |
| onCentralPush | central button is pressed |
| onCentralRelease | central button is released |
| onCentralDoublePush | central button is double pushed |
| onIncrement | The counter value is incremented |
| onDecrement | The counter value is decremented |
| onChange | The counter value is incremented or decremented |
| onMax | The counter value reach the maximum threshold |
| onMin | The counter value reach the minimum threshold |
| onMinMax | The counter value reach the maximum or minimum threshold |
| onGP1Rise | GP1 configured as input, rising edge |
| onGP1Fall | GP1 configured as input, falling edge |
| onGP2Rise | GP2 configured as input, rising edge  |
| onGP2Fall | GP2 configured as input, falling edge  |
| onGP3Rise | GP3 configured as input, rising edge  |
| onGP3Fall | GP3 configured as input, falling edge  |
| onFadeProcess | Fade process terminated |

#### Examples:

```python
navkey = i2cNavKeyLib.i2cNavKeyLib(bus, 0x12)

...

 # Simple callback that ist's called when the UP button is pressed and blink the LED on GP1 #
def Up_Button():
    navkey.writeGP1(100)
    print ('Button Up Pushed!')
    navkey.writeGP1(0)

 # Simple callback that ist's called when the Down button is pressed and blink the LED on GP2 # 
def Down_Button():
    navkey.writeGP2(100)
    print ('Button Down Pushed!')
    navkey.writeGP2(0)
...

navkey.onUpPush = Up_Button # Attach the event of UP button to the callback function#
navkey.onDownPush = Down_Button # Attach the event of Down button to the callback function#

}

```

If you need to remove the link with a callback, you just need to define:
```python
navkey.onUpPush = None
```

## Methods

### Initialization
#### begin(conf)
This is used for initialize the I2CNavKey by writing the configuration register.
The parameters can be concatenate in OR mode.
Possible parameters are the following:

| Parameter | Description |
|:----------:|:------------------------------------------------------ |
| INT_DATA | The Threshold, counter step and counter value are used with integer numbers |
| FLOAT_DATA | The Threshold, counter step and counter value are used with floating numbers |
| | |
| WRAP_ENABLE | Wrap enable. When the counter value reaches the CMAX+1, restart to the CMIN and vice versa |
| WRAP_DISABLE | Wrap disable. When the counter value reaches the CMAX or CMIN, the counter stops to increasing or decreasing |
| | |
| DIRE_LEFT | Rotate left side to increase the value counter |
| DIRE_RIGHT | Rotate right side to increase the value counter |
| | |
| IPUP_DISABLE | Disable the internall pull-up on the INT pin |
| IPUP_ENABLE | Enable the internall pull-up on the INT pin |
| | |
| CLK_STRECH_ENABLE | Enable the I2C clock stretch  |
| CLK_STRECH_DISABLE | Disable the I2C clock stretch  |
| | |
| EEPROM_BANK1 | Select the first EEPROM bank |
| EEPROM_BANK2 | Select the second EEPROM bank |
| | |
| RESET | Reset the board |

###### Examples:

```python
navkey.begin(i2cNavKeyLib.INT_DATA | i2cNavKeyLib.WRAP_ENABLE | i2cNavKeyLib.DIRE_RIGHT | i2cNavKeyLib.IPUP_ENABLE)
```

###  reset()
Reset of the board. 
In this command there is 8ms delay in order to make the board correctly restart.

### Configuration

#### GPx pins configuration

This 3 function are used for configure the GP pins. The parameter are the same for all of the 3 GP pins.
The interrupt configuration are used only when the pin is configured as digital input.

##### writeGP1conf(gp1)
##### writeGP2conf(gp2)
##### writeGP3conf(gp3)

| Parameter   | Description   |
|:-----------:|:-------------:|
|GP_PWM| Set the GP pin as PWM output|
|GP_OUT| Set the GP pin as digital output|
|GP_AN| Set the GP pin as analog input|
|GP_IN| Set the GP pin as digital input output|
|||
|GP_PULL_EN| Enable the internal pull-up of the pin|
|GP_PULL_DI| Disable the internal pull-up of the pin|
|||
|GP_INT_DI| Disable the pin interrupt|
|GP_INT_PE| Enable the interrupt at the positive edge|
|GP_INT_NE|  Enable the interrupt at the negative edge|
|GP_INT_BE|  Enable the interrupt at the positive and negative edge|

###### Examples:

```python
navkey.writeGP1conf(i2cNavKeyLib.GP_AN | i2cNavKeyLib.GP_PULL_DI | i2cNavKeyLib.GP_INT_DI)  # Configure the GP1 as analog input with the pull-up and the interrupt disable #
```

##### writeInterruptConfig(interrupt)

This method is used for enable or disable the interrupt source selectively. When an interrupt event occurs, the INT pin goes low and the event is stored in the status register.

| Parameter   | Description   |
|:-----------:|:-------------|
| UPR   | Arrow up is released |
| UPP   | Arrow up is pressed |
| DNR   | Arrow down is released |
| DNP   | Arrow down is pressed |
| RTR   | Arrow right is released |
| RTP   | Arrow right is pressed |
| LTR   | Arrow left is released |
| LTP   | Arrow left is pressed |
| CTRR  | Central button is released |
| CTRP  | Central button is pressed |
| CTRDP | Central button is double pushed |
| RINC  | Encoder is rotated in the increment direction  |
| RDEC  | Encoder is rotated in the decrement direction  |
| RMAX  | Maximum threshold is reached  |
| RMIN  | Minimum threshold is reached  |
| INT_2  | An event on the interrupt 2 register occurs |


###  void autoconfigInterrupt(void)

This method auto configures the **INTCONF** register according to the attached callback.
**For the proper use, must be called after the definition of the last event property.**

```python

navkey.onUpPush = Up_Button
navkey.onDownPush = Down_Button
navkey.onLeftPush = Left_Button
navkey.onRightPush = Right_Button
navkey.onCentralPush = Push_Button
navkey.onCentralDoublePush = DoublePush_Button
navkey.onChange = EncoderChange
navkey.onMax = EncoderMax
navkey.onMin = EncoderMin
  # Enable the I2C NavKey interrupts according to the previous attached callback #
navkey.autoconfigInterrupt()

```


##### writeDoublePushPeriod(dperiod)

This method is used for setting the window period **DPPERIOD** of the double push of the central button. When the value is 0, the double push option is disabled.
The I2C NavKey will multiplies this value by 10 (value x10).
###### Examples:

```python
navkey.writeDoublePushPeriod(50)  # Set a period for the double push of 500ms # 
```


##### writeFadeGP(fade)

This method is used for setting the fade speed **FADEGP** of the GP pins. It the value is 0 the fade option is disabled.

###### Examples:

```python
  navkey.writeFadeGP(5)  #GP Fade enabled with 5ms step 
```


### writeGammaGP1(gamma)
### writeGammaGP2(gamma)
### writeGammaGP3(gamma)

This method is used to set a gamma correction in case the GP pin is set to PWM

| Parameter   | Description   |
|:-----------:|:-------------|
| GAMMA_OFF   | Gamma correction is OFF |
| GAMMA_1   | Gamma is 1, in this case the PWM is linear |
| GAMMA_1_8   | Gamma is 1.8 |
| GAMMA_2   | Gamma is 2 |
| GAMMA_2_2   | Gamma is 2.2 |
| GAMMA_2_4   | Gamma is 2.4 |
| GAMMA_2_6 | Gamma is 2.6 |
| GAMMA_2_8   | Gamma is 2.8 |

#### Examples:

```python
  navkey.writeGammaGP1(i2cNavKeyLib.GAMMA_2)
  navkey.writeGammaGP2(i2cNavKeyLib.GAMMA_2)
  navkey.writeGammaGP3(i2cNavKeyLib.GAMMA_2)
```


### Status

##### updateStatus()
Read the I2CNavKey status register **ISTATUS**. In case of events the attached callback is called.
Return value is **true** in case of some event, otherwise is **false**
In case an event of the SSTATUS  register, the SSTATUS is automatically be read.

###### Examples:

```python
  if navkey.updateStatus() == True :
  # Something happens
  
```



##### readStatus(status)

Must be called after **updateStatus()**, this method is used for checking if some event occurs on the **ISTATUS** register.
Return value is **true** in case of the event occurred, otherwise is **false**
Possible parameters are:

| Parameter   | Description   |
|:-----------:|:-------------|
| UPR   | Arrow up is released |
| UPP   | Arrow up is pressed |
| DNR   | Arrow down is released |
| DNP   | Arrow down is pressed |
| RTR   | Arrow right is released |
| RTP   | Arrow right is pressed |
| LTR   | Arrow left is released |
| LTP   | Arrow left is pressed |
| CTRR  | Central button is released |
| CTRP  | Central button is pressed |
| CTRDP | Central button is double pushed |
| RINC  | Encoder is rotated in the increment direction  |
| RDEC  | Encoder is rotated in the decrement direction  |
| RMAX  | Maximum threshold is reached  |
| RMIN  | Minimum threshold is reached  |
| INT_2  | An event on the interrupt 2 register occurs |

###### Example:
```python

 if  navkey.updateStatus() == True :
      if  navkey.readStatus(UPR) == True :
      	print ('Button Up Pushed!') 
      
      if  navkey.readStatus(DNR) == True :
      	print ('Button Down Pushed!') 

      if  navkey.readStatus(RTR) == True :
      	print ('Button Left Pushed!') 

      if  navkey.readStatus(LTR) == True :
      	print ('Button Right Pushed!')  

      if  navkey.readStatus(PUSHP) == True :
      	print ('Encoder pushed!')  
        
	  if  navkey.readStatus(PUSHR) == True :
      	print ('Encoder released!')   

      if  navkey.readStatus(PUSHD) == True :
      	print ('Encoder double pushed!')

```


##### readStatus()

Return the status of the register **ESTATUS**



##### readInt2(status)
Must be called after **updateStatus()**, this method is used for check if some event occurred one the secondary interrupt status **SSTATUS** register.
Return value is **true** in case of the event occurred, otherwise is **false**
Possible parameter are:

| Parameter   | Description   |
|:-----------:|:-------------:|
| GP1_POS  | Positive edge on the GP1 pin |
| GP1_NEG  | Negative edge on the GP1 pin |
| GP2_POS  | Positive edge on the GP2 pin |
| GP2_NEG  |Negative edge on the GP2 pin |
| GP3_POS  | Positive edge on the GP3 pin|
| GP3_NEG  |Negative edge on the GP3 pin |
| FADE_INT |Fade process finished   |

###### Example:
```python
 if  navkey.updateStatus() == True :
      if  navkey.readInt2(GP1_POS)
        print("GP1 positive edge")
      
      if navkey.readInt2(GP1_NEG) == True :
        print ('GP1 negative edge ')
    

      if navkey.readInt2(GP2_POS)  == True :
          print('GP2 positive edge')
      
    
      if  navkey.readInt2(GP2_NEG) == True :
        print('GP2 negative edge ')
      

      if  navkey.readInt2(GP3_POS) == True :
        print('GP3 positive edge')
      

      if  navkey.readInt2(GP3_NEG) == True :
        print('GP3 negative edge ')
      

      if  navkey.readInt2(FADE_INT) == True :
        print('Fade process finished') 
      
```

##### readInt2Raw()

Return the status of the register **SSTATUS**



##### readFadeStatus(status)

When this function is called, it performs a I2C reading.
This function return **true** when the fade running, otherwise return **false**

| Parameter   | Description   |
|:-----------:|:-------------:|
| FADE_GP1  | Fade process status of the GP1 |
| FADE_GP2  | Fade process status of the GP2 |
| FADE_GP3  | Fade process status of the GP3 |



##### readFadeStatusRaw()

Return the value of the register **FSTATUS**.



### Reading methods
In this section are listed all the reading method available


##### readCounter32()
Return the counter value in the format **32bit int**, by reading all the 4 bytes of the counter value registers.



##### readCounter16()
Return the counter value in the format **16bit int**, by reading the 2 LSB  of the counter value registers.
Useful when the counter register is between the values -32768 to 32767.



##### readCounter8()
Return the counter value in the format **8bit int**, by reading the LSB byte of the counter value register.
Useful when the counter register is between the values -128 to 127



##### readCounterFloat()
Return the counter value in the format **float**, by reading all the 4 bytes of the counter value registers.
For using this function you have to configure the board with the parameter **FLOAT_DATA**.


##### readMax()
Return the maximum threshold in format **32bit int**, bye reading all the 4 bytes of the counter Max.



##### readMaxFloat()
Return the maximum threshold in format **float**, bye reading all the 4 bytes of the counter Max.



##### readMin()
Return the minimum threshold in format **32bit int**, by reading all the 4 byte of the counter Min.



##### readMinFloat()
Return the minimum  threshold in format **float**, bye reading all the 4 bytes of the counter Min.



##### readStep()
Return the minimum threshold in format **32bit int**, by reading all the 4 bytes of the ISTEP registers.



##### readStepFloat()
Return the step value in format **float**, by reading all the 4 bytes of the ISTEP registers .


##### readGP1()
Return the value of the GP1REG register. 
If the **GP1** is configured as input, it's possible to read the logic status of the pin: *1* when the pin is high, otherwise *0*.
If the **GP1** is configured as analog, it's possible to read the 8bit of the ADC.



##### readGP2()
Return the value of the GP2REG register. 
If the **GP2** is configured as input, it's possible to read the logic status of the pin: *1* when the pin is high, otherwise *0*.
If the **GP2** is configured as analog, it's possible to read the 8bit of the ADC.



##### readGP3()
Return the value of the GP3REG register. 
If the **GP3** is configured as input, it's possible to read the logic status of the pin: *1* when the pin is high, otherwise *0*.
If the **GP3** is configured as analog, it's possible to read the 8bit of the ADC. 


##### readDoublePushPeriod()
Return the value of the DPPERIOD register. 


##### readFadeGP()
Return the value of the FADEGP register. 


##### readIDCode()
Return the ID code of the I2C NavKey, that is 0x5B


##### readVersion()
Return the version of the board. 


##### readEEPROM(add)
Return the value of the EEPROM register. 
This function automatically manage the setting of the first and second memory bank.


### Writing methods

#####  writeCounter(value)
Write the counter value register with a  **32bit int** number. All of the 4 bytes are wrote.


#####  writeCounterFloat(value)
Write the counter value register with a  **float** number. All of the 4 bytes are wrote.



#####  writeMax(max)
Write the Max register with a  **32bit int** number. All of the 4 bytes are wrote.



#####  writeMax(max)
Write the Max register with a  **float** number. All of the 4 bytes are wrote.



#####  writeMin(min)
Write the Min register with a **32bit int** number. All of the 4 bytes are wrote.



#####  writeMinFloat(min)
Write the Min register with a **float** number. All of the 4 bytes are wrote.



#####  writeStep(step)
Write the increment step  with a  **32bit int** number. All of the 4 bytes are wrote.



#####  writeStepFloat(step)
Write the increment step with a  **float** number. All of the 4 bytes are wrote.


##### writeGP1(gp1)
Write the GP1REG register.
If the GP1 is configure as PWM with this method it's possible to write the PWM value.
If the GP1 is configure as output with this method it's possible to write the logic status: 1 for high, while 0 for low.



##### writeGP2(gp2)
Write the GP2REG register.
If the GP2 is configure as PWM with this method it's possible to write the PWM value.
If the GP2 is configure as output with this method it's possible to write the logic status: 1 for high, while 0 for low.



##### writeGP3(gp3)
Write the GP2REG register.
If the GP2 is configure as PWM with this method it's possible to write the PWM value.
If the GP2 is configure as output with this method it's possible to write the logic status: 1 for high, while 0 for low.



##### writeDoublePushPeriod(dperiod)
Write the DPPERIOD register.



##### writeFadeGP(fade)
Write the FADEGP register.


##### writeGammaGP1(gamma)
Configure the gamma correction for the GP1 pin

##### writeGammaGP2(gamma)
Configure the gamma correction for the GP2 pin

##### writeGammaGP3(gamma)
Configure the gamma correction for the GP3 pin


##### writeEEPROM(add, data)
Write the EEPROM memory.
The input parameter *add* is the address. This method automatically change the first or the second bank.
The input parameter *data* is the data that will be written.

