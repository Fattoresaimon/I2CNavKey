/* 
 * File:   DataVariable.h
 * Author: Saimon
 *
 * Created on 11 settembre 2017, 21.20
 */

#ifndef DATAVARIABLE_H
#define	DATAVARIABLE_H

#include <stdint.h>
#include <stdbool.h>

#define IDVALUE 0x5B
#define BOARD_VERSION   0x12


extern volatile uint8_t i2c_address;

extern volatile uint8_t I2C1_slaveWriteData;

extern volatile bool DataType;
#define INT_DATA_TYPE false
#define FLOAT_DATA_TYPE true

#define RGB_ENCODER true
#define STD_ENCODER false

union Data_l {
    double fval;
    int32_t val;
    uint8_t bval[4];

};

union Data_s {
    uint16_t val;
    uint8_t bval[2];

};

/** Internal register **/
/** Configuration **/
extern volatile uint8_t GCONF; //address 0x00
/** GPIO_CONF **/
extern volatile uint8_t GP1CONF; //address 0x01
extern volatile uint8_t GP2CONF; //address 0x02
extern volatile uint8_t GP3CONF; //address 0x03

/** INTCONF_CONF **/
extern volatile union Data_s INTCONF; //address 0x04 - 0x05

/** Status **/
extern volatile union Data_s NSTATUS; //address 0x06 - 0x07
extern volatile uint8_t SSTATUS; //address 0x08
extern volatile uint8_t FSTATUS; //address 0x09

/** Data Value **/
extern volatile union Data_l CVAL; //address 0x0A - 0x0D
extern volatile union Data_l CMAX; //address 0x0E - 0x11
extern volatile union Data_l CMIN; //address 0x12 - 0x15
extern volatile union Data_l ISTEP; //address 0x16 - 0x19


/** GPx register **/
extern volatile uint8_t GP1REG; //address 0x1A
extern volatile uint8_t GP2REG; //address 0x1B
extern volatile uint8_t GP3REG; //address 0x1C

/** Timing register **/
extern volatile uint8_t DPPERIOD; //address 0x1D
extern volatile uint8_t FADEGP; //address 0x1E

/* Gamma register */
extern volatile uint8_t GAMMAGP1; //address 0x1F
extern volatile uint8_t GAMMAGP2; //address 0x20
extern volatile uint8_t GAMMAGP3; //address 0x21

/** General configuration bit **/
extern volatile bool C_RESET, C_MBANK, C_CKSRC, C_IPUD, C_DIRE, C_WRAPE, C_DTYPE;

extern volatile uint16_t DoublePush;




/* GP register setting */
#define GPMODE 0x03
#define GPPULLUP 0x04
#define GPINNT 0x18
/* GP MODE configuration */
#define GP_PWM  0x00
#define GP_OUT  0x01
#define GP_ADC  0x02
#define GP_IN   0x03
/* GP pull-up configuration */
#define GP_PULLDI   0x00
#define GP_PULLEN   0x04
/* GP Interrupt configuration */
#define GP_NOINT    0x00
#define GP_POSED    0x08
#define GP_NEGED    0x10
#define GP_BOTHED   0x18

typedef enum {
    S_UPR = 0x0001,
    S_UPP = 0x0002,
    S_DNR = 0x0004,
    S_DNP = 0x0008,
    S_RTR = 0x0010,
    S_RTP = 0x0020,
    S_LTR = 0x0040,
    S_LTP = 0x0080,
    S_CTRR = 0x0100,
    S_CTRP = 0x0200,
    S_CTRDP = 0x0400,
    S_RINC = 0x0800,
    S_RDEC = 0x1000,
    S_RMAX = 0x2000,
    S_RMIN = 0x4000,
    S_INT2 = 0x8000,
} ENCODER_STATUS_CASE;

typedef enum {
    E_GP1POS = 0x01,
    E_GP1NEG = 0x02,
    E_GP2POS = 0x04,
    E_GP2NEG = 0x08,
    E_GP3POS = 0x10,
    E_GP3NEG = 0x20,
    E_GPFADE = 0x40,
} INT2_STATUS_CASE;

typedef enum {
    F_FGP1 = 0x01,
    F_FGP2 = 0x02,
    F_FGP3 = 0x04,
} FADE_STATUS_CASE;



void DataInitSet(void);
void GeneralDataSplit(void);
void NavKeyStatusUpdate(ENCODER_STATUS_CASE stat);
void Int2StatusUpdate(INT2_STATUS_CASE stat);
void FadeProcessSet(FADE_STATUS_CASE stat);
void StatusClear(void);
void Int2StatusClear(void);
void FadeProcessClear(FADE_STATUS_CASE stat);

#endif	/* DATAVARIABLE_H */