#ifndef NAVKEY_H
#define	NAVKEY_H

#include <xc.h> // include processor files - each processor file is guarded.  


#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */

#define ENC_DEBOUNCE 10
#define PB_DEBOUNCE 5
#define PB_PRESSED false // logic of the button is negated
#define PB_RELEASED true    
#define CTR_KEY 0
#define DN_KEY 1
#define RT_KEY 2
#define UP_KEY 3
#define LT_KEY 4


    
    

    /** FSM for the push button **/
    typedef enum {
        NavKey_WAITPUSH,
        NavKey_WAITRELEASE,
        NavKey_WAITDOUBLEPUSH,
        NavKey_WAITDOUBLERELEASED,
        NavKey_TIMEOUT,
        NavKey_PUSHRESET,
    } NavKey_SWITCH_STATUS;

    bool NavKeySwitch_GetValue(void);
    bool NavKeySwitch_GetValueFiltered(void);
    void CLC_1_Interrupt(void);
    void CLC_2_Interrupt(void);
    void NavKey_PushButton_FSM(void);
    void NavKey_FSM(void);


#ifdef	__cplusplus
}
#endif /* __cplusplus */

#endif	/* XC_HEADER_TEMPLATE_H */

