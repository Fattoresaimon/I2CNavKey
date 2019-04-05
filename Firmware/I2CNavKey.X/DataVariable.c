
#include "DataVariable.h"
#include "mcc_generated_files/mcc.h"
#include "main.h"
#include "GPports.h"
#include <stdbool.h>

volatile uint8_t i2c_address;


/** Internal register **/

/** Configuration **/
volatile uint8_t GCONF = 0; //address 0x00
/** GPIO_CONF **/
volatile uint8_t GP1CONF = 0; //address 0x01
volatile uint8_t GP2CONF = 0; //address 0x02
volatile uint8_t GP3CONF = 0; //address 0x03

/** INTCONF_CONF **/
volatile union Data_s INTCONF = 0; //address 0x04 - 0x05

/** Status **/
volatile union Data_s NSTATUS; //address 0x06 - 0x07
volatile uint8_t SSTATUS; //address 0x08
volatile uint8_t FSTATUS; //address 0x09

/** Data Value **/
volatile union Data_l CVAL; //address 0x0A - 0x0D
volatile union Data_l CMAX; //address 0x0E - 0x11
volatile union Data_l CMIN; //address 0x12 - 0x15
volatile union Data_l ISTEP; //address 0x16 - 0x19


/** GPx register **/
volatile uint8_t GP1REG = 0; //address 0x1A
volatile uint8_t GP2REG = 0; //address 0x1B
volatile uint8_t GP3REG = 0; //address 0x1C

/** Timing register **/
volatile uint8_t DPPERIOD; //address 0x1D
volatile uint8_t FADEGP; //address 0x1E

/* Gamma register */
volatile uint8_t GAMMAGP1; //address 0x1F
volatile uint8_t GAMMAGP2; //address 0x20
volatile uint8_t GAMMAGP3; //address 0x21

/** General configuration bit **/
volatile bool C_RESET, C_MBANK, C_CKSRC, C_IPUD, C_DIRE, C_WRAPE, C_DTYPE;

volatile uint16_t DoublePush;

void DataInitSet(void) {
    GCONF = 0;
    GP1CONF = 0;
    GP3CONF = 0;
    INTCONF.val = 0;
    NSTATUS.val = 0;
    CVAL.val = 0;
    CMAX.val = 0;
    CMIN.val = 0;
    ISTEP.val = 1;
    GP1REG = 0;
    GP2REG = 0;
    GP3REG = 0;
    C_RESET = false;
    C_MBANK = false;
    C_CKSRC = false;
    C_IPUD = false;
    C_DIRE = false;
    C_WRAPE = false;
    C_DTYPE = false;

    DPPERIOD = 0;
    FADEGP = 0;
    GAMMAGP1=0;
    GAMMAGP2=0;
    GAMMAGP3=0;
    DoublePush = 0;
}

/**
 * @brief Function that split the configuration byte in the single bit
 */
void GeneralDataSplit(void) {

    C_DTYPE = GCONF & 0x01U;
    C_WRAPE = (bool) (GCONF >> 1) & 0x01U;
    C_DIRE = (bool) (GCONF >> 2) & 0x01U;
    C_IPUD = (bool) (GCONF >> 3) & 0x01U;
    C_CKSRC = (bool) (GCONF >> 4) & 0x01U;
    C_MBANK = (bool) (GCONF >> 5) & 0x01U;
    C_RESET = (bool) (GCONF >> 7) & 0x01U;

}

/**
 * @brief Function for update the status variable 
 * @param stat Status of the encoder from ::ENCODER_STATUS_CASE
 */
void NavKeyStatusUpdate(ENCODER_STATUS_CASE stat) {
    NSTATUS.val |= (uint16_t) stat;
}

/**
 * @brief Function for update the status variable of the GP pins
 * @param stat Status of the encoder from GP_STATUS_CASE
 */
void Int2StatusUpdate(INT2_STATUS_CASE stat) {
    SSTATUS |= (uint8_t) stat;
    NavKeyStatusUpdate(S_INT2);
}

/**
 * @brief Function for clear the status of the encoder
 */
void StatusClear(void) {
    NSTATUS.val = 0;
}

/**
 * @brief Function for clear the status of the GPz pins
 */
void Int2StatusClear(void) {
    SSTATUS = 0;
}

/**
 * @brief Function for update the status of the fading process
 * @param stat Status of the fade process from FADE_STATUS_CASE
 */
void FadeProcessSet(FADE_STATUS_CASE stat) {
    FSTATUS |= (uint8_t) stat;
}

/**
 * @brief Function for clear a bit of the fading process
 * @param stat Status of the fade process from FADE_STATUS_CASE
 */
void FadeProcessClear(FADE_STATUS_CASE stat) {
    FSTATUS &= ~(uint8_t) stat;
    Int2StatusUpdate(E_GPFADE);

    SetInterrupt();
}
