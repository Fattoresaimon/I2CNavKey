#include "i2c_register.h"
#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/adc.h"
#include "main.h"
#include "GPports.h"
#include "DataVariable.h"
#include "NavKey.h"


uint8_t pb_fsm = NavKey_WAITPUSH;
int8_t pb_cnt[5] = 0;
uint16_t double_push_cnt = 0;
bool NavKey_PBtemp[5] = {false};
bool NavKey_PBstatus[5] = {false};

uint16_t en_deb = 0;
uint8_t en_prev = 0;
#define ENC_1 0
#define ENC_2 1

/**
 * @brief function that is called on one direction of the encoder
 */
void CLC_1_Interrupt(void) {

    if (en_prev == ENC_2)
        if (en_deb < ENC_DEBOUNCE)
            return;


    en_deb = 0;
    en_prev = ENC_1;

    if (C_DTYPE == INT_DATA_TYPE) {
        CVAL.val = CVAL.val + ISTEP.val;
        NavKeyStatusUpdate(S_RINC);
        if (CVAL.val > CMAX.val) {
            NavKeyStatusUpdate(S_RMAX);
            if (C_WRAPE == true) {
                CVAL.val = CMIN.val;
            } else {
                CVAL.val = CMAX.val;
            }
        }
    } else {
        CVAL.fval = CVAL.fval + ISTEP.fval;
        NavKeyStatusUpdate(S_RINC);
        if (CVAL.fval > CMAX.fval) {
            NavKeyStatusUpdate(S_RMAX);
            if (C_WRAPE == true) {
                CVAL.fval = CMIN.fval;
            } else {
                CVAL.fval = CMAX.fval;
            }
        }
    }


    SetInterrupt();
}

/**
 * @brief function that is called on the other direction of the encoder
 */

void CLC_2_Interrupt(void) {

    if (en_prev == ENC_1)
        if (en_deb < ENC_DEBOUNCE)
            return;

    en_deb = 0;
    en_prev = ENC_2;

    if (C_DTYPE == INT_DATA_TYPE) {

        CVAL.val = CVAL.val - ISTEP.val;
        NavKeyStatusUpdate(S_RDEC);
        if (CVAL.val < CMIN.val) {
            NavKeyStatusUpdate(S_RMIN);
            if (C_WRAPE == true) {
                CVAL.val = CMAX.val;
            } else {
                CVAL.val = CMIN.val;
            }
        }
    } else {
        CVAL.fval = CVAL.fval - ISTEP.fval;
        NavKeyStatusUpdate(S_RDEC);
        if (CVAL.fval < CMIN.fval) {
            NavKeyStatusUpdate(S_RMIN);
            if (C_WRAPE == true) {
                CVAL.fval = CMAX.fval;
            } else {
                CVAL.fval = CMIN.fval;
            }
        }
    }

    SetInterrupt();
}

/**
 * @brief function that make a anti-bouncing of the switch, must be called every 1ms
 * @return true if pressed, false if released
 */
void NavKeySwitch_KeyFilter(void) {
    uint8_t i;

    NavKey_PBtemp[0] = S1_GetValue();
    NavKey_PBtemp[1] = S2_GetValue();
    NavKey_PBtemp[2] = S3_GetValue();
    NavKey_PBtemp[3] = S4_GetValue();
    NavKey_PBtemp[4] = S5_GetValue();

    for (i = 0; i < 5; i++) {
        if (NavKey_PBtemp[i] == PB_PRESSED) {
            if (pb_cnt[i]++ >= PB_DEBOUNCE) {
                pb_cnt[i] = PB_DEBOUNCE;
                NavKey_PBstatus[i] = true;
            }
        } else {
            if (pb_cnt[i]-- <= 0) {
                pb_cnt[i] = 0;
                NavKey_PBstatus[i] = false;
            }
        }
    }
}

/*
 @brief  Central button FSM. It's check when the button is pressed, released and double pushed
 */

void NavKey_CentralButton_FSM(void) {

    if (double_push_cnt > DoublePush) {
        pb_fsm = NavKey_TIMEOUT;
    } else {
        double_push_cnt++;
    }

    switch (pb_fsm) {
        case NavKey_WAITPUSH:
            double_push_cnt = 0;
            if (NavKey_PBstatus[CTR_KEY] == true) {
                pb_fsm = NavKey_WAITRELEASE;
            }
            break;


        case NavKey_WAITRELEASE:
            if (NavKey_PBstatus[CTR_KEY] == false) {
                pb_fsm = NavKey_WAITDOUBLEPUSH;
            }
            break;

        case NavKey_WAITDOUBLEPUSH:
            if (NavKey_PBstatus[CTR_KEY] == true) {
                pb_fsm = NavKey_WAITDOUBLERELEASED;
            }
            break;

        case NavKey_WAITDOUBLERELEASED:
            if (NavKey_PBstatus[CTR_KEY] == false) {
                double_push_cnt = 0;
                pb_fsm = NavKey_WAITPUSH;
                NavKeyStatusUpdate(S_CTRDP);
                SetInterrupt();
            }
            break;

        case NavKey_TIMEOUT:
            double_push_cnt = 0;
            NavKeyStatusUpdate(S_CTRP);
            if (NavKey_PBstatus[CTR_KEY] == true) {
                pb_fsm = NavKey_PUSHRESET;
            } else {
                pb_fsm = NavKey_WAITPUSH;
                NavKeyStatusUpdate(S_CTRR);
            }
            SetInterrupt();
            break;

        case NavKey_PUSHRESET:
            double_push_cnt = 0;
            if (NavKey_PBstatus[CTR_KEY] == false) {

                pb_fsm = NavKey_WAITPUSH;
                NavKeyStatusUpdate(S_CTRR);
                SetInterrupt();
            }
            break;
    }
}

/*
 @brief  It's check when the UP button is pressed or released
 */

void NavKey_UPButton_FSM(void) {
    static uint8_t up_fsm;

    switch (up_fsm) {

        case NavKey_WAITPUSH:
            if (NavKey_PBstatus[UP_KEY] == true) {
                up_fsm = NavKey_WAITRELEASE;
                NavKeyStatusUpdate(S_UPP);
                SetInterrupt();
            }
            break;

        case NavKey_WAITRELEASE:
            if (NavKey_PBstatus[UP_KEY] == false) {
                up_fsm = NavKey_WAITPUSH;
                NavKeyStatusUpdate(S_UPR);
                SetInterrupt();
            }
            break;

        default:
            up_fsm = NavKey_WAITPUSH;
            break;
    }
}

/*
 @brief  It's check when the DOWN button is pressed or released
 */

void NavKey_DWButton_FSM(void) {
    static uint8_t dn_fsm;

    switch (dn_fsm) {

        case NavKey_WAITPUSH:
            if (NavKey_PBstatus[DN_KEY] == true) {
                dn_fsm = NavKey_WAITRELEASE;
                NavKeyStatusUpdate(S_DNP);
                SetInterrupt();
            }
            break;

        case NavKey_WAITRELEASE:
            if (NavKey_PBstatus[DN_KEY] == false) {
                dn_fsm = NavKey_WAITPUSH;
                NavKeyStatusUpdate(S_DNR);
                SetInterrupt();
            }
            break;

        default:
            dn_fsm = NavKey_WAITPUSH;
            break;
    }
}

/*
 @brief  It's check when the RIGHT button is pressed or released
 */

void NavKey_RTButton_FSM(void) {
    static uint8_t rt_fsm;

    switch (rt_fsm) {

        case NavKey_WAITPUSH:
            if (NavKey_PBstatus[RT_KEY] == true) {
                rt_fsm = NavKey_WAITRELEASE;
                NavKeyStatusUpdate(S_RTP);
                SetInterrupt();
            }
            break;

        case NavKey_WAITRELEASE:
            if (NavKey_PBstatus[RT_KEY] == false) {
                rt_fsm = NavKey_WAITPUSH;
                NavKeyStatusUpdate(S_RTR);
                SetInterrupt();
            }
            break;

        default:
            rt_fsm = NavKey_WAITPUSH;
            break;
    }
}

/*
 @brief  It's check when the LEFT button is pressed or released
 */

void NavKey_LTButton_FSM(void) {
    static uint8_t lt_fsm;

    switch (lt_fsm) {

        case NavKey_WAITPUSH:
            if (NavKey_PBstatus[LT_KEY] == true) {
                lt_fsm = NavKey_WAITRELEASE;
                NavKeyStatusUpdate(S_LTP);
                SetInterrupt();
            }
            break;

        case NavKey_WAITRELEASE:
            if (NavKey_PBstatus[LT_KEY] == false) {
                lt_fsm = NavKey_WAITPUSH;
                NavKeyStatusUpdate(S_LTR);
                SetInterrupt();
            }
            break;

        default:
            lt_fsm = NavKey_WAITPUSH;
            break;
    }
}

/*
 @brief FMS for managing the RGB led fade, the push button and the debounce of the encoder
 */
void NavKey_FSM(void) {


    if (en_deb < ENC_DEBOUNCE) {
        en_deb++;
    }

    NavKeySwitch_KeyFilter();
    NavKey_CentralButton_FSM();
    NavKey_UPButton_FSM();
    NavKey_DWButton_FSM();
    NavKey_RTButton_FSM();
    NavKey_LTButton_FSM();
}