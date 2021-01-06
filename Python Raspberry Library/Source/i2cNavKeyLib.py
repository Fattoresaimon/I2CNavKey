import smbus
import time
import struct
from time import sleep

# Encoder register definition#
REG_GCONF = 0x00
REG_GP1CONF = 0x01
REG_GP2CONF = 0x02
REG_GP3CONF = 0x03
REG_INTCONFB2 = 0x04
REG_INTCONFB1 = 0x05
REG_STATUSB2 = 0x06
REG_STATUSB1 = 0x07
REG_SSTATUS = 0x08
REG_FSTATUS = 0x09
REG_CVALB4 = 0x0A
REG_CVALB3 = 0x0B
REG_CVALB2 = 0x0C
REG_CVALB1 = 0x0D
REG_CMAXB4 = 0x0E
REG_CMAXB3 = 0x0F
REG_CMAXB2 = 0x10
REG_CMAXB1 = 0x11
REG_CMINB4 = 0x12
REG_CMINB3 = 0x13
REG_CMINB2 = 0x14
REG_CMINB1 = 0x15
REG_ISTEPB4 = 0x16
REG_ISTEPB3 = 0x17
REG_ISTEPB2 = 0x18
REG_ISTEPB1 = 0x19
REG_GP1REG = 0x1A
REG_GP2REG = 0x1B
REG_GP3REG = 0x1C
REG_DPPERIOD = 0x1D
REG_FADEGP = 0x1E
REG_GAMMAGP1 = 0x1F
REG_GAMMAGP2 = 0x20
REG_GAMMAGP3 = 0x21
REG_IDCODE = 0x70
REG_VERSION = 0x71
REG_EEPROMS = 0x80

# Encoder configuration bit. Use with GCONF #
FLOAT_DATA = 0x01
INT_DATA = 0x00
WRAP_ENABLE = 0x02
WRAP_DISABLE = 0x00
DIRE_LEFT = 0x04
DIRE_RIGHT = 0x00
IPUP_DISABLE = 0x08
IPUP_ENABLE = 0x00
CLK_STRECH_ENABLE = 0x10
CLK_STRECH_DISABLE = 0x00
EEPROM_BANK1 = 0x20
EEPROM_BANK2 = 0x00
RESET = 0x80

# Encoder status bits and setting. Use with: INTCONF for set and with ESTATUS for read the bits  #
UPR = 0x0001
UPP = 0x0002
DNR = 0x0004
DNP = 0x0008
RTR = 0x0010
RTP = 0x0020
LTR = 0x0040
LTP = 0x0080
CTRR = 0x0100
CTRP = 0x0200
CTRDP = 0x0400
RINC = 0x0800
RDEC = 0x1000
RMAX = 0x2000
RMIN = 0x4000
INT_2 = 0x8000

# Encoder Int2 bits. Use to read the bits of I2STATUS  #
GP1_POS = 0x01
GP1_NEG = 0x02
GP2_POS = 0x04
GP2_NEG = 0x08
GP3_POS = 0x10
GP3_NEG = 0x20
FADE_INT = 0x40

# Encoder Fade status bits. Use to read the bits of FSTATUS  #
FADE_GP1 = 0x01
FADE_GP2 = 0x02
FADE_GP3 = 0x04

# GPIO Configuration. USe with GP1CONF,GP2CONF,GP3CONF #
GP_PWM = 0x00
GP_OUT = 0x01
GP_AN = 0x02
GP_IN = 0x03

GP_PULL_EN = 0x04
GP_PULL_DI = 0x00

GP_INT_DI = 0x00
GP_INT_PE = 0x08
GP_INT_NE = 0x10
GP_INT_BE = 0x18

# Gamma configuration #

GAMMA_1 = 0
GAMMA_1_8 = 1
GAMMA_2 = 2
GAMMA_2_2 = 3
GAMMA_2_4 = 4
GAMMA_2_6 = 5
GAMMA_2_8 = 6


class i2cNavKeyLib:

    # Event #
    onArrowsPush = None
    onArrowsRelese = None
    onUpPush = None
    onUpRelease = None
    onDownPush = None
    onDownRelease = None
    onRightPush = None
    onRightRelease = None
    onLeftPush = None
    onLeftRelease = None
    onCentralPush = None
    onCentralRelease = None
    onCentralDoublePush = None
    onIncrement = None
    onDecrement = None
    onChange = None
    onMax = None
    onMin = None
    onMinMax = None
    onGP1Rise = None
    onGP1Fall = None
    onGP2Rise = None
    onGP2Fall = None
    onGP3Rise = None
    onGP3Fall = None
    onFadeProcess = None

    stat = 0
    stat2 = 0
    gconf = 0

# Class constructor 

    def __init__(self, bus, add):
        self.i2cbus = bus
        self.i2cadd = add

# Used for initialize the NavKey
    def begin(self, conf):
        self.writeNavKey8(REG_GCONF, conf & 0xFF)
        self.gconf = conf

    def reset(self) :
        self.writeNavKey8(REG_GCONF, 0x80)
        sleep(0.001)

# Call the attached callback if it is defined #
    def eventCaller(self, event) :
        if event:
            event()

# Return true if the status of the NavKey changed, otherwise return false #
# Call also the related callback if defined #
    def updateStatus(self) :
        self.stat = self.readNavKey16(REG_STATUSB2)
        
        if (self.stat == 0):
            self.stat2 = 0
            return False

        if (self.stat & UPR) != 0 :
            self.eventCaller (self.onUpRelease)
            self.eventCaller (self.onArrowsRelese)

        if (self.stat & UPP) != 0 :
            self.eventCaller (self.onUpPush)
            self.eventCaller (self.onArrowsRelese)

        if (self.stat & DNR) != 0 :
            self.eventCaller (self.onDownRelease)
            self.eventCaller (self.onArrowsRelese)
            
        if (self.stat & DNP) != 0 :
            self.eventCaller (self.onDownPush)
            self.eventCaller (self.onArrowsRelese)
            
        if (self.stat & RTR) != 0 :
            self.eventCaller (self.onRightRelease)
            self.eventCaller (self.onArrowsRelese)

        if (self.stat & RTP) != 0 :
            self.eventCaller (self.onRightPush)
            self.eventCaller (self.onArrowsRelese)

        if (self.stat & LTR) != 0 :
            self.eventCaller (self.onLeftRelease)
            self.eventCaller (self.onArrowsRelese)
            
        if (self.stat & LTP) != 0 :
            self.eventCaller (self.onLeftPush)
            self.eventCaller (self.onArrowsRelese)
            
        if (self.stat & CTRR) != 0 :
            self.eventCaller (self.onCentralRelease)

        if (self.stat & CTRP) != 0 :
            self.eventCaller (self.onCentralPush)
            
        if (self.stat & CTRDP) != 0 :
            self.eventCaller (self.onCentralDoublePush)

        if (self.stat & RINC) != 0 :
            self.eventCaller (self.onIncrement)
            self.eventCaller (self.onChange)

        if (self.stat & RDEC) != 0 :
            self.eventCaller (self.onDecrement)
            self.eventCaller (self.onChange)

        if (self.stat & RMAX) != 0 :
            self.eventCaller (self.onMax)
            self.eventCaller (self.onMinMax)

        if (self.stat & RMIN) != 0 :
            self.eventCaller (self.onMin)
            self.eventCaller (self.onMinMax)


        if (self.stat & INT_2) != 0 :
            self.stat2 = self.readNavKey8(REG_SSTATUS)
            if (self.stat2 == 0) :
                return True

            if (self.stat2 & GP1_POS) != 0 :
                self.eventCaller (self.onGP1Rise)

            if (self.stat2 & GP1_NEG) != 0 :
                self.eventCaller (self.onGP1Fall)

            if (self.stat2 & GP2_POS) != 0 :
                self.eventCaller (self.onGP2Rise)

            if (self.stat2 & GP2_NEG) != 0 :
                self.eventCaller (self.onGP2Fall)

            if (self.stat2 & GP3_POS) != 0 :
                self.eventCaller (self.onGP3Rise)

            if (self.stat2 & GP3_NEG) != 0 :
                self.eventCaller (self.onGP3Fall)

            if (self.stat2 & FADE_INT) != 0 :
                self.eventCaller (self.onFadeProcess)
        return True

#********************************* Read functions ***********************************#

# Return the GP1 Configuration#
    def readGP1conf(self) :
        return (self.readNavKey8(REG_GP1CONF))

# Return the GP1 Configuration#
    def readGP2conf(self) :
        return (self.readNavKey8(REG_GP2CONF))

# Return the GP1 Configuration#
    def readGP3conf(self) :
        return (self.readNavKey8(REG_GP3CONF))

# Return the INT pin configuration#
    def readInterruptConfig(self) :
        return (self.readNavKey16(REG_INTCONFB2))

# Check if a particular status match, return true is match otherwise false. Before require updateStatus() #
    def readStatus(self, status) :
        if (self.stat & status) != 0 :
            return True
        else:
            return False

# Return the status of the encoder #
    def readStatusRaw(self) :
        return self.stat

# Check if a particular status of the Int2 match, return true is match otherwise false. Before require updateStatus() #
    def readInt2(self, status) :
        if (self.stat2 & status) != 0 :
            return True
        else:
            return False

# Return the Int2 status of the encoder. Before require updateStatus()  #
    def readInt2Raw(self):
        return self.stat2

# Return Fade process status  #
    def readFadeStatusRaw(self):
        return self.readNavKey8(REG_FSTATUS)

# Check if a particular status of the Fade process match, return true is match otherwise false. #
    def readFadeStatus(self, status):
        if (self.readNavKey8(REG_FSTATUS) & status) == 1 :
            return True
        else:
            return False

# Return the 32 bit value of the encoder counter  #
    def readCounterFloat(self) :
        return (self.readNavKeyFloat(REG_CVALB4))

# Return the 32 bit value of the encoder counter  #
    def readCounter32(self) :
        return (self.readNavKey32(REG_CVALB4))

# Return the 16 bit value of the encoder counter  #
    def readCounter16(self) :
        return (self.readNavKey16(REG_CVALB2))

# Return the 8 bit value of the encoder counter  #
    def readCounter8(self) :
        return (self.readNavKey8(REG_CVALB1))

# Return the Maximum threshold of the counter #
    def readMax(self) :
        return (self.readNavKey32(REG_CMAXB4))

# Return the Minimum threshold of the counter #
    def readMin(self) :
        return (self.readNavKey32(REG_CMINB4))

# Return the Maximum threshold of the counter #
    def readMaxFloat(self) :
        return (self.readNavKeyFloat(REG_CMAXB4))

# Return the Minimum threshold of the counter #
    def readMinFloat(self) :
        return (self.readNavKeyFloat(REG_CMINB4))

# Return the Steps increment #
    def readStep(self) :
        return (self.readNavKey16(REG_ISTEPB4))

# Return the Steps increment, in float variable #
    def readStepFloat(self) :
        return (self.readNavKeyFloat(REG_ISTEPB4))

# Read GP1 register value #
    def readGP1(self) :
        return (self.readNavKey8(REG_GP1REG))

# Read GP2 register value #
    def readGP2(self) :
        return (self.readNavKey8(REG_GP2REG))

# Read GP3 register value #
    def readGP3(self) :
        return (self.readNavKey8(REG_GP3REG))

# Read Anti-bouncing period register #
    def readAntibouncingPeriod(self) :
        return (self.readNavKey8(REG_ANTBOUNC))

# Read Double push period register #
    def readDoublePushPeriod(self) :
        return (self.readNavKey8(REG_DPPERIOD))

# Read the fade period of the GP LED#
    def readFadeGP(self):
        return self.readNavKey8(REG_FADEGP)

# Read the ID code #
    def readIDCode(self):
        return self.readNavKey8(REG_IDCODE)

# Read the Version code #
    def readVersion(self):
        return self.readNavKey8(REG_VERSION)

# Read the EEPROM memory#
    def readEEPROM(self, add):

        if add <= 0x7f:
            if (self.gconf & EEPROM_BANK1) != 0:
                self.gconf = self.gconf & 0xBF
                self.writeNavKey8(REG_GCONF, self.gconf)

            data = self.readNavKey8((REG_EEPROMS + add))
        else:
            if (self.gconf & EEPROM_BANK1) == 0:
                self.gconf = self.gconf | 0x40
                self.writeNavKey8(REG_GCONF, self.gconf)

            data = self.readNavKey8(add)

        sleep(0.001)
        return (data)

#********************************* Write functions ***********************************#
# Write the GP1 configuration#
    def writeGP1conf(self, gp1) :
        self.writeNavKey8(REG_GP1CONF, gp1)

# Write the GP2 configuration#
    def writeGP2conf(self, gp2) :
        self.writeNavKey8(REG_GP2CONF, gp2)

# Write the GP3 configuration#
    def writeGP3conf(self, gp3) :
        self.writeNavKey8(REG_GP3CONF, gp3)

# Write the interrupt configuration #
    def writeInterruptConfig(self, interrupt) :
        self.writeNavKey16(REG_INTCONFB2, interrupt)

# Auto-configure the interrupt register according to the callback declared #
    def autoconfigInterrupt(self) :
        reg = 0

        if (self.onArrowsPush != None):
            reg = reg | UPP | DNP | RTP | LTP

        if (self.onArrowsRelese != None):
            reg = reg | UPR | DNR | RTR | LTR
            
        if (self.onUpPush != None):
            reg = reg | UPP
        
        if (self.onUpRelease != None):
            reg = reg | UPR  
            
        if (self.onDownPush != None):
            reg = reg | DNP
        
        if (self.onDownRelease != None):
            reg = reg | DNR  
            
        if (self.onRightPush != None):
            reg = reg | RTP
        
        if (self.onRightRelease != None):
            reg = reg | RTR             
            
        if (self.onLeftPush != None):
            reg = reg | LTP
        
        if (self.onLeftRelease != None):
            reg = reg | LTR             

        if (self.onCentralPush != None):
            reg = reg | CTRP             
            
        if (self.onCentralRelease != None):
            reg = reg | CTRR
        
        if (self.onCentralDoublePush != None):
            reg = reg | CTRDP             

        if (self.onIncrement != None):
            reg = reg | RINC

        if (self.onDecrement != None):
            reg = reg | RDEC

        if (self.onChange != None):
            reg = reg | RINC
            reg = reg | RDEC

        if (self.onMax != None):
            reg = reg | RMAX

        if (self.onMin != None):
            reg = reg | RMIN

        if (self.onMinMax != None): 
            reg = reg | RMAX
            reg = reg | RMIN

        if (self.onGP1Rise != None):
            reg = reg | INT_2

        if (self.onGP1Fall != None):
            reg = reg | INT_2

        if (self.onGP2Rise != None):
            reg = reg | INT_2

        if (self.onGP2Fall != None):
            reg = reg | INT_2

        if (self.onGP3Rise != None):
            reg = reg | INT_2

        if (self.onGP3Fall != None):
            reg = reg | INT_2

        if (self.onFadeProcess != None):
            reg = reg | INT_2

        self.writeNavKey16(REG_INTCONFB2, reg)

# Write the counter value #
    def writeCounter(self, value) :
        self.writeNavKey32(REG_CVALB4, value)

# Write the counter value #
    def writeCounterFloat(self, value) :
        self.writeNavKeyFloat(REG_CVALB4, value)

# Write the maximum threshold value #
    def writeMax(self, max) :
        self.writeNavKey32(REG_CMAXB4, max)

# Write the maximum threshold value #
    def writeMaxFloat(self, max) :
        self.writeNavKeyFloat(REG_CMAXB4, max)

# Write the minimum threshold value #
    def writeMin(self, min) :
        self.writeNavKey32(REG_CMINB4, min)

# Write the minimum threshold value #
    def writeMinFloat(self, min) :
        self.writeNavKeyFloat(REG_CMINB4, min)

# Write the Step increment value #
    def writeStep(self, step):
        self.writeNavKey32(REG_ISTEPB4, step)

# Write the Step increment value #
    def writeStepFloat(self, step):
        self.writeNavKeyFloat(REG_ISTEPB4, step)

# Write GP1 register, used when GP1 is set to output or PWM #
    def writeGP1(self, gp1):
        self.writeNavKey8(REG_GP1REG, gp1)

# Write GP2 register, used when GP2 is set to output or PWM #
    def writeGP2(self, gp2):
        self.writeNavKey8(REG_GP2REG, gp2)

# Write GP3 register, used when GP3 is set to output or PWM #
    def writeGP3(self, gp3):
        self.writeNavKey8(REG_GP3REG, gp3)

# Write Anti-bouncing period register #
    def writeAntibouncingPeriod(self, bounc):
        self.writeNavKey8(REG_ANTBOUNC, bounc)

# Write Anti-bouncing period register #
    def writeDoublePushPeriod(self, dperiod):
        self.writeNavKey8(REG_DPPERIOD, dperiod)

# Write Fade timing in ms #
    def writeFadeGP(self, fade):
        self.writeNavKey8(REG_FADEGP, fade)

# Write the Gamma value on GP1 #
    def writeGammaGP1(self, gamma):
        self.writeNavKey8(REG_GAMMAGP1, gamma)

# Write the Gamma value on GP2 #
    def writeGammaGP2(self, gamma):
        self.writeNavKey8(REG_GAMMAGP2, gamma)

# Write the Gamma value on GP3 #
    def writeGammaGP3(self, gamma):
        self.writeNavKey8(REG_GAMMAGP3, gamma)

# Write the EEPROM memory#
    def writeEEPROM(self, add, data):

        if add <= 0x7f:
            if (self.gconf & EEPROM_BANK1) != 0:
                self.gconf = self.gconf & 0xBF
                self.writeNavKey8(REG_GCONF, self.gconf)

            self.writeNavKey8((REG_EEPROMS + add), data)
        else:
            if (self.gconf & EEPROM_BANK1) == 0:
                self.gconf = self.gconf | 0x40
                self.writeNavKey8(REG_GCONF, self.gconf)

            self.writeNavKey8(add, data)

        sleep(0.001)

# Send to the encoder 1 byte #
    def writeNavKey8(self, add, value):
        self.i2cbus.write_byte_data(self.i2cadd, add, value)    
        return -1
    
# Send to the encoder 2 byte #
    def writeNavKey16(self, add, value):
        data = [0, 0]
        s = struct.pack('>h', value)
        data = struct.unpack('BB', s)
        self.i2cbus.write_i2c_block_data(self.i2cadd, add, data)
        return -1
        
# Send to the encoder 4 byte #
    def writeNavKey32(self, add, value):
        data = [0, 0, 0, 0]
        s = struct.pack('>i', value)
        data = struct.unpack('BBBB', s)
        self.i2cbus.write_i2c_block_data(self.i2cadd, add, data)
        return -1
        
# Send to the encoder a float number #
    def writeNavKeyFloat(self, add, value):
        data = [0, 0, 0, 0]
        s = struct.pack('>f', value)
        data = struct.unpack('BBBB', s)
        self.i2cbus.write_i2c_block_data(self.i2cadd, add, data)
        return -1
        
# read the encoder 1 byte #     
    def readNavKey8(self, add):
        data = [0]
        data[0] = self.i2cbus.read_byte_data(self.i2cadd, add)    
        value = struct.unpack(">b", bytearray(data))
        return value[0]
        
# read the encoder 2 byte #             
    def readNavKey16(self, add):
        data = [0, 0]
        data = self.i2cbus.read_i2c_block_data(self.i2cadd, add, 2)
        value = struct.unpack(">h", bytearray(data))
        return value[0] 
    
# read the encoder 4 byte #             
    def readNavKey32(self, add):
        data = [0, 0, 0, 0]
        data = self.i2cbus.read_i2c_block_data(self.i2cadd, add, 4)
        value = struct.unpack(">i", bytearray(data))
        return value[0]
        
# read the encoder float#             
    def readNavKeyFloat(self, add):
        data = [0, 0, 0, 0]
        data = self.i2cbus.read_i2c_block_data(self.i2cadd, add, 4)
        value = struct.unpack(">f", bytearray(data)) 
        return value[0]
