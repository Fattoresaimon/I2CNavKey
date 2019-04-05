

#include "i2c_register.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/i2c1.h"
#include "main.h"
#include "GPports.h"
#include "DataVariable.h"
#include "NavKey.h"


volatile uint8_t EncoderReg = 0;
volatile bool intclear = false;
volatile bool int2clear = false;

/**
 * @brief Function that set the I2C address according to the A0-A3 jumper setting
 */

void I2C1_AddressSet(void) {
#ifdef CUSTOM_ADD
    i2c_address = CUSTOM_ADD;

#else

    i2c_address = I2C1_SLAVE_ADDRESS;

    ADD0_SetDigitalInput();
    ADD1_SetDigitalInput();
    ADD2_SetDigitalInput();

    ADD0_SetPullup();
    ADD1_SetPullup();
    ADD2_SetPullup();
    ADD3_SetPullup();

    if (!ADD0_GetValue()) {
        i2c_address |= 0x01;
        ADD0_ResetPullup();
    }

    if (!ADD1_GetValue()) {
        i2c_address |= 0x02;
        ADD1_ResetPullup();
    }

    if (!ADD2_GetValue()) {
        i2c_address |= 0x04;
        ADD2_ResetPullup();
    }

    if (!ADD3_GetValue()) {
        i2c_address |= 0x08;
        ADD3_ResetPullup();
    }

#endif
    i2c_address = (uint8_t) (i2c_address << 1);


}

/**
 * @brief Callback for managing the I2C request from the master
 * @param i2c_bus_state 
 */
void I2C1_StatusCallback(I2C1_SLAVE_DRIVER_STATUS i2c_bus_state) {
    static uint8_t slaveWriteType = SLAVE_NORMAL_DATA;

    switch (i2c_bus_state) {
        case I2C1_SLAVE_WRITE_REQUEST:
            // the master will be sending the eeprom address next
            slaveWriteType = SLAVE_DATA_ADDRESS;
            break;


        case I2C1_SLAVE_WRITE_COMPLETED:

            switch (slaveWriteType) {
                case SLAVE_DATA_ADDRESS:
                    EncoderReg = I2C1_slaveWriteData;
                    break;

                case SLAVE_NORMAL_DATA:
                default:
                    RegisterWrite(EncoderReg, I2C1_slaveWriteData);
                    EncoderReg++;
                    break;

            } // end switch(slaveWriteType)

            slaveWriteType = SLAVE_NORMAL_DATA;
            break;

        case I2C1_SLAVE_READ_REQUEST:
            SSP1BUF = RegisterRead(EncoderReg);
            EncoderReg++;
            break;

        case I2C1_SLAVE_READ_COMPLETED:
            if (intclear == true) {
                StatusClear();
                ClearInterrupt();
                intclear = false;
            }

            if (int2clear == true) {
                Int2StatusClear();
                int2clear = false;
            }

            break;

        default:
            break;

    } // end switch(i2c_bus_state)

}

/**
 * @brief Function that write inside on the Encoder register 
 * @param add Address of the internal register
 * @param data Data to be written inside of the register
 */
void RegisterWrite(uint8_t add, uint8_t data) {

    switch (add) {
        case REG_GCONF:
            GCONF = data;
            GeneralDataSplit();
            GeneralDataSet();
            break;

        case REG_GP1CONF:
            GP1CONF = data;
            Config_GP1();
            break;

        case REG_GP2CONF:
            GP2CONF = data;
            Config_GP2();
            break;

        case REG_GP3CONF:
            GP3CONF = data;
            Config_GP3();
            break;

        case REG_INTCONFB2:
            INTCONF.bval[BYTE2] = data;
            break;

        case REG_INTCONFB1:
            INTCONF.bval[BYTE1] = data;
            break;

            /*** Counter value reg ***/
        case REG_CVALB4:
            CVAL.bval[BYTE4] = data;
            break;
        case REG_CVALB3:
            CVAL.bval[BYTE3] = data;
            break;
        case REG_CVALB2:
            CVAL.bval[BYTE2] = data;
            break;
        case REG_CVALB1:
            CVAL.bval[BYTE1] = data;
            break;

            /*** Max Value ***/
        case REG_CMAXB4:
            CMAX.bval[BYTE4] = data;
            break;
        case REG_CMAXB3:
            CMAX.bval[BYTE3] = data;
            break;
        case REG_CMAXB2:
            CMAX.bval[BYTE2] = data;
            break;
        case REG_CMAXB1:
            CMAX.bval[BYTE1] = data;
            break;

            /*** Min Value ***/
        case REG_CMINB4:
            CMIN.bval[BYTE4] = data;
            break;
        case REG_CMINB3:
            CMIN.bval[BYTE3] = data;
            break;
        case REG_CMINB2:
            CMIN.bval[BYTE2] = data;
            break;
        case REG_CMINB1:
            CMIN.bval[BYTE1] = data;
            break;

            /*** Increment step  Value ***/
        case REG_ISTEPB4:
            ISTEP.bval[BYTE4] = data;
            break;
        case REG_ISTEPB3:
            ISTEP.bval[BYTE3] = data;
            break;
        case REG_ISTEPB2:
            ISTEP.bval[BYTE2] = data;
            break;
        case REG_ISTEPB1:
            ISTEP.bval[BYTE1] = data;
            break;

            /* GPs */
        case REG_GP1REG:
            GP1REG = data;
            if (GP1REG > 100)
                GP1REG = 100;
            UpdateOut_GP1();
            break;

        case REG_GP2REG:
            GP2REG = data;
            if (GP2REG > 100)
                GP2REG = 100;
            UpdateOut_GP2();
            break;

        case REG_GP3REG:
            GP3REG = data;
            if (GP3REG > 100)
                GP3REG = 100;
            UpdateOut_GP3();
            break;

            // timing register

        case REG_DPPERIOD:
            DPPERIOD = data;
            DoublePush = ((uint16_t) DPPERIOD * 10);
            if (DoublePush > 5) {
                DoublePush = DoublePush - 5;
            }
            break;

        case REG_FADEGP:
            FADEGP = data;
            break;

        case REG_GAMMAGP1:
            GAMMAGP1 = data;
            if (GAMMAGP1 > 7) {
                GAMMAGP1 = 7;
            }
            break;
        case REG_GAMMAGP2:
            GAMMAGP2 = data;
            if (GAMMAGP2 > 7) {
                GAMMAGP2 = 7;
            }
            break;
        case REG_GAMMAGP3:
            GAMMAGP3 = data;
            if (GAMMAGP3 > 7) {
                GAMMAGP3 = 7;
            }
            break;

    }

    if (add >= REG_EEPROMS) {

        if (C_MBANK == 0) {
            eeprom_write((uint8_t) (add - REG_EEPROMS), (uint8_t) data);

        } else {
            eeprom_write((uint8_t) add, (uint8_t) data);
        }
    }
}

/**
 * @brief Function called when there is a Read request from the i2c master
 * @param add Address of the internal register
 * @return Value of the internal register, 0 in case of invalid register
 */

uint8_t RegisterRead(uint8_t add) {
    uint8_t return_value = 0;

    switch (add) {
        case REG_GCONF:
            return_value = GCONF;
            break;

        case REG_GP1CONF:
            return_value = GP1CONF;
            break;

        case REG_GP2CONF:
            return_value = GP2CONF;
            break;

        case REG_GP3CONF:
            return_value = GP3CONF;
            break;

        case REG_INTCONFB2:
            return_value = INTCONF.bval[BYTE2];
            break;

        case REG_INTCONFB1:
            return_value = INTCONF.bval[BYTE1];
            break;

        case REG_STATUSB2:
            return_value = NSTATUS.bval[BYTE2];
            intclear = true;
            break;

        case REG_STATUSB1:
            return_value = NSTATUS.bval[BYTE1];
            intclear = true;
            break;

        case REG_SSTATUS:
            return_value = SSTATUS;
            int2clear = true;
            break;

        case REG_FSTATUS:
            return_value = FSTATUS;
            break;

            /*** Data Value ***/
        case REG_CVALB4:
            return_value = CVAL.bval[BYTE4];
            break;
        case REG_CVALB3:
            return_value = CVAL.bval[BYTE3];
            break;
        case REG_CVALB2:
            return_value = CVAL.bval[BYTE2];
            break;
        case REG_CVALB1:
            return_value = CVAL.bval[BYTE1];
            break;

            /*** Max Value ***/
        case REG_CMAXB4:
            return_value = CMAX.bval[BYTE4];
            break;
        case REG_CMAXB3:
            return_value = CMAX.bval[BYTE3];
            break;
        case REG_CMAXB2:
            return_value = CMAX.bval[BYTE2];
            break;
        case REG_CMAXB1:
            return_value = CMAX.bval[BYTE1];
            break;

            /*** Min Value ***/
        case REG_CMINB4:
            return_value = CMIN.bval[BYTE4];
            break;
        case REG_CMINB3:
            return_value = CMIN.bval[BYTE3];
            break;
        case REG_CMINB2:
            return_value = CMIN.bval[BYTE2];
            break;
        case REG_CMINB1:
            return_value = CMIN.bval[BYTE1];
            break;

            /*** Increment step  Value ***/
        case REG_ISTEPB4:
            return_value = ISTEP.bval[BYTE4];
            break;
        case REG_ISTEPB3:
            return_value = ISTEP.bval[BYTE3];
            break;
        case REG_ISTEPB2:
            return_value = ISTEP.bval[BYTE2];
            break;
        case REG_ISTEPB1:
            return_value = ISTEP.bval[BYTE1];
            break;

        case REG_GP1REG:
            return_value = GP1REG;
            break;

        case REG_GP2REG:
            return_value = GP2REG;
            break;

        case REG_GP3REG:
            return_value = GP3REG;
            break;

        case REG_DPPERIOD:
            return_value = DPPERIOD;
            break;

        case REG_FADEGP:
            return_value = FADEGP;
            break;

        case REG_GAMMAGP1:
            return_value = GAMMAGP1;
            break;

        case REG_GAMMAGP2:
            return_value = GAMMAGP2;
            break;

        case REG_GAMMAGP3:
            return_value = GAMMAGP3;
            break;

        case REG_IDCODE:
            return_value = IDVALUE;
            break;

        case REG_FWVER:
            return_value = BOARD_VERSION;
            break;

        default:
            return_value = 0;
            break;

    }
    if (add >= REG_EEPROMS) {
        if (C_MBANK == 0) {
            return_value = eeprom_read((uint8_t) (add - REG_EEPROMS));
        } else {
            return_value = eeprom_read(add);
        }
    }
    return return_value;
}

/**
 * @brief Function that execute the command according on the configuration register
 */
void GeneralDataSet(void) {

    if (C_DIRE == false) {
        UNLOCK_PPS;
        CLCIN1PPSbits.CLCIN1PPS = 0x14; //RC5->CLC2:CLCIN1;    
        CLCIN0PPSbits.CLCIN0PPS = 0x15; //RC4->CLC2:CLCIN0; 
        LOCK_PPS;
    } else {
        UNLOCK_PPS;
        CLCIN1PPSbits.CLCIN1PPS = 0x15; //RC5->CLC2:CLCIN1;    
        CLCIN0PPSbits.CLCIN0PPS = 0x14; //RC4->CLC2:CLCIN0; 
        LOCK_PPS;
    }

    if (C_IPUD == true) {
        INT_ResetPullup();
        INT_SetHigh();
    } else {
        INT_SetPullup();
        INT_SetHigh();

    }


    if (C_CKSRC == true) {
        I2C1_Initialize_ClockStreach();
    } else {
        I2C1_Initialize();
    }

    if (C_RESET == true) {
        RESET();
    }
}