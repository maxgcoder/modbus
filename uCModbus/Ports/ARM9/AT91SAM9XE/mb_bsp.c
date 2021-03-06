/*
*********************************************************************************************************
*                                              uC/Modbus
*                                       The Embedded Modbus Stack
*
*                    Copyright 2003-2020 Silicon Laboratories Inc. www.silabs.com
*
*                                 SPDX-License-Identifier: APACHE-2.0
*
*               This software is subject to an open source license and is distributed by
*                Silicon Laboratories Inc. pursuant to the terms of the Apache License,
*                    Version 2.0 available at www.apache.org/licenses/LICENSE-2.0.
*
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                            uC/Modbus
*
*                                      Board Support Package
*                                     Atmel AT91SAM9XE (ARM9)
*
* Filename : mb_bsp.c
* Version  : V2.14.00
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include    <mb.h>
#include    <mb_bsp.h>
#include    <bsp.h>

/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/
                                                                /* ------------------ BASE REGISTER ADDRESS ---------------- */
#define  AT91SAM9XE_USART0_BASE_ADDR    ((CPU_INT32U)0xFFFB0000)
#define  AT91SAM9XE_USART1_BASE_ADDR    ((CPU_INT32U)0xFFFB4000)
#define  AT91SAM9XE_USART2_BASE_ADDR    ((CPU_INT32U)0xFFFB8000)
#define  AT91SAM9XE_USART3_BASE_ADDR    ((CPU_INT32U)0xFFFD0000)
#define  AT91SAM9XE_USART4_BASE_ADDR    ((CPU_INT32U)0xFFFD4000)
#define  AT91SAM9XE_DBGU_BASE_ADDR      ((CPU_INT32U)0xFFFFF200)

#define  AT91SAM9XE_AIC_BASE_ADDR       ((CPU_INT32U)0xFFFFF000)

#define  AT91SAM9XE_PIOA_BASE_ADDR      ((CPU_INT32U)0xFFFFF400)
#define  AT91SAM9XE_PIOB_BASE_ADDR      ((CPU_INT32U)0xFFFFF600)

#define  AT91SAM9XE_PMC_BASE_ADDR       ((CPU_INT32U)0xFFFFFC00)

#define  AT91SAM9XE_TC0_BASE_ADDR       ((CPU_INT32U)0xFFFA0000)
#define  AT91SAM9XE_TC1_BASE_ADDR       ((CPU_INT32U)0xFFFA0040)
#define  AT91SAM9XE_TC2_BASE_ADDR       ((CPU_INT32U)0xFFFA0080)
#define  AT91SAM9XE_TC3_BASE_ADDR       ((CPU_INT32U)0xFFFDC000)
#define  AT91SAM9XE_TC4_BASE_ADDR       ((CPU_INT32U)0xFFFDC040)
#define  AT91SAM9XE_TC5_BASE_ADDR       ((CPU_INT32U)0xFFFDC080)

                                                                /* -------------------- Peripheral IDs -------------------- */
#define  AT91SAM9XE_PER_ID_SYS                      1

#define  AT91SAM9XE_PER_ID_USART0                   6
#define  AT91SAM9XE_PER_ID_USART1                   7
#define  AT91SAM9XE_PER_ID_USART2                   8
#define  AT91SAM9XE_PER_ID_USART3                  23
#define  AT91SAM9XE_PER_ID_USART4                  24

#define  AT91SAM9XE_PER_ID_TC0                     17
#define  AT91SAM9XE_PER_ID_TC1                     18
#define  AT91SAM9XE_PER_ID_TC2                     19
#define  AT91SAM9XE_PER_ID_TC3                     26
#define  AT91SAM9XE_PER_ID_TC4                     27
#define  AT91SAM9XE_PER_ID_TC5                     28


/*
*********************************************************************************************************
*                                            AT91SAM9XE REGISTER BIT DEFINES
*********************************************************************************************************
*/
                                                                /* --------- USART MODE (US_MR) REGISTER BIT DEFINES ------- */
#define  AT91SAM9XE_USART_MR_MODE_NORMAL             (0x00 <<  0)      
#define  AT91SAM9XE_USART_MR_MODE_RS485              (0x01 <<  0)
#define  AT91SAM9XE_USART_MR_MODE_IRDA               (0x08 <<  0)

#define  AT91SAM9XE_USART_MR_USCLKS_MCK              (0x00 <<  4)
#define  AT91SAM9XE_USART_MR_USCLKS_MCK_DIV          (0x01 <<  4)
#define  AT91SAM9XE_USART_MR_USCLKS_SCK              (0x03 <<  4)

#define  AT91SAM9XE_USART_MR_CHRL_5                  (0x00 <<  6)
#define  AT91SAM9XE_USART_MR_CHRL_6                  (0x01 <<  6)
#define  AT91SAM9XE_USART_MR_CHRL_7                  (0x02 <<  6)
#define  AT91SAM9XE_USART_MR_CHRL_8                  (0x03 <<  6)

#define  AT91SAM9XE_USART_MR_PAR_EVEN                (0x00 <<  9)
#define  AT91SAM9XE_USART_MR_PAR_ODD                 (0x01 <<  9)
#define  AT91SAM9XE_USART_MR_PAR_FORCED0             (0x02 <<  9)
#define  AT91SAM9XE_USART_MR_PAR_FORCED1             (0x03 <<  9)
#define  AT91SAM9XE_USART_MR_PAR_NONE                (0x04 <<  9)
#define  AT91SAM9XE_USART_MR_PAR_MULTIDROP           (0x06 <<  9)
 
#define  AT91SAM9XE_USART_MR_NBSTOP_1                (0x00 << 12)
#define  AT91SAM9XE_USART_MR_NBSTOP_1_5              (0x01 << 12)
#define  AT91SAM9XE_USART_MR_NBSTOP_2                (0x02 << 12)

#define  AT91SAM9XE_USART_MR_CHMODE_NORMAL           (0x00 << 14)
#define  AT91SAM9XE_USART_MR_CHMODE_AUTOECHO         (0x01 << 14)
#define  AT91SAM9XE_USART_MR_CHMODE_LOOPBACK         (0x02 << 14)
#define  AT91SAM9XE_USART_MR_CHMODE_REMOTE           (0x03 << 14)

                                                                /* ------ USART CONTROL (US_CR) REGISTER BIT DEFINES ------- */
#define  AT91SAM9XE_USART_CR_RSTRX                     DEF_BIT_02
#define  AT91SAM9XE_USART_CR_RSTTX                     DEF_BIT_03
#define  AT91SAM9XE_USART_CR_RXEN                      DEF_BIT_04
#define  AT91SAM9XE_USART_CR_RXDIS                     DEF_BIT_05
#define  AT91SAM9XE_USART_CR_TXEN                      DEF_BIT_06
#define  AT91SAM9XE_USART_CR_TXDIS                     DEF_BIT_07
#define  AT91SAM9XE_USART_CR_RSTSTA                    DEF_BIT_08

                                                                /* -- USART CHANNEL STATUS (US_CSR) REGISTER BIT DEFINES --- */
#define  AT91SAM9XE_USART_CSR_RXRDY                    DEF_BIT_00
#define  AT91SAM9XE_USART_CSR_TXRDY                    DEF_BIT_01
#define  AT91SAM9XE_USART_CSR_ENDRX                    DEF_BIT_03
#define  AT91SAM9XE_USART_CSR_ENDTX                    DEF_BIT_04
#define  AT91SAM9XE_USART_CSR_OVRE                     DEF_BIT_05
#define  AT91SAM9XE_USART_CSR_FRAME                    DEF_BIT_06
#define  AT91SAM9XE_USART_CSR_PARE                     DEF_BIT_07
#define  AT91SAM9XE_USART_CSR_TIMEOUT                  DEF_BIT_08
#define  AT91SAM9XE_USART_CSR_TXEMPTY                  DEF_BIT_09
#define  AT91SAM9XE_USART_CSR_ITERATION                DEF_BIT_09
#define  AT91SAM9XE_USART_CSR_TXBUFE                   DEF_BIT_11
#define  AT91SAM9XE_USART_CSR_RXBUFF                   DEF_BIT_12

#define  AT91SAM9XE_USART_IDR_DIS_ALL                  0xFFFFFFFF

                                                               /* -------------- TC_CMR Register Bit Defines ------------- */
#define  AT91SAM9XE_TC_CMR_CPCTRG_EN                   DEF_BIT_14

                                                               /* -------------- TC_IER Register Bit Defines ------------- */
#define  AT91SAM9XE_TC_IER_CPCS                        DEF_BIT_04

                                                               /* --------------- TC_SR Register Bit Defines ------------- */
#define  AT91SAM9XE_TC_SR_CPCS                         DEF_BIT_04

                                                               /* --------------- TC_CR Register Bit Defines ------------- */
#define  AT91SAM9XE_TC_CCR_CLKEN                       DEF_BIT_00
#define  AT91SAM9XE_TC_CCR_CLKDIS                      DEF_BIT_01
#define  AT91SAM9XE_TC_CCR_SWTRG                       DEF_BIT_02

                                                                /* --------------- US_CR Register Bit Defines ------------- */
#define  AT91SAM9XE_US_RSTRX                           DEF_BIT_02
#define  AT91SAM9XE_US_RSTTX                           DEF_BIT_03
#define  AT91SAM9XE_US_RXEN                            DEF_BIT_04
#define  AT91SAM9XE_US_RXDIS                           DEF_BIT_05
#define  AT91SAM9XE_US_TXEN                            DEF_BIT_06
#define  AT91SAM9XE_US_TXDIS                           DEF_BIT_07
#define  AT91SAM9XE_US_RSTSTA                          DEF_BIT_08

                                                                /* ------------- AIC_SMR Register Bit Defines ------------- */
#define  AT91SAM9XE_AIC_SMR_SRCTYPE_HIGH_LEVEL       (0x02 <<  5)
#define  AT91SAM9XE_AIC_SMR_PRIOR_LOWEST             (0x00 <<  0)

                                                                /* -------------  GPIOx Register Bit Defines -------------- */
                                                                /* Set GPIOB pins 4 and 5                                   */
#define  AT91SAM9XE_PIOB_PINS_USART0                  (DEF_BIT_04 | \
                                                       DEF_BIT_05)
                                                                /* Set GPIOB pins 6 and 7                                   */
#define  AT91SAM9XE_PIOB_PINS_USART1                  (DEF_BIT_06 | \
                                                       DEF_BIT_07)
                                                                /* Set GPIOB pins 8 and 9                                   */
#define  AT91SAM9XE_PIOB_PINS_USART2                  (DEF_BIT_08 | \
                                                       DEF_BIT_09)
                                                                /* Set GPIOB pins 10 and 11                                 */
#define  AT91SAM9XE_PIOB_PINS_USART3                  (DEF_BIT_10 | \
                                                       DEF_BIT_11)
                                                                /* Set GPIOB pins 18 and 19                                 */                      
#define  AT91SAM9XE_PIOB_PINS_DBG                     (DEF_BIT_18 | \
                                                       DEF_BIT_19)
                                                                /* Set GPIOA pins 30 and 31                                 */                      
#define  AT91SAM9XE_PIOA_PINS_USART4                  (DEF_BIT_30 | \
                                                       DEF_BIT_31)

/*
*********************************************************************************************************
*                                        REGISTER DEFINITIONS
*
* Note(s) : (1) The device register definition structure MUST take into account appropriate
*               register offsets and apply reserved space as required.  The registers listed
*               within the register definition structure MUST reflect the exact ordering and
*               data sizes illustrated in the device user guide.
*********************************************************************************************************
*/
                                                                /* +------------|---------------------|--------------------+ */
                                                                /* |Offset      | Register            | Name               | */
                                                                /* |------------|---------------------|--------------------| */
                                                                /* |========= UASART/DBGU UNIT REGISTERS ================  | */
typedef  struct  at91sam9xe_usart {                             /* +------------|---------------------|--------------------+ */
    CPU_INT32U  US_CR;                                          /* |0x0000      | Control             |US_CR               | */
    CPU_INT32U  US_MR;                                          /* |0x0004      | Mode                |US_MR               | */
    CPU_INT32U  US_IER;                                         /* |0x0008      | Interrupt Enable    |US_IER              | */
    CPU_INT32U  US_IDR;                                         /* |0x000C      | Interrupt Disable   |US_IDR              | */                                         
    CPU_INT32U  US_IMR;                                         /* |0x0010      | Interrupt Mask      |US_IMR              | */
    CPU_INT32U  US_CSR;                                         /* |0x0014      | Channel Status      |US_CSR              | */
    CPU_INT32U  US_RHR;                                         /* |0x0018      | Reciver Holding     |US_RHR              | */
    CPU_INT32U  US_THR;                                         /* |0x001C      | Transmitter Holding |US_THR              | */
    CPU_INT32U  US_BRGR;                                        /* |0x0020      | Baud Rate Generator |US_BRGR             | */
} AT91SAM9XE_USART;                                             /* +------------|---------------------|--------------------+ */
                                                                /* |================= PIO REGISTERS =====================  | */
typedef  struct  at91sam9xe_pio {                               /* +------------|---------------------|--------------------+ */
    CPU_INT32U  PIO_PER;                                        /* |0x0000      | PIO Enable          |PIO_PER             | */
    CPU_INT32U  PIO_PDR;                                        /* |0x0004      | PIO Disable         |PIO_PDR             | */
    CPU_INT32U  PIO_PSR;                                        /* |0x0008      | PIO Status          |PIO_PSR             | */
    CPU_INT32U  RESERVED0;                                      /* |0x000C      | Reserved            |------              | */
    CPU_INT32U  PIO_OER;                                        /* |0x0010      | Output Enable       |PIO_IER             | */                                         
    CPU_INT32U  PIO_ODR;                                        /* |0x0013      | Output Disable      |PIO_ODR             | */
    CPU_INT32U  PIO_OSR;                                        /* |0x0018      | Output Status       |PIO_OSR             | */
    CPU_INT32U  RESERVED1;                                      /* |0x001C      | Reserved            |------              | */
    CPU_INT32U  PIO_IFER;                                       /* |0x0020      | Glitch IN Fil En    |PIO_IFER            | */                                         
    CPU_INT32U  PIO_IFDR;                                       /* |0x0024      | Glitch IN Fil Dis   |PIO_IFDR            | */
    CPU_INT32U  PIO_IFSR;                                       /* |0x0028      | Glitch IN Fil Stat  |PIO_IFSR            | */
    CPU_INT32U  RESERVED2;                                      /* |0x002C      | Reserved            |------              | */
    CPU_INT32U  PIO_SODR;                                       /* |0x0030      | Set Output Data     |PIO_SODR            | */
    CPU_INT32U  PIO_CODR;                                       /* |0x0034      | Clear Output Data   |PIO_CODR            | */
    CPU_INT32U  PIO_ODSR;                                       /* |0x0038      | Output Data Status  |PIO_ODSR            | */
    CPU_INT32U  PIO_PDSR;                                       /* |0x003C      | Pin Data status     |PIO_PDSR            | */
    CPU_INT32U  PIO_IER;                                        /* |0x0040      | Interrupt Enable    |PIO_IER             | */
    CPU_INT32U  PIO_IDR;                                        /* |0x0044      | Interrupt Disable   |PIO_IDR             | */
    CPU_INT32U  PIO_IMR;                                        /* |0x0048      | Interrupt Mask      |PIO_IMR             | */
    CPU_INT32U  PIO_ISR;                                        /* |0x004C      | Interrupt Status    |PIO_ISR             | */
    CPU_INT32U  PIO_MDER;                                       /* |0x0050      | Multi-Driver Enable |PIO_MDER            | */
    CPU_INT32U  PIO_MDDR;                                       /* |0x0054      | Multi-Driver Dis    |PIO_MDDR            | */
    CPU_INT32U  PIO_MDSR;                                       /* |0x0058      | Multi-Driver Status |PIO_MDSR            | */
    CPU_INT32U  RESERVED3;                                      /* |0x005C      | Reserved            |-------             | */
    CPU_INT32U  PIO_PUDR;                                       /* |0x0060      | Pull-up Disable     |PIO_PUDR            | */
    CPU_INT32U  PIO_PUER;                                       /* |0x0064      | Pull-up Enable      |PIO_PUER            | */
    CPU_INT32U  PIO_PUSR;                                       /* |0x0068      | Pad Pull-up Status  |PIO_PUSR            | */
    CPU_INT32U  RESERVED4;                                      /* |0x006C      | Reserved            |------              | */
    CPU_INT32U  PIO_ASR;                                        /* |0x0070      | Peripheral A Sel    |PIO_ASR             | */
    CPU_INT32U  PIO_BSR;                                        /* |0x0074      | Peripheral B Sel    |PIO_BSR             | */
    CPU_INT32U  PIO_ABSR;                                       /* |0x0078      | AB Status           |PIO_ABSR            | */
    CPU_INT32U  RESERVED5[9];                                   /* |0x7C-0x9C   | Reserved            |------              | */
    CPU_INT32U  PIO_OWER;                                       /* |0x00A0      | Output write enable |PIO_OWER            | */
    CPU_INT32U  PIO_OWDR;                                       /* |0x00A4      | Output write dis    |PIO_OWDR            | */
    CPU_INT32U  PIO_OWSR;                                       /* |0x00A8      | Output write status |PIO_OWSR            | */
    CPU_INT32U  RESERVED6;                                      /* |0x00AC      | Reserved            |------              | */ 
} AT91SAM9XE_PIO;                                               /* +------------|---------------------|--------------------+ */
                                                                /* |================= AIC REGISTERS =====================  | */
typedef  struct  at91sam9xe_aic {                               /* +------------|---------------------|--------------------+ */
    CPU_INT32U  AIC_SMR[32];                                    /* |0x04-0x7C   | Source Mode 0..31   |AIC_SMR0..AIC_SMR32 | */
    CPU_INT32U  AIC_SVR[32];                                    /* |0x80-0xFC   | Source Vector 0..31 |AIC_SVR0..AIC_SVR31 | */
    CPU_INT32U  AIC_IVR;                                        /* |0x0100      | Interrupt Vector    |AIC_IVR             | */
    CPU_INT32U  AIC_FVR;                                        /* |0x0104      | FIQ Interrup vector |AIC_FVR             | */
    CPU_INT32U  AIC_ISR;                                        /* |0x0108      | Interrupt Status    |AIC_ISR             | */
    CPU_INT32U  AIC_IPR;                                        /* |0x010C      | Interrupt Pending   |AIC_IPR             | */
    CPU_INT32U  AIC_IMR;                                        /* |0x0110      | Interrupt Mask      |AIC_MASK            | */
    CPU_INT32U  AIC_CISR;                                       /* |0x0114      | Core interrupt stat |AIC_CISR            | */
    CPU_INT32U  RESERVED0;                                      /* |0x0118      | Reserved            |------              | */ 
    CPU_INT32U  RESERVED1;                                      /* |0x011C      | Reserved            |------              | */ 
    CPU_INT32U  AIC_IECR;                                       /* |0x0120      | Interrupt En  Com   |AIC_IECR            | */
    CPU_INT32U  AIC_IDCR;                                       /* |0x0123      | Interrupt Dis Com   |AIC_IDCR            | */
    CPU_INT32U  AIC_ICCR;                                       /* |0x0128      | Interrupt Clr Com   |AIC_ICCR            | */
    CPU_INT32U  AIC_ISCR;                                       /* |0x012C      | Interrupt Set Com   |AIC_ISCR            | */
    CPU_INT32U  AIC_EOICR;                                      /* |0x0130      | End of Interrupt Com|AIC_EOIC            | */
    CPU_INT32U  AIC_SPU;                                        /* |0x0104      | Spurious Interrupt  |AIC_SPU             | */
    CPU_INT32U  AIC_DCR;                                        /* |0x0104      | Debug control       |AIC_DCR             | */
    CPU_INT32U  RESERVED2;                                      /* |0x0104      | Reserved            |-------             | */ 
    CPU_INT32U  AIC_FFER;                                       /* |0x0104      | Fast Forcing En     |AIC_FFER            | */
    CPU_INT32U  AIC_FFDR;                                       /* |0x0104      | Fast Forcing Dis    |AIC_FFDR            | */
    CPU_INT32U  AIC_FFSR;                                       /* |0x0104      | Fast Forcing Status |AIC_FSR             | */
} AT91SAM9XE_AIC;                                               /* +------------|---------------------|--------------------+ */
                                                                /* |================= PMC REGISTER  =====================  | */
typedef struct at91sam9xe_pmc {                                 /* +------------|---------------------|--------------------+ */
    CPU_INT32U  PMC_SCER;                                       /* |0x0000      | System Clk Enable   |PMC_SCER            | */
    CPU_INT32U  PMC_SCDR;                                       /* |0x0004      | System Clk Disable  |PMC_SCDR            | */
    CPU_INT32U  PMC_SCSR;                                       /* |0x0008      | Interrupt Vector    |PMC_SCSR            | */
    CPU_INT32U  RESERVED0;                                      /* |0x000C      | Reserved            |-------             | */
    CPU_INT32U  PMC_PCER;                                       /* |0x0010      | Peripheral Clk En   |PMC_PCER            | */
    CPU_INT32U  PMC_PCDR;                                       /* |0x0014      | Peripheral Clk Dis  |PMC_PCDR            | */
    CPU_INT32U  PMC_PCSR;                                       /* |0x0018      | Peripheral Clk Stat |PMC_PCSR            | */ 
} AT91SAM9XE_PMC;                                               /* +------------|---------------------|--------------------+ */
                                                                /* |================= TC CHANNEL REGISTER  ==============  | */
typedef struct at91sam9xe_tc    {                               /* +------------|---------------------|--------------------+ */
    CPU_INT32U  TC_CCR;                                         /* |0x0000      | Channel Control     |TC_CCR              | */
    CPU_INT32U  TC_CMR;                                         /* |0x0004      | Channel Mode        |TC_CMR              | */
    CPU_INT32U  RESERVED0;                                      /* |0x0008      | Reserved            |-------             | */
    CPU_INT32U  RESERVED1;                                      /* |0x000C      | Reserved            |-------             | */
    CPU_INT32U  TC_CV;                                          /* |0x0010      | Counter Value       |TC_CV               | */
    CPU_INT32U  TC_RA;                                          /* |0x0014      | Register A          |TC_RA               | */
    CPU_INT32U  TC_RB;                                          /* |0x0018      | Register B          |TC_RB               | */
    CPU_INT32U  TC_RC;                                          /* |0x001C      | Register C          |TC_RC               | */
    CPU_INT32U  TC_SR;                                          /* |0x0020      | Status Register     |TC_SR               | */
    CPU_INT32U  TC_IER;                                         /* |0x0024      | Interrupt Enable    |TC_IER              | */
    CPU_INT32U  TC_IDR;                                         /* |0x0028      | Interrupt Disable   |TC_IDR              | */
    CPU_INT32U  TC_IMR;                                         /* |0x002C      | Interrupt Mask      |TC_IMR              | */
} AT91SAM9XE_TC;                                               /* +------------|---------------------|--------------------+ */


/*
*********************************************************************************************************
*                                    LOCAL CONFIGURATION ERRORS
*********************************************************************************************************
*/
                                                                /*-------------- UART MODE CONFIGURATION ERRORS ------------ */
#ifndef MB_BSP_CFG_UART_00_MODE
    #error  "MB_BSP_CFG_UART_00_MODE           not #define'd in 'app_cfg.h'          "
    #error  "                                  [MUST be  MB_BSP_UART_RS232_MODE   ]  "
    #error  "                                  [     ||  MB_BSP_UART_RS485_MODE   ]  "

#elif   (MB_BSP_CFG_UART_00_MODE != MB_BSP_UART_RS232_MODE  ) && \
        (MB_BSP_CFG_UART_00_MODE != MB_BSP_UART_RS485_MODE  ) 
    #error  "MB_BSP_CFG_UART_00_MODE           illegally #define'd in 'app_cfg.h'    "
    #error  "                                  [MUST be  MB_BSP_UART_RS232_MODE   ]  "
    #error  "                                  [     ||  MB_BSP_UART_RS485_MODE   ]  "
#endif

#ifndef MB_BSP_CFG_UART_01_MODE
    #error  "MB_BSP_CFG_UART_01_MODE           not #define'd in 'app_cfg.h'          "
    #error  "                                  [MUST be  MB_BSP_UART_RS232_MODE   ]  "
    #error  "                                  [     ||  MB_BSP_UART_RS485_MODE   ]  "

#elif   (MB_BSP_CFG_UART_01_MODE != MB_BSP_UART_RS232_MODE  ) && \
        (MB_BSP_CFG_UART_01_MODE != MB_BSP_UART_RS485_MODE  ) 
    #error  "MB_BSP_CFG_UART_01_MODE           illegally #define'd in 'app_cfg.h'    
    #error  "                                  [MUST be  MB_BSP_UART_RS232_MODE   ]  "
    #error  "                                  [     ||  MB_BSP_UART_RS485_MODE   ]  "
#endif

#ifndef MB_BSP_CFG_UART_02_MODE
    #error  "MB_BSP_CFG_UART_01_MODE           not #define'd in 'app_cfg.h'          "
    #error  "                                  [MUST be  MB_BSP_UART_RS232_MODE   ]  "
    #error  "                                  [     ||  MB_BSP_UART_RS485_MODE   ]  "

#elif   (MB_BSP_CFG_UART_02_MODE != MB_BSP_UART_RS232_MODE  ) && \
        (MB_BSP_CFG_UART_02_MODE != MB_BSP_UART_RS485_MODE  ) 
    #error  "MB_BSP_CFG_UART_01_MODE           illegally #define'd in 'app_cfg.h'    "
    #error  "                                  [MUST be  MB_BSP_UART_RS232_MODE   ]  "
    #error  "                                  [     ||  MB_BSP_UART_RS485_MODE   ]  "
#endif

                                                                /*-------------- TIMER SEL CONFIGURATION  ------------ */
#ifndef MS_BSP_CFG_TMR
    #error  "MS_BSP_CFG_TMR           not #define'd in 'app_cfg.h'                  "
    #error  "                                  [MUST be  MB_BSP_TMR_0   ]           "
    #error  "                                  [     ||  MB_BSP_TMR_1   ]           "
    #error  "                                  [     ||  MB_BSP_TMR_2   ]           "

#elif   (MS_BSP_CFG_TMR != MB_BSP_TMR_0 ) && \
        (MS_BSP_CFG_TMR != MB_BSP_TMR_1 ) && \
        (MS_BSP_CFG_TMR != MB_BSP_TMR_2 )            
    #error  "MS_BSP_CFG_TMR           illegally #define'd in 'app_cfg.h'          "
    #error  "                                  [MUST be  MB_BSP_TMR_0   ]         "
    #error  "                                  [     ||  MB_BSP_TMR_1   ]         "
    #error  "                                  [     ||  MB_BSP_TMR_2   ]         "

#endif


/*
*********************************************************************************************************
*                                             LOCAL VARIABLES
*********************************************************************************************************
*/

#if (MODBUS_CFG_RTU_EN == DEF_ENABLED)
static  CPU_INT32U  MB_Tmr_ReloadCnts;
#endif


/*
*********************************************************************************************************
*                                             MB_CommExit()
*
* Description : This function is called to terminate Modbus communications.  All Modbus channels are close.
*
* Argument(s) : none
*
* Return(s)   : none.
*
* Caller(s)   : MB_Exit()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_CommExit (void)
{
    CPU_INT08U   ch;
    MODBUS_CH   *pch;


    pch = &MB_ChTbl[0];
    for (ch = 0; ch < MODBUS_CFG_MAX_CH; ch++) {
        MB_CommTxIntDis(pch);
        MB_CommRxIntDis(pch);
        pch++;
    }
}


/*
*********************************************************************************************************
*                                           MB_CommPortCfg()
*
* Description : This function initializes the serial port to the desired baud rate and the UART will be
*               configured for N, 8, 1 (No parity, 8 bits, 1 stop).
*
* Argument(s) : pch        is a pointer to the Modbus channel
*               port_nbr   is the desired serial port number.  This argument allows you to assign a
*                          specific serial port to a sepcific Modbus channel.
*               baud       is the desired baud rate for the serial port.
*               parity     is the desired parity and can be either:
*
*                          MODBUS_PARITY_NONE
*                          MODBUS_PARITY_ODD
*                          MODBUS_PARITY_EVEN
*
*               bits       specifies the number of bit and can be either 7 or 8.
*               stops      specifies the number of stop bits and can either be 1 or 2
*
* Return(s)   : none.
*
* Caller(s)   : MB_CfgCh()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_CommPortCfg (MODBUS_CH  *pch,
                      CPU_INT08U  port_nbr,
                      CPU_INT32U  baud,
                      CPU_INT08U  bits,
                      CPU_INT08U  parity,
                      CPU_INT08U  stops)
{
              CPU_INT32U         dev_mclk_freq;
              CPU_INT32U         dev_usart_mr; 
              CPU_INT16U         dev_usart_brgr;    
              CPU_INT08U         dev_per_id; 
              CPU_INT32U         dev_pio_val;
              CPU_INT32U         dev_usart_handler;    
    
    volatile  AT91SAM9XE_PIO    *p_dev_pio;
    volatile  AT91SAM9XE_USART  *p_dev_usart;  
    volatile  AT91SAM9XE_AIC    *p_dev_aic;
    volatile  AT91SAM9XE_PMC    *p_dev_pmc;

    
    if (pch != (MODBUS_CH *)0){
        pch->PortNbr        = port_nbr;                               /* Store configuration in channel              */
        pch->BaudRate       = baud;
        pch->Parity         = parity;
        pch->Bits           = bits;
        pch->Stops          = stops;        
        
                                                                      /* ------ USART CONFIGURATION SETUP ----------  */
        switch (parity) {                                             /* (1) Setup USART parity                       */
            case MODBUS_PARITY_ODD:
                 dev_usart_mr = AT91SAM9XE_USART_MR_PAR_ODD;
                 break;
                 
            case MODBUS_PARITY_EVEN:            
                 dev_usart_mr = AT91SAM9XE_USART_MR_PAR_ODD;
                 break;

            case MODBUS_PARITY_NONE:
            default:
                 dev_usart_mr = AT91SAM9XE_USART_MR_PAR_NONE;
                 break;
        }
        
        if (bits == 7) {                                              /* (2) Setup #bits                               */
            dev_usart_mr |= AT91SAM9XE_USART_MR_CHRL_7;
        } else {
            dev_usart_mr |= AT91SAM9XE_USART_MR_CHRL_8;
        }
            
        if (stops == 2) {                                             /* (3) Setup # stops bits                        */
            dev_usart_mr |= AT91SAM9XE_USART_MR_NBSTOP_2;
        }
                                                                      /* (4) Setup UASRT baud rate                     */
        dev_mclk_freq  = BSP_PMC_MclkFreqGet();                            
        dev_usart_brgr = (CPU_INT16U)(dev_mclk_freq / baud / 16);
        
        switch (port_nbr) {                                           /* ----------- USART PORT SELECT --------------- */ 
            default:
            case MB_BSP_UART_00:
                 p_dev_pio         = (AT91SAM9XE_PIO   *)(AT91SAM9XE_PIOB_BASE_ADDR);
                 p_dev_usart       = (AT91SAM9XE_USART *)(AT91SAM9XE_USART0_BASE_ADDR);
                 dev_pio_val       = (CPU_INT32U        )(AT91SAM9XE_PIOB_PINS_USART0);
                 dev_per_id        = (CPU_INT08U        )(AT91SAM9XE_PER_ID_USART0);
                 dev_usart_handler = (CPU_INT32U        )(MB_CommRxTxISR_0_Handler);

#if (MB_BSP_CFG_UART_00_MODE == MB_BSP_UART_RS485_MODE)
                 usart_mr   |= AT91SAM9261X_USART_CHMODE_RS485;
#endif                 
                 break;
                 
            case MB_BSP_UART_01:
                 p_dev_pio         = (AT91SAM9XE_PIO   *)(AT91SAM9XE_PIOB_BASE_ADDR);
                 p_dev_usart       = (AT91SAM9XE_USART *)(AT91SAM9XE_USART1_BASE_ADDR);
                 dev_pio_val       = (CPU_INT32U         )(AT91SAM9XE_PIOB_PINS_USART1);
                 dev_per_id        = (CPU_INT08U         )(AT91SAM9XE_PER_ID_USART1);
                 dev_usart_handler = (CPU_INT32U         )(MB_CommRxTxISR_1_Handler);

#if (MB_BSP_CFG_UART_01_MODE == MB_BSP_UART_RS485_MODE)
                 usart_mr   |= AT91SAM9261X_USART_CHMODE_RS485;
#endif                                  
                 break;
                 
            case MB_BSP_UART_02:
                 p_dev_pio         = (AT91SAM9XE_PIO   *)(AT91SAM9XE_PIOB_BASE_ADDR);
                 p_dev_usart       = (AT91SAM9XE_USART *)(AT91SAM9XE_USART2_BASE_ADDR);
                 dev_pio_val       = (CPU_INT32U         )(AT91SAM9XE_PIOB_PINS_USART2);
                 dev_per_id        = (CPU_INT08U         )(AT91SAM9XE_PER_ID_USART2);
                 dev_usart_handler = (CPU_INT32U         )(MB_CommRxTxISR_2_Handler);

#if (MB_BSP_CFG_UART_02_MODE == MB_BSP_UART_RS485_MODE)
                 usart_mr   |= AT91SAM9261X_USART_CHMODE_RS485;
#endif                                  
                                  
            case MB_BSP_UART_03:
                 p_dev_pio         = (AT91SAM9XE_PIO   *)(AT91SAM9XE_PIOB_BASE_ADDR);
                 p_dev_usart       = (AT91SAM9XE_USART *)(AT91SAM9XE_USART3_BASE_ADDR);
                 dev_pio_val       = (CPU_INT32U        )(AT91SAM9XE_PIOB_PINS_USART3);
                 dev_per_id        = (CPU_INT08U        )(AT91SAM9XE_PER_ID_USART3);
                 dev_usart_handler = (CPU_INT32U        )(MB_CommRxTxISR_3_Handler);

#if (MB_BSP_CFG_UART_03_MODE == MB_BSP_UART_RS485_MODE)
                 usart_mr   |= AT91SAM9261X_USART_CHMODE_RS485;
#endif                                  

            case MB_BSP_UART_04:
                 p_dev_pio         = (AT91SAM9XE_PIO   *)(AT91SAM9XE_PIOA_BASE_ADDR);
                 p_dev_usart       = (AT91SAM9XE_USART *)(AT91SAM9XE_USART4_BASE_ADDR);
                 dev_pio_val       = (CPU_INT32U        )(AT91SAM9XE_PIOA_PINS_USART4);
                 dev_per_id        = (CPU_INT08U        )(AT91SAM9XE_PER_ID_USART2);
                 dev_usart_handler = (CPU_INT32U        )(MB_CommRxTxISR_4_Handler);

#if (MB_BSP_CFG_UART_04_MODE == MB_BSP_UART_RS485_MODE)
                 usart_mr   |= AT91SAM9261X_USART_CHMODE_RS485;
#endif                                  

            case MB_BSP_UART_DBG:
                 p_dev_pio         = (AT91SAM9XE_PIO   *)(AT91SAM9XE_PIOB_BASE_ADDR);
                 p_dev_usart       = (AT91SAM9XE_USART *)(AT91SAM9XE_DBGU_BASE_ADDR);
                 dev_pio_val       = (CPU_INT32U        )(AT91SAM9XE_PIOB_PINS_DBG);
                 dev_per_id        = (CPU_INT08U        )(AT91SAM9XE_PER_ID_SYS);
                 break;
        }

        p_dev_pmc            = (AT91SAM9XE_PMC *)(AT91SAM9XE_PMC_BASE_ADDR);        
        p_dev_pmc->PMC_PCER  = (CPU_INT32U       )(1 << dev_per_id);
        p_dev_pio->PIO_PDR   = dev_pio_val;

#if (port_nbr == MB_BSP_UART_04)        
        p_dev_pio->PIO_BSR   = dev_pio_val;
#else
        p_dev_pio->PIO_ASR   = dev_pio_val;
#endif        
        
        p_dev_usart->US_IDR  = AT91SAM9XE_USART_IDR_DIS_ALL;

        p_dev_usart->US_CR   = AT91SAM9XE_USART_CR_RSTSTA      /* Reset status bits, Tx and Rx                              */
                             | AT91SAM9XE_USART_CR_RSTRX
                             | AT91SAM9XE_USART_CR_RSTTX;

        p_dev_usart->US_CR   = AT91SAM9XE_USART_CR_RXEN        /* Enable receiver and tranmitter                            */
                             | AT91SAM9XE_USART_CR_TXEN;
        
        p_dev_usart->US_IER  = AT91SAM9XE_USART_CSR_RXRDY;     /* Enable Rx interrupts                                      */

        p_dev_usart->US_MR   = dev_usart_mr;                    /* Set the mode register                                     */
        p_dev_usart->US_BRGR = dev_usart_brgr;                  /* Set the baud rate generator register                      */
                                                                /* -------- INITIALIZE AIC FOR USARTx/DBGU UNIT ------------ */

        if (port_nbr != MB_BSP_UART_DBG) {
            p_dev_aic                      = (AT91SAM9XE_AIC *)(AT91SAM9XE_AIC_BASE_ADDR);
            p_dev_aic->AIC_SVR[dev_per_id] = dev_usart_handler;
            p_dev_aic->AIC_SMR[dev_per_id] = AT91SAM9XE_AIC_SMR_SRCTYPE_HIGH_LEVEL
                                           | AT91SAM9XE_AIC_SMR_PRIOR_LOWEST;
            p_dev_aic->AIC_ICCR            = (1 << dev_per_id);
            p_dev_aic->AIC_IECR            = (1 << dev_per_id);
        }
    }
}


/*
*********************************************************************************************************
*                                         MB_CommRxIntDis()
*
* Description : This function disables Rx interrupts.
*
* Argument(s) : pch        is a pointer to the Modbus channel
*
* Return(s)   : none.
*
* Caller(s)   : MB_CommExit()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_CommRxIntDis (MODBUS_CH  *pch)
{
    volatile  AT91SAM9XE_USART  *p_dev_usart;  
    
    switch (pch->PortNbr) {
        default:
        case MB_BSP_UART_00:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART0_BASE_ADDR);;
             break;

        case MB_BSP_UART_01:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART1_BASE_ADDR);;
             break;
             
        case MB_BSP_UART_02:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART2_BASE_ADDR);;
             break;
             
        case MB_BSP_UART_03:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART3_BASE_ADDR);;
             break;
                          
        case MB_BSP_UART_04:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART4_BASE_ADDR);;
             break;

        case MB_BSP_UART_DBG:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_DBGU_BASE_ADDR);;                          
             break;
    }
    
    p_dev_usart->US_IDR = AT91SAM9XE_USART_CSR_RXRDY;
}


/*
*********************************************************************************************************
*                                          MB_CommRxIntEn()
*
* Description : This function enables Rx interrupts.
*
* Argument(s) : pch        is a pointer to the Modbus channel
*
* Return(s)   : none.
*
* Caller(s)   : MB_TxByte()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_CommRxIntEn (MODBUS_CH  *pch)
{   
    volatile  AT91SAM9XE_USART  *p_dev_usart;  
    
    switch (pch->PortNbr) {
        default:
        case MB_BSP_UART_00:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART0_BASE_ADDR);;
             break;

        case MB_BSP_UART_01:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART1_BASE_ADDR);;
             break;
             
        case MB_BSP_UART_02:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART2_BASE_ADDR);;
             break;

        case MB_BSP_UART_03:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART3_BASE_ADDR);;
             break;

        case MB_BSP_UART_04:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART4_BASE_ADDR);;
             break;
             
        case MB_BSP_UART_DBG:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_DBGU_BASE_ADDR);;                          
             break;
    }

    p_dev_usart->US_IER = AT91SAM9XE_USART_CSR_RXRDY;
}


/*
*********************************************************************************************************
*                                       MB_CommRxTxISR_Handler()
*
* Description : This function is the ISR for either a received or transmitted character.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : This is a ISR
*
* Note(s)     : (1) The pseudo-code for this function should be:  
*
*               if (Rx Byte has been received) {
*                  c = get byte from serial port;
*                  Clear receive interrupt;
*                  pch->RxCtr++;                      Increment the number of bytes received
*                  MB_RxByte(pch, c);                 Pass character to Modbus to process
*              }
*
*              if (Byte has been transmitted) {
*                  pch->TxCtr++;                      Increment the number of bytes transmitted
*                  MB_TxByte(pch);                    Send next byte in response
*                  Clear transmit interrupt           Clear Transmit Interrupt flag
*              }
*********************************************************************************************************
*/

void  MB_CommRxTxISR_Handler (CPU_INT08U  port_nbr)
{
    volatile  AT91SAM9XE_USART  *p_dev_usart;  
    volatile  AT91SAM9XE_AIC    *p_dev_aic;  
              MODBUS_CH         *pch;
              CPU_INT08U         ch;
              CPU_INT08U         rx_data;

    
    p_dev_aic          = (AT91SAM9XE_AIC *)(AT91SAM9XE_AIC_BASE_ADDR);
    p_dev_aic->AIC_IVR = 0;    
    pch                = &MB_ChTbl[0];
    
    for (ch = 0; ch < MODBUS_CFG_MAX_CH; ch++) {        /* Find the channel assigned to this port       */
        if (pch->PortNbr == port_nbr) {
            ch = MODBUS_CFG_MAX_CH;
        } else {
            pch++;
        }
    }
    
    switch (port_nbr) {
        default:
        case MB_BSP_UART_00:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART0_BASE_ADDR);;
             break;

        case MB_BSP_UART_01:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART1_BASE_ADDR);;
             break;
             
        case MB_BSP_UART_02:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART2_BASE_ADDR);;
             break;

        case MB_BSP_UART_03:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART3_BASE_ADDR);;
             break;

        case MB_BSP_UART_04:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART4_BASE_ADDR);;
             break;
             
        case MB_BSP_UART_DBG:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_DBGU_BASE_ADDR);;                          
             break;
    }

    if ((DEF_BIT_IS_SET(p_dev_usart->US_IMR, AT91SAM9XE_USART_CSR_RXRDY)) && \
        (DEF_BIT_IS_SET(p_dev_usart->US_CSR, AT91SAM9XE_USART_CSR_RXRDY))) {
    
        pch->RxCtr++;                                           /* Increment the Rx counter                                  */
        rx_data = (CPU_INT08U)(p_dev_usart->US_RHR & 0x00FF);
        MB_RxByte(pch, rx_data);
    }
    
    if ((DEF_BIT_IS_SET(p_dev_usart->US_IMR, AT91SAM9XE_USART_CSR_TXRDY)) && \
        (DEF_BIT_IS_SET(p_dev_usart->US_CSR, AT91SAM9XE_USART_CSR_TXRDY))) {
    
        pch->TxCtr++;
        MB_TxByte(pch);                                         /* Send next byte                                            */
    }
    
    if ((DEF_BIT_IS_SET(p_dev_usart->US_IMR, AT91SAM9XE_USART_CSR_OVRE))) {   
        p_dev_usart->US_CR = AT91SAM9XE_USART_CR_RSTSTA;      /* if an overrun occurs, reset the status bits                */
    }
}


/*
*********************************************************************************************************
*                                UART #0 Rx/Tx Communication handler for Modbus
*********************************************************************************************************
*/

void  MB_CommRxTxISR_0_Handler (void)
{
    MB_CommRxTxISR_Handler(MB_BSP_UART_00);
}


/*
*********************************************************************************************************
*                                UART #1 Rx/Tx Communication handler for Modbus
*********************************************************************************************************
*/

void  MB_CommRxTxISR_1_Handler (void)
{
    MB_CommRxTxISR_Handler(MB_BSP_UART_01);
}

/*
*********************************************************************************************************
*                                UART #2 Rx/Tx Communication handler for Modbus
*********************************************************************************************************
*/

void  MB_CommRxTxISR_2_Handler (void)
{
    MB_CommRxTxISR_Handler(MB_BSP_UART_02);
}

/*
*********************************************************************************************************
*                                UART #3 Rx/Tx Communication handler for Modbus
*********************************************************************************************************
*/

void  MB_CommRxTxISR_3_Handler (void)
{
    MB_CommRxTxISR_Handler(MB_BSP_UART_03);
}

/*
*********************************************************************************************************
*                                UART #4 Rx/Tx Communication handler for Modbus
*********************************************************************************************************
*/

void  MB_CommRxTxISR_4_Handler (void)
{
    MB_CommRxTxISR_Handler(MB_BSP_UART_04);
}

/*
*********************************************************************************************************
*                                UART #3 Rx/Tx Communication handler for Modbus
*********************************************************************************************************
*/

void  MB_CommRxTxISR_5_Handler (void)
{
    MB_CommRxTxISR_Handler(MB_BSP_UART_DBG);
}


/*
*********************************************************************************************************
*                                             MB_CommTx1()
*
* Description : This function is called to obtain the next byte to send from the transmit buffer.  When
*               all bytes in the reply have been sent, transmit interrupts are disabled and the receiver
*               is enabled to accept the next Modbus request.
*
* Argument(s) : c     is the byte to send to the serial port
*
* Return(s)   : none.
*
* Caller(s)   : MB_TxByte()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_CommTx1 (MODBUS_CH  *pch,
                  CPU_INT08U  c)

{    
    volatile  AT91SAM9XE_USART  *p_dev_usart;  

    
    switch (pch->PortNbr) {
        default:
        case MB_BSP_UART_00:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART0_BASE_ADDR);;
             break;

        case MB_BSP_UART_01:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART1_BASE_ADDR);;
             break;
             
        case MB_BSP_UART_02:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART2_BASE_ADDR);;
             break;

        case MB_BSP_UART_03:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART3_BASE_ADDR);;
             break;
             
        case MB_BSP_UART_04:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART4_BASE_ADDR);;
             break;
             
        case MB_BSP_UART_DBG:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_DBGU_BASE_ADDR);;                          
             break;
    }

    p_dev_usart->US_THR = c;
}


/*
*********************************************************************************************************
*                                         MB_CommTxIntDis()
*
* Description : This function disables Tx interrupts.
*
* Argument(s) : pch        is a pointer to the Modbus channel
*
* Return(s)   : none.
*
* Caller(s)   : MB_CommExit()
*               MB_TxByte()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_CommTxIntDis (MODBUS_CH  *pch)
{
    volatile  AT91SAM9XE_USART  *p_dev_usart;  

    
    switch (pch->PortNbr) {
        default:
        case MB_BSP_UART_00:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART0_BASE_ADDR);;
             break;

        case MB_BSP_UART_01:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART1_BASE_ADDR);;
             break;
             
        case MB_BSP_UART_02:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART2_BASE_ADDR);;
             break;

        case MB_BSP_UART_03:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART3_BASE_ADDR);;
             break;
             
        case MB_BSP_UART_04:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART4_BASE_ADDR);;
             break;

             
        case MB_BSP_UART_DBG:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_DBGU_BASE_ADDR);;                          
             break;
    }

    p_dev_usart->US_IDR = AT91SAM9XE_USART_CSR_TXRDY;
}


/*
*********************************************************************************************************
*                                         MB_CommTxIntEn()
*
* Description : This function enables Tx interrupts.
*
* Argument(s) : pch        is a pointer to the Modbus channel
*
* Return(s)   : none.
*
* Caller(s)   : MB_Tx()
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  MB_CommTxIntEn (MODBUS_CH  *pch)
{
    volatile  AT91SAM9XE_USART  *p_dev_usart;  

    
    switch (pch->PortNbr) {
        default:
        case MB_BSP_UART_00:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART0_BASE_ADDR);;
             break;

        case MB_BSP_UART_01:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART1_BASE_ADDR);;
             break;
             
        case MB_BSP_UART_02:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART2_BASE_ADDR);;
             break;

        case MB_BSP_UART_03:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART3_BASE_ADDR);;
             break;
             
        case MB_BSP_UART_04:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_USART4_BASE_ADDR);;
             break;
             
             
        case MB_BSP_UART_DBG:
             p_dev_usart = (AT91SAM9XE_USART *)(AT91SAM9XE_DBGU_BASE_ADDR);;                          
             break;
    }

    p_dev_usart->US_IER = AT91SAM9XE_USART_CSR_TXRDY;
}


/*
*********************************************************************************************************
*                                           MB_RTU_TmrInit()
*
* Description : This function is called to initialize the RTU timeout timer.
*
* Argument(s) : freq          Is the frequency of the modbus RTU timer interrupt.
*
* Return(s)   : none.
*
* Caller(s)   : MB_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_RTU_EN == DEF_ENABLED)
void  MB_RTU_TmrInit (void)
{
              CPU_INT32U       dev_mclk_freq;
              CPU_INT08U       dev_id;
    volatile  AT91SAM9XE_TC   *p_dev_tc;
    volatile  AT91SAM9XE_PMC  *p_dev_pmc;
    volatile  AT91SAM9XE_AIC  *p_dev_aic;

        

    p_dev_aic            = (AT91SAM9XE_AIC *)(AT91SAM9XE_AIC_BASE_ADDR);
    p_dev_pmc            = (AT91SAM9XE_PMC *)(AT91SAM9XE_PMC_BASE_ADDR);        
    dev_mclk_freq        = BSP_PMC_MclkFreqGet();
    MB_Tmr_ReloadCnts    = (dev_mclk_freq / 2) / MB_RTU_Freq;

#if   (MS_BSP_CFG_TMR == MB_BSP_TMR_0)
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC0_BASE_ADDR);   
    dev_id   = AT91SAM9XE_PER_ID_TC0;

#elif (MS_BSP_CFG_TMR == MB_BSP_TMR_1)    
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC1_BASE_ADDR);
    dev_id   = AT91SAM9XE_PER_ID_TC1;    

#elif (MS_BSP_CFG_TMR == MB_BSP_TMR_2)    
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC2_BASE_ADDR);
    dev_id   = AT91SAM9XE_PER_ID_TC2;    
    
#elif (MS_BSP_CFG_TMR == MB_BSP_TMR_3)    
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC3_BASE_ADDR);
    dev_id   = AT91SAM9XE_PER_ID_TC3;    
    
    
#elif (MS_BSP_CFG_TMR == MB_BSP_TMR_4)    
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC4_BASE_ADDR);
    dev_id   = AT91SAM9XE_PER_ID_TC3;    
    
#else
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC5_BASE_ADDR);
    dev_id   = AT91SAM9XE_PER_ID_TC5;    
    
#endif
    p_dev_pmc->PMC_PCER = (1 << dev_id);  
 
    p_dev_tc->TC_CCR           = AT91SAM9XE_TC_CCR_CLKDIS;      /* TCx Clk disable                                           */
    p_dev_tc->TC_CMR           = AT91SAM9XE_TC_CMR_CPCTRG_EN;   /* TCx Compare trigger enable                                */
    p_dev_tc->TC_RC            = MB_Tmr_ReloadCnts;             /* TCx RC compare trigger value                              */

    
    p_dev_tc->TC_CCR           = AT91SAM9XE_TC_CCR_CLKEN;       /* TCx clk enable                                            */            
    p_dev_tc->TC_CCR           = AT91SAM9XE_TC_CCR_SWTRG;       /* TCx Software trigger                                      */ 
    p_dev_tc->TC_IER           = AT91SAM9XE_TC_IER_CPCS;        /* TCx RC compare interrupt enable                           */ 
    
    
                                                                /* AIC configuration                                         */
    p_dev_aic->AIC_SVR[dev_id] = (CPU_INT32U)MB_RTU_TmrISR_Handler;  
    p_dev_aic->AIC_SMR[dev_id] = AT91SAM9XE_AIC_SMR_SRCTYPE_HIGH_LEVEL 
                               | AT91SAM9XE_AIC_SMR_PRIOR_LOWEST;
    p_dev_aic->AIC_ICCR        = (CPU_INT32U)(1 << dev_id);
    p_dev_aic->AIC_IECR        = (CPU_INT32U)(1 << dev_id);

    MB_RTU_TmrResetAll();                                       /* Reset all the RTU timers.                                 */
}
#endif


/*
*********************************************************************************************************
*                                           MB_RTU_TmrExit()
*
* Description : This function is called to disable the RTU timeout timer.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : MB_Exit()
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_RTU_EN == DEF_ENABLED)
void  MB_RTU_TmrExit (void)
{
    volatile  AT91SAM9XE_TC   *p_dev_tc;    
   
#if   (MS_BSP_CFG_TMR == MB_BSP_TMR_0)
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC0_BASE_ADDR);    

#elif (MS_BSP_CFG_TMR == MB_BSP_TMR_1)    
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC1_BASE_ADDR);

#elif (MS_BSP_CFG_TMR == MB_BSP_TMR_2)    
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC2_BASE_ADDR);
    
#elif (MS_BSP_CFG_TMR == MB_BSP_TMR_3)    
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC3_BASE_ADDR);
    
#elif (MS_BSP_CFG_TMR == MB_BSP_TMR_4)    
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC4_BASE_ADDR);
    
#else
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC5_BASE_ADDR);
#endif
    
    p_dev_tc->TC_CCR = AT91SAM9XE_TC_CCR_CLKDIS;    
}
#endif


/*
*********************************************************************************************************
*                                       MB_RTU_TmrISR_Handler()
*
* Description : This function handles the case when the RTU timeout timer expires.
*
* Arguments   : none.
*
* Returns     : none.
*
* Caller(s)   : This is a ISR.
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if (MODBUS_CFG_RTU_EN == DEF_ENABLED)
void  MB_RTU_TmrISR_Handler (void)
{
    volatile  AT91SAM9XE_TC   *p_dev_tc;
    volatile  AT91SAM9XE_AIC  *p_dev_aic;
              CPU_INT08U       dev_id;
            
    p_dev_aic            = (AT91SAM9XE_AIC *)(AT91SAM9XE_AIC_BASE_ADDR);
    
#if   (MS_BSP_CFG_TMR == MB_BSP_TMR_0)
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC0_BASE_ADDR);   
    dev_id   = AT91SAM9XE_PER_ID_TC0;

#elif (MS_BSP_CFG_TMR == MB_BSP_TMR_1)    
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC1_BASE_ADDR);
    dev_id   = AT91SAM9XE_PER_ID_TC1;    

#elif (MS_BSP_CFG_TMR == MB_BSP_TMR_2)    
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC2_BASE_ADDR);
    dev_id   = AT91SAM9XE_PER_ID_TC2;    
    
#elif (MS_BSP_CFG_TMR == MB_BSP_TMR_3)    
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC3_BASE_ADDR);
    dev_id   = AT91SAM9XE_PER_ID_TC3;    
    
    
#elif (MS_BSP_CFG_TMR == MB_BSP_TMR_4)    
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC4_BASE_ADDR);
    dev_id   = AT91SAM9XE_PER_ID_TC3;    
    
#else
    p_dev_tc = (AT91SAM9XE_TC *)(AT91SAM9XE_TC5_BASE_ADDR);
    dev_id   = AT91SAM9XE_PER_ID_TC5;    
    
#endif

    if (DEF_BIT_IS_SET(p_dev_tc->TC_SR , AT91SAM9XE_TC_SR_CPCS)) {
        p_dev_tc->TC_RC     = MB_Tmr_ReloadCnts;         /* Load the match value to the RC register                              */
        p_dev_aic->AIC_ICCR = (1 << dev_id);
    }

    MB_RTU_TmrCtr++;                                    /* Indicate that we had activities on this interrupt.                    */
    MB_RTU_TmrUpdate();                                 /* Check for RTU timers that have expired                                */
}

#endif
