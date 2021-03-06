#include "i2c_register.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/adc.h"
#include "main.h"
#include "GPports.h"
#include "DataVariable.h"
#include "PWM.h"


#define GP_PORTS_TIME 10
uint8_t gp_timer;
uint8_t temp_gp1;
uint8_t temp_gp2;
uint8_t temp_gp3;

uint8_t gp1_fsm = GP_CHECKMODE;
uint8_t gp2_fsm = GP_CHECKMODE;
uint8_t gp3_fsm = GP_CHECKMODE;

uint8_t gp_fade_cnt = 0;

/*
 * @brief FSM of the fade process on the port GP1
 */

void FADE_GP1(void) {

    if ((GP1CONF & GPMODE) != GP_PWM)
        return;

    if (FADEGP == 0) {
        if (temp_gp1 != GP1REG) {
            temp_gp1 = GP1REG;
            PWM_GP1(temp_gp1);
        }
        return;
    }

    if (gp_fade_cnt >= FADEGP) {
        if (temp_gp1 != GP1REG) {

            if (temp_gp1 < GP1REG) {
                temp_gp1++;
            }
            if (temp_gp1 > GP1REG) {
                temp_gp1--;
            }

            PWM_GP1(temp_gp1);
            if (temp_gp1 == GP1REG) {
                FadeProcessClear(F_FGP1);
            } else {
                FadeProcessSet(F_FGP1);
            }
        }
    }

}

/*
 * @brief FSM of the fade process on the port GP2
 */
void FADE_GP2(void) {

    if ((GP2CONF & GPMODE) != GP_PWM)
        return;

    if (FADEGP == 0) {
        if (temp_gp2 != GP2REG) {
            temp_gp2 = GP2REG;
            PWM_GP2(temp_gp2);
        }
        return;
    }

    if (gp_fade_cnt >= FADEGP) {
        if (temp_gp2 != GP2REG) {

            if (temp_gp2 < GP2REG) {
                temp_gp2++;
            }
            if (temp_gp2 > GP2REG) {
                temp_gp2--;
            }

            PWM_GP2(temp_gp2);
            if (temp_gp2 == GP2REG) {
                FadeProcessClear(F_FGP2);
            } else {
                FadeProcessSet(F_FGP2);
            }
        }
    }

}

/*
 * @brief FSM of the fade process on the port GP3
 */

void FADE_GP3(void) {

    if ((GP3CONF & GPMODE) != GP_PWM)
        return;

    if (FADEGP == 0) {
        if (temp_gp3 != GP3REG) {
            temp_gp3 = GP3REG;
            PWM_GP3(temp_gp3);
        }
        return;
    }

    if (gp_fade_cnt >= FADEGP) {
        if (temp_gp3 != GP3REG) {

            if (temp_gp3 < GP3REG) {
                temp_gp3++;
            }
            if (temp_gp3 > GP3REG) {
                temp_gp3--;
            }

            PWM_GP3(temp_gp3);
            if (temp_gp3 == GP3REG) {
                FadeProcessClear(F_FGP3);
            } else {
                FadeProcessSet(F_FGP3);
            }
        }
    }

}

/**
 * @brief Function for configure the GP1 port
 */
void Config_GP1(void) {


    UNLOCK_PPS;
    RC2PPSbits.RC2PPS = 0x00;
    LOCK_PPS;
    CCP1CON = 0;
    
    switch (GP1CONF & GPMODE) {
        case GP_PWM:
            GP1_SetDigitalMode();
            GP1_SetHigh();
            GP1_SetDigitalOutput();
            UNLOCK_PPS;
            RC2PPSbits.RC2PPS = 0x0C; //RC2->CCP1:PWM1;  
            LOCK_PPS;
            PWM1_Initialize();
            PWM_GP1(0);
            break;

        case GP_OUT:
            GP1_SetDigitalMode();
            GP1_SetDigitalOutput();
            GP1_SetPushPull();
            break;

        case GP_ADC:
            GP1_SetDigitalInput();
            GP1_SetAnalogMode();
            break;
        case GP_IN:
            GP1_SetDigitalMode();
            GP1_SetDigitalInput();
            break;
    }

    switch (GP1CONF & GPPULLUP) {
        case GP_PULLDI:
            GP1_ResetPullup();
            break;
        case GP_PULLEN:
            GP1_SetPullup();

            break;
    }

}

/**
 * @brief Function for configure the GP2 port
 */
void Config_GP2(void) {


    UNLOCK_PPS;
    RC1PPSbits.RC1PPS = 0x00;
    LOCK_PPS;
    CCP2CON = 0;
    switch (GP2CONF & GPMODE) {
        case GP_PWM:
            GP2_SetDigitalMode();
            GP2_SetHigh();
            GP2_SetDigitalOutput();
            UNLOCK_PPS;
            RC1PPSbits.RC1PPS = 0x0D; //RC1->CCP2:PWM2;
            LOCK_PPS;
            PWM2_Initialize();
            PWM_GP2(0);
            break;

        case GP_OUT:
            GP2_SetDigitalMode();
            GP2_SetDigitalOutput();
            GP2_SetPushPull();
            break;

        case GP_ADC:
            GP2_SetDigitalInput();
            GP2_SetAnalogMode();
            break;

        case GP_IN:
            GP2_SetDigitalMode();
            GP2_SetDigitalInput();
            break;
    }

    switch (GP2CONF & GPPULLUP) {
        case GP_PULLDI:
            GP2_ResetPullup();
            break;
        case GP_PULLEN:
            GP2_SetPullup();

            break;
    }

}

/**
 * @brief Function for configure the GP3 port
 */
void Config_GP3(void) {

    UNLOCK_PPS;
    RC0PPSbits.RC0PPS = 0x00;
    LOCK_PPS;
    CCP3CON = 0;
    switch (GP3CONF & GPMODE) {
        case GP_PWM:
            GP3_SetDigitalMode();
            GP3_SetHigh();
            GP3_SetDigitalOutput();
            UNLOCK_PPS;
            RC0PPSbits.RC0PPS = 0x0E; //RC0->CCP3:PWM3;  
            LOCK_PPS;
            PWM3_Initialize();
            PWM_GP3(0);
            break;

        case GP_OUT:
            GP3_SetDigitalMode();
            GP3_SetDigitalOutput();
            GP3_SetPushPull();
            break;

        case GP_ADC:
            GP3_SetDigitalInput();
            GP3_SetAnalogMode();
            break;

        case GP_IN:
            GP3_SetDigitalMode();
            GP3_SetDigitalInput();
            break;
    }

    switch (GP3CONF & GPPULLUP) {
        case GP_PULLDI:
            GP3_ResetPullup();
            break;
        case GP_PULLEN:
            GP3_SetPullup();
            break;
    }

}

/**
 * @brief Set the logic output for the GP1 pin
 */
void UpdateOut_GP1(void) {
    if ((GP1CONF & GPMODE) == GP_OUT) {
        if (GP1REG == 0) {
            GP1_SetLow();
        } else {
            GP1_SetHigh();
            GP1REG = 1;
        }
        return;
    }
    if ((GP1CONF & GPMODE) == GP_PWM) {
        if (FADEGP == 0) {
            PWM_GP1(GP1REG);
        }
    }
}

/**
 * @brief Set the logic output for the GP2 pin
 */
void UpdateOut_GP2(void) {
    if ((GP2CONF & GPMODE) == GP_OUT) {
        if (GP2REG == 0) {
            GP2_SetLow();
        } else {
            GP2_SetHigh();
            GP2REG = 1;
        }
        return;
    }

    if ((GP2CONF & GPMODE) == GP_PWM) {
        if (FADEGP == 0) {
            PWM_GP2(GP2REG);
        }
    }
}

/**
 * @brief Set the logic output for the GP3 pin
 */
void UpdateOut_GP3(void) {
    if ((GP3CONF & GPMODE) == GP_OUT) {
        if (GP3REG == 0) {
            GP3_SetLow();
        } else {
            GP3_SetHigh();
            GP3REG = 1;
        }
        return;
    }
    if ((GP3CONF & GPMODE) == GP_PWM) {
        if (FADEGP == 0) {
            PWM_GP3(GP3REG);
        }
    }
}

/**
 * @brief FSM for manage the ADC and the Input pin of GP1. it's called every 10ms
 */
void GP1_FSM(void) {
    switch (gp1_fsm) {
        case GP_CHECKMODE:
            if ((GP1CONF & GPMODE) == GP_ADC) {
                gp1_fsm = GP_ADC_MODE;
                ADC_Initialize();
                return;
            }
            if ((GP1CONF & GPMODE) == GP_IN) {
                gp1_fsm = GP_WAITRISE;
                return;
            }
            break;

        case GP_ADC_MODE:
            GP1REG = (ADC_GetConversion(A_GP1) >> 2);
            break;

        case GP_WAITRISE:
            if (GP1_GetValue() == HIGH) {
                GP1REG = 1;
                Int2StatusUpdate(E_GP1POS);
                if ((GP1CONF & GPIOMASKPOSINT) != 0) {
                    SetInterrupt();
                }
                gp1_fsm = GP_WAITFALL;
            }
            break;

        case GP_WAITFALL:
            if (GP1_GetValue() == LOW) {
                GP1REG = 0;
                Int2StatusUpdate(E_GP1NEG);
                if ((GP1CONF & GPIOMASKNEGINT) != 0) {
                    SetInterrupt();
                }
                gp1_fsm = GP_WAITRISE;
            }
            break;
    }
}

/**
 * @brief FSM for manage the ADC and the Input pin of GP2. it's called every 10ms
 */
void GP2_FSM(void) {

    switch (gp2_fsm) {
        case GP_CHECKMODE:
            if ((GP2CONF & GPMODE) == GP_ADC) {
                gp2_fsm = GP_ADC_MODE;
                ADC_Initialize();
                return;
            }

            if ((GP2CONF & GPMODE) == GP_IN) {
                gp2_fsm = GP_WAITRISE;
                return;
            }
            break;

        case GP_ADC_MODE:
            GP2REG = (ADC_GetConversion(A_GP2) >> 2);
            break;

        case GP_WAITRISE:
            if (GP2_GetValue() == HIGH) {
                GP2REG = 1;
                Int2StatusUpdate(E_GP2POS);
                if ((GP2CONF & GPIOMASKPOSINT) != 0) {
                    SetInterrupt();
                }
                gp2_fsm = GP_WAITFALL;
            }
            break;

        case GP_WAITFALL:
            if (GP2_GetValue() == LOW) {

                GP2REG = 0;
                Int2StatusUpdate(E_GP2NEG);
                if ((GP2CONF & GPIOMASKNEGINT) != 0) {
                    SetInterrupt();
                }
                gp2_fsm = GP_WAITRISE;
            }
            break;
    }

}

/**
 * @brief FSM fror manage the ADC and the Input pin of GP3. it's called every 10ms
 */
void GP3_FSM(void) {

    switch (gp3_fsm) {
        case GP_CHECKMODE:
            if ((GP3CONF & GPMODE) == GP_ADC) {
                gp3_fsm = GP_ADC_MODE;
                ADC_Initialize();
                return;
            }

            if ((GP3CONF & GPMODE) == GP_IN) {
                gp3_fsm = GP_WAITRISE;
                return;
            }
            break;

        case GP_ADC_MODE:
            GP3REG = (ADC_GetConversion(A_GP3) >> 2);
            break;

        case GP_WAITRISE:
            if (GP3_GetValue() == HIGH) {
                GP3REG = 1;
                Int2StatusUpdate(E_GP3POS);
                if ((GP3CONF & GPIOMASKPOSINT) != 0) {
                    SetInterrupt();
                }
                gp3_fsm = GP_WAITFALL;
            }
            break;

        case GP_WAITFALL:
            if (GP3_GetValue() == LOW) {

                GP3REG = 0;
                Int2StatusUpdate(E_GP3NEG);
                if ((GP3CONF & GPIOMASKNEGINT) != 0) {
                    SetInterrupt();
                }
                gp3_fsm = GP_WAITRISE;
            }
            break;
    }
}

void GP_Ports_FSM(void) {

    if (FADEGP > 0) {
        FADE_GP1();
        FADE_GP2();
        FADE_GP3();

        if (gp_fade_cnt++ >= FADEGP) {
            gp_fade_cnt = 0;
        }
    }



    if (gp_timer++ > GP_PORTS_TIME) {
        gp_timer = 0;
        GP1_FSM();
        GP2_FSM();
        GP3_FSM();
    }
}