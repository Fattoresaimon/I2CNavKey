/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16F18345
        Driver Version    :  2.01
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set ADD0 aliases
#define ADD0_TRIS                 TRISAbits.TRISA0
#define ADD0_LAT                  LATAbits.LATA0
#define ADD0_PORT                 PORTAbits.RA0
#define ADD0_WPU                  WPUAbits.WPUA0
#define ADD0_OD                   ODCONAbits.ODCA0
#define ADD0_ANS                  ANSELAbits.ANSA0
#define ADD0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define ADD0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define ADD0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define ADD0_GetValue()           PORTAbits.RA0
#define ADD0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define ADD0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define ADD0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define ADD0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define ADD0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define ADD0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define ADD0_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define ADD0_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set ADD1 aliases
#define ADD1_TRIS                 TRISAbits.TRISA1
#define ADD1_LAT                  LATAbits.LATA1
#define ADD1_PORT                 PORTAbits.RA1
#define ADD1_WPU                  WPUAbits.WPUA1
#define ADD1_OD                   ODCONAbits.ODCA1
#define ADD1_ANS                  ANSELAbits.ANSA1
#define ADD1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define ADD1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define ADD1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define ADD1_GetValue()           PORTAbits.RA1
#define ADD1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define ADD1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define ADD1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define ADD1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define ADD1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define ADD1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define ADD1_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define ADD1_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set ADD2 aliases
#define ADD2_TRIS                 TRISAbits.TRISA2
#define ADD2_LAT                  LATAbits.LATA2
#define ADD2_PORT                 PORTAbits.RA2
#define ADD2_WPU                  WPUAbits.WPUA2
#define ADD2_OD                   ODCONAbits.ODCA2
#define ADD2_ANS                  ANSELAbits.ANSA2
#define ADD2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define ADD2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define ADD2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define ADD2_GetValue()           PORTAbits.RA2
#define ADD2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define ADD2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define ADD2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define ADD2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define ADD2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define ADD2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define ADD2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define ADD2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set ADD3 aliases
#define ADD3_PORT               PORTAbits.RA3
#define ADD3_WPU                WPUAbits.WPUA3
#define ADD3_GetValue()           PORTAbits.RA3
#define ADD3_SetPullup()      do { WPUAbits.WPUA3 = 1; } while(0)
#define ADD3_ResetPullup()    do { WPUAbits.WPUA3 = 0; } while(0)

// get/set S3 aliases
#define S3_TRIS                 TRISAbits.TRISA4
#define S3_LAT                  LATAbits.LATA4
#define S3_PORT                 PORTAbits.RA4
#define S3_WPU                  WPUAbits.WPUA4
#define S3_OD                   ODCONAbits.ODCA4
#define S3_ANS                  ANSELAbits.ANSA4
#define S3_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define S3_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define S3_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define S3_GetValue()           PORTAbits.RA4
#define S3_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define S3_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define S3_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define S3_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define S3_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define S3_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define S3_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define S3_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set S1 aliases
#define S1_TRIS                 TRISBbits.TRISB4
#define S1_LAT                  LATBbits.LATB4
#define S1_PORT                 PORTBbits.RB4
#define S1_WPU                  WPUBbits.WPUB4
#define S1_OD                   ODCONBbits.ODCB4
#define S1_ANS                  ANSELBbits.ANSB4
#define S1_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define S1_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define S1_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define S1_GetValue()           PORTBbits.RB4
#define S1_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define S1_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define S1_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define S1_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define S1_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define S1_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define S1_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define S1_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set INT aliases
#define INT_TRIS                 TRISBbits.TRISB5
#define INT_LAT                  LATBbits.LATB5
#define INT_PORT                 PORTBbits.RB5
#define INT_WPU                  WPUBbits.WPUB5
#define INT_OD                   ODCONBbits.ODCB5
#define INT_ANS                  ANSELBbits.ANSB5
#define INT_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define INT_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define INT_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define INT_GetValue()           PORTBbits.RB5
#define INT_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define INT_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define INT_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define INT_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define INT_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define INT_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define INT_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define INT_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set SCL1 aliases
#define SCL1_TRIS                 TRISBbits.TRISB6
#define SCL1_LAT                  LATBbits.LATB6
#define SCL1_PORT                 PORTBbits.RB6
#define SCL1_WPU                  WPUBbits.WPUB6
#define SCL1_OD                   ODCONBbits.ODCB6
#define SCL1_ANS                  ANSELBbits.ANSB6
#define SCL1_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define SCL1_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define SCL1_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define SCL1_GetValue()           PORTBbits.RB6
#define SCL1_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define SCL1_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define SCL1_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define SCL1_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define SCL1_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define SCL1_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define SCL1_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define SCL1_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set SDA1 aliases
#define SDA1_TRIS                 TRISBbits.TRISB7
#define SDA1_LAT                  LATBbits.LATB7
#define SDA1_PORT                 PORTBbits.RB7
#define SDA1_WPU                  WPUBbits.WPUB7
#define SDA1_OD                   ODCONBbits.ODCB7
#define SDA1_ANS                  ANSELBbits.ANSB7
#define SDA1_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define SDA1_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define SDA1_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define SDA1_GetValue()           PORTBbits.RB7
#define SDA1_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define SDA1_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define SDA1_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define SDA1_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define SDA1_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define SDA1_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define SDA1_SetAnalogMode()      do { ANSELBbits.ANSB7 = 1; } while(0)
#define SDA1_SetDigitalMode()     do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set GP3 aliases
#define GP3_TRIS                 TRISCbits.TRISC0
#define GP3_LAT                  LATCbits.LATC0
#define GP3_PORT                 PORTCbits.RC0
#define GP3_WPU                  WPUCbits.WPUC0
#define GP3_OD                   ODCONCbits.ODCC0
#define GP3_ANS                  ANSELCbits.ANSC0
#define GP3_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define GP3_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define GP3_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define GP3_GetValue()           PORTCbits.RC0
#define GP3_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define GP3_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define GP3_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define GP3_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define GP3_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define GP3_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define GP3_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define GP3_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set GP2 aliases
#define GP2_TRIS                 TRISCbits.TRISC1
#define GP2_LAT                  LATCbits.LATC1
#define GP2_PORT                 PORTCbits.RC1
#define GP2_WPU                  WPUCbits.WPUC1
#define GP2_OD                   ODCONCbits.ODCC1
#define GP2_ANS                  ANSELCbits.ANSC1
#define GP2_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define GP2_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define GP2_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define GP2_GetValue()           PORTCbits.RC1
#define GP2_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define GP2_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define GP2_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define GP2_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define GP2_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define GP2_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define GP2_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define GP2_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set GP1 aliases
#define GP1_TRIS                 TRISCbits.TRISC2
#define GP1_LAT                  LATCbits.LATC2
#define GP1_PORT                 PORTCbits.RC2
#define GP1_WPU                  WPUCbits.WPUC2
#define GP1_OD                   ODCONCbits.ODCC2
#define GP1_ANS                  ANSELCbits.ANSC2
#define GP1_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define GP1_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define GP1_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define GP1_GetValue()           PORTCbits.RC2
#define GP1_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define GP1_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define GP1_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define GP1_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define GP1_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define GP1_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define GP1_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define GP1_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set S5 aliases
#define S5_TRIS                 TRISCbits.TRISC3
#define S5_LAT                  LATCbits.LATC3
#define S5_PORT                 PORTCbits.RC3
#define S5_WPU                  WPUCbits.WPUC3
#define S5_OD                   ODCONCbits.ODCC3
#define S5_ANS                  ANSELCbits.ANSC3
#define S5_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define S5_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define S5_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define S5_GetValue()           PORTCbits.RC3
#define S5_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define S5_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define S5_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define S5_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define S5_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define S5_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define S5_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define S5_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()               do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()                do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()                do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()       do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()      do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()               do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()                do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()                do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()       do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()      do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSC5 = 0; } while(0)

// get/set S4 aliases
#define S4_TRIS                 TRISCbits.TRISC6
#define S4_LAT                  LATCbits.LATC6
#define S4_PORT                 PORTCbits.RC6
#define S4_WPU                  WPUCbits.WPUC6
#define S4_OD                   ODCONCbits.ODCC6
#define S4_ANS                  ANSELCbits.ANSC6
#define S4_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define S4_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define S4_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define S4_GetValue()           PORTCbits.RC6
#define S4_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define S4_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define S4_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define S4_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define S4_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define S4_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define S4_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define S4_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set S2 aliases
#define S2_TRIS                 TRISCbits.TRISC7
#define S2_LAT                  LATCbits.LATC7
#define S2_PORT                 PORTCbits.RC7
#define S2_WPU                  WPUCbits.WPUC7
#define S2_OD                   ODCONCbits.ODCC7
#define S2_ANS                  ANSELCbits.ANSC7
#define S2_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define S2_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define S2_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define S2_GetValue()           PORTCbits.RC7
#define S2_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define S2_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define S2_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define S2_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define S2_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define S2_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define S2_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define S2_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/