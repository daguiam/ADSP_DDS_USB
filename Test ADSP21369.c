

/*****************************************************************************
 * Test ADSP21369.c
 *****************************************************************************/
#define LED6 DAI_PB16_I
#include ".\h\general.h" 

/////////////////////////////////////////////////
// 			GLOBALS
/////////////////////////////////////////////////

int gStatus,gStatus2;
int gFreq;
int gChangeFreq;
char gPhase;

unsigned char gDDS_word[5];



void Config_SRU_LEDS(void)
{
//Setting the SRU and route so that Flag pins connects to DPI pin buffers.
//Use Flags 4 to 15 only. Flags 0 to 3 are reserved
	SRU(FLAG4_O,DPI_PB06_I);	//DPI => We can use flags.
	SRU(FLAG5_O,DPI_PB07_I);	//DPI => We can use flags.
	SRU(FLAG6_O,DPI_PB08_I);	//DPI => We can use flags.
	SRU(FLAG7_O,DPI_PB13_I);	//DPI => We can use flags.
	SRU(FLAG8_O,DPI_PB14_I);	//DPI => We can use flags.
	SRU(LOW,DAI_PB15_I);		//DAI => We can't use flags. Value has to be set low or high.
	SRU(LOW,DAI_PB16_I);		//DAI => We can't use flags. Value has to be set low or high.

//Enabling the Buffer using the following sequence: High -> Output, Low -> Input
	SRU(HIGH,DPI_PBEN06_I);
	SRU(HIGH,DPI_PBEN07_I);
	SRU(HIGH,DPI_PBEN08_I);
	SRU(HIGH,DPI_PBEN13_I);
	SRU(HIGH,DPI_PBEN14_I);
	SRU(HIGH,PBEN15_I);		//default format to enable the buffer using DAI
	SRU(HIGH,PBEN16_I);
}

void Setup_leds(void)
{
	Config_SRU_LEDS();

    sysreg_bit_set(sysreg_FLAGS, (FLG3O|FLG4O|FLG5O|FLG6O|FLG7O|FLG8O) ); 	//Setting flag pins as outputs
	sysreg_bit_clr(sysreg_FLAGS, (FLG3|FLG4|FLG5|FLG6|FLG7|FLG8) );			//Clearing flag pins
}


#define LED6_off SRU(LOW,DAI_PB16_I)
#define LED6_on SRU(HIGH,DAI_PB16_I)
#define LED5_off SRU(LOW,DAI_PB15_I)
#define LED5_on SRU(HIGH,DAI_PB15_I)


//////////////////////////////////////////////////////////////////////////////
// void IRQ0_routine(int sig_int)
//
// PURPOSE:		ISR for pushbutton 2
//
//////////////////////////////////////////////////////////////////////////////
void IRQ0_routine(int sig_int)
{
	if(gStatus %2== 1){
	//	gStatus = 0;
		LED6_off;
	//	DDS_powerdown;
	}else{
	//	gStatus = 1;
		LED6_on;
	//	DDS_powerup;
	}
	//DDS_init();
	// Double Reset and INIT - Makes no sense but works...
	//DDS_init();
	DDS_current_scale(gStatus%4);
	gStatus++;
	
	
	DDS3_frequency = 0xa0aF0aaF;
	DDS3_phase = 0x1;
	DDS_set_DMA(DDS_ch3);
	DDS_set_SRU(DDS_ch3);
	DDS_start_SPORT();

}

//////////////////////////////////////////////////////////////////////////////
// void IRQ1_routine(int sig_int)
//
// PURPOSE:		ISR for pushbutton 1
//
//////////////////////////////////////////////////////////////////////////////
void IRQ1_routine(int sig_int)
{
	int freq;
	if(gStatus2 %2== 1){
	//	gStatus = 0;
		LED5_off;
	}else{
	//	gStatus = 1;
		LED5_on;
	}

	gStatus2++;
	gChangeFreq = 1;
	switch(gStatus2%4){
		case 0:
			gFreq = DDS_10kHz;
			break;
		case 1:
			gFreq = DDS_100kHz;
			break;
		case 2:
			gFreq = DDS_1MHz;
			break;
		case 3:
			gFreq = DDS_10MHz;
			break;
		default:
			break;
	}
		//gFreq = DDS_10MHz;
	//for(k=0;k<100;k++);
	//DDS_update_frequency();
	//*pTXSP3A = 0x80000001;

/*	    // Configure the DMA
	*pSPCTL1 = 0;
	while(*pCSP1A!=0);
    *pIISP1A =  (unsigned int)	gDDS_word;  // Internal DMA memory address
   // *pIMSP1A = sizeof(gDDS_word[0]);			// Address modifier
    *pCSP1A  = 5; 			// word count 4 bytes 
//    *pCPSP3B = 0;
    *pSPCTL1 = (SPTRAN | FSR | LAFS | IFS | LSBF | ICLK | CKRE | SLEN8 | SPEN_A | SDEN_A);
*/


}

//////////////////////////////////////////////////////////////////////////////
// void SP0_Interrupt(int sig_int)
//
// PURPOSE:		ISR For sp0 done interrupt!
//
//////////////////////////////////////////////////////////////////////////////
void SP1_Interrupt(int sig_int)
{
	int i;
	LED6_on;
	//for(i=0;i<10000000;i++);
	LED6_off;

}


//////////////////////////////////////////////////////////////////////////////
// void Setup_Ints(void)
//
// PURPOSE:		Configure the system to accept the push buttons as inputs
//
//////////////////////////////////////////////////////////////////////////////
void Setup_Ints(void)
{
	//Config_SRU_INTS();


    (*pDAI_IRPTL_PRI) = (SRU_EXTMISCA1_INT  | SRU_EXTMISCA2_INT);    //unmask individual interrupts
    (*pDAI_IRPTL_RE) = (SRU_EXTMISCA1_INT  | SRU_EXTMISCA2_INT);    //make sure interrupts latch on the rising edge

	//Set up interrupt priorities
    sysreg_bit_set(sysreg_IMASK, DAIHI); //make DAI interrupts high priority

    (*pSYSCTL) |= (IRQ0EN|IRQ1EN);

    sysreg_bit_set(sysreg_MODE2, (IRQ0E|IRQ1E) );
    sysreg_bit_clr(sysreg_IRPTL, (IRQ1I|IRQ0I) );
    sysreg_bit_set(sysreg_IMASK, (IRQ1I|IRQ0I) ); //enable IRQ interrupts
    sysreg_bit_set(sysreg_MODE1, IRPTEN ); 		  //enable global interrupts

  //  interrupt(SIG_DAIH,DAIroutine);
    interrupt (SIG_SP1,IRQ_DDS_SP1);

    interrupt(SIG_IRQ0,IRQ0_routine);
    interrupt(SIG_IRQ1,IRQ1_routine);
}





void InitSPORT(void)
{
	
	#define DAC4
	
/*    //Proceed from Block A to Block C
    TCB_Block_A[0] = (int) TCB_Block_C + 3 - OFFSET + PCI ;
    TCB_Block_A[3] = (unsigned int) Block_A - OFFSET ;

    //Proceed from Block B to Block A
    TCB_Block_B[0] = (int) TCB_Block_A + 3 - OFFSET + PCI ;
    TCB_Block_B[3] = (unsigned int) Block_B - OFFSET ;

    //Proceed from Block C to Block B
    TCB_Block_C[0] = (int) TCB_Block_B + 3 - OFFSET + PCI ;
    TCB_Block_C[3] = (unsigned int) Block_C - OFFSET ;
*/
    //Clear the Mutlichannel control registers
    *pSPMCTL0 = 0;
    *pSPMCTL1 = 0;
    *pSPMCTL3 = 0;
    *pSPCTL0 = 0 ;
    *pSPCTL1 = 0 ;
    *pSPCTL3 = 0 ;
	*pTXSP3A=0;
    //============================================================
    //
    // Configure SPORT 0 for input from ADC
    //
    //------------------------------------------------------------


//    *pSPCTL0 = (OPMODE | SLEN24 | SPEN_A | SCHEN_A | SDEN_A);

    // Enabling Chaining
    // Block A will be filled first
//    *pCPSP0A = (unsigned int) TCB_Block_A - OFFSET + 3 ;

    //============================================================
    //
    // Configure SPORTs 1 & 2 for output to DACs 1-4
    //
    //------------------------------------------------------------

    // Configure the DMA
    *pIISP1A =  (unsigned int)	gDDS_word;  // Internal DMA memory address
    *pIMSP1A = sizeof(gDDS_word[0]);			// Address modifier
    *pCSP1A  = 5; 			// word count 4 bytes 
//    *pCPSP3B = 0;

    // Clock divisor;   
    *pDIV1 = 0x0000008;
    

        // #!
/*    gDDS_word[0] = 0xDA;
    gDDS_word[1] = 0x73;
    gDDS_word[2] = 0x0D;
    gDDS_word[3] = 0x00;
    gDDS_word[4] = 0x00;
*/
    gDDS_word[0] = 0xFF;
    gDDS_word[1] = 0x00;
    gDDS_word[2] = 0xFF;
    gDDS_word[3] = 0x00;
    gDDS_word[4] = 0xFF;

    
    
    

    // Configure and enable SPORT 1 and DMA
    
    //*pSPCTL1 = (SPTRAN  | SLEN7 | SPEN_A );/* | SDEN_A | LSBF | CKRE ) ;*/
    *pSPCTL1 = (SPTRAN | FSR | LAFS | IFS | LSBF | ICLK | CKRE | SLEN8 | SPEN_A | SDEN_A);
    
    // Configure the DMA
    
 /*
    #ifdef DDS1
    *pSPCTL1 = (SPTRAN | OPMODE | SLEN24 | SPEN_A | SCHEN_A | SDEN_A) ;
    // write to DAC1
    *pCPSP1A = (unsigned int) TCB_Block_C - OFFSET + 3 ;
    #endif

    #ifdef DDS2
    *pSPCTL1 |= (SPTRAN | OPMODE | SLEN24 | SPEN_B | SCHEN_B | SDEN_B) ;
    // write to DAC2
    *pCPSP1B = (unsigned int) TCB_Block_C - OFFSET + 3 ;
    #endif

    #ifdef DDS3
    *pSPCTL2 = (SPTRAN | OPMODE | SLEN24 | SPEN_A | SCHEN_A | SDEN_A) ;
    // write to DAC3
    *pCPSP2A = (unsigned int) TCB_Block_C - OFFSET + 3 ;
    #endif
-*/

}


void InitSRU(void){
/*
		W_CLK_1 - DAI_PB10
		W_CLK_2 - DAI_PB08
		W_CLK_3 - DAI_PB06
		DATA 	- DAI_PB07
		FQ_UD	- DAI_PB09
		RESET	- DAI_PB05

*/
    //  Clock out on pin 10 WCLK1
    SRU(SPORT1_CLK_O, DAI_PB10_I);
    //  Data in on pin 5
    SRU(SPORT1_DA_O, DAI_PB07_I);
    SRU(SPORT1_FS_O, DAI_PB08_I);
    SRU(SPORT1_FS_O, MISCA4_I);
    
    // Inverts MISC buffer 4 output
    // SRU (HIGH, INV_MISCA4_I);
    // MISC buffer 4 implements a gated clock that depends on frame sync
    SRU(MISCA4_O, PBEN10_I);
    
    SRU(SPORT1_DA_PBEN_O, PBEN07_I);
   // SRU(HIGH, PBEN10_I);
    SRU(SPORT1_FS_PBEN_O, PBEN08_I);
    //	SRU(SPORT3_CLK_O, SPORT3_CLK_I);


//------------------------------------------------------------------------
//  Tie the pin buffer enable inputs HIGH to make DAI pins 9-14 outputs.
   // SRU(HIGH,PBEN07_I);
  //  SRU(HIGH,PBEN10_I);
  //  SRU(HIGH,SPORT1_CLK_PBEN);
 //   SRU(HIGH,SPORT1_DA_PBEN);
    
  //  SRU(HIGH,DAI_PB07_I);
  //  SRU(LOW,DAI_PB10_I);


}






void main( void )
{
	/* Begin adding your custom code here */
	int i,k = 0,nr=0;
	
	unsigned char w4 = 0x8E;// 0x8E;
	unsigned char w3 = 0xE3;
	unsigned char w2 = 0x38;//0x38;
	unsigned char w1 = 0x0E>>0;//0x0E;
	unsigned char w0 = 0x09; // phase, power down, REF Multiplier
/*	union dds_freq freq;
	freq.freq_byte[0]=0x0E;
	freq.freq_byte[1]=0x38;
	freq.freq_byte[2]=0xE3;
	freq.freq_byte[3]=0x8E;
*/	
	gStatus = 0;
	gChangeFreq =0;
	gPhase = 0;
	
	//initPLL_SDRAM();
	InitPLL_SDRAM();
	
	
	Setup_leds();
	
	//SRU(HIGH,PIN_SCALE_b0);	
	//SRU(HIGH,PIN_SCALE_b1);	
	//InitSRU();

	//InitSPORT();
	
	
	//DDS_init_io();

	//DDS_current_scale(DDS_CURRENT_100);
	
	InitDDS_IO();
		
	Setup_Ints();
	
	DDS_init();
	// Double Reset and INIT - Makes no sense but works...
	DDS_init();
	

/*		SRU(HIGH,PIN_FQ_UD);	
		// tWH W_CLOCK High time
		for(k=0;k<100;k++);
		
		
		SRU(LOW,PIN_FQ_UD);	
		for(k=0;k<100;k++);
*/
	
	while(1){
		if(gChangeFreq ==1){
	/*     	*/ 
			DDS1_frequency = gFreq;// 0x80FFFF01;//DDS_10kHz;
			DDS1_phase = DDS_PHASE_0;
			DDS_set_DMA(DDS_ch1);
			DDS_set_SRU(DDS_ch1);
			DDS_start_SPORT();
	
			DDS2_frequency = gFreq;//DDS_100kHz;
			DDS2_phase = DDS_PHASE_0;
			DDS_set_DMA(DDS_ch2);
			DDS_set_SRU(DDS_ch2);
			DDS_start_SPORT();
	
			DDS3_frequency = gFreq;
			DDS3_phase = DDS_PHASE_180;
			DDS_set_DMA(DDS_ch3);
			DDS_set_SRU(DDS_ch3);
			DDS_start_SPORT();
		
			DDS_update_frequency();			
			
			
			
			gChangeFreq = 0;
//			gPhase++;
//			gPhase = gPhase&0x1f;
		}
	//			DDS_update_frequency();
		for(i=0;i<1000000;i++);
		LED6_off;
		for(i=0;i<10000000;i++);
		LED6_on;
		
	//while ((*pSPCTL3 & DXS_A)!=0);  //wait DAC:
     	
    	//*pTXSP1B = 0;
		//*pTXSP1A=0xaa;
		
		//gDDS_word[0]=nr++;
		//InitSRU();

	}
//	return 0;
}
