#include <MKL25Z4.h>
#define LED_A   (3)   												// set the LED segment1 A pin number 
#define LED_B   (4)   												// set the LED segment1 B pin number 
#define LED_C   (5)   												// set the LED segment1 C pin number 
#define LED_D   (6)   												// set the LED segment1 D pin number 
#define LED_E   (10)   												// set the LED segment1 E pin number 
#define LED_F   (0)   												// set the LED segment1 F pin number 
#define LED_G   (7)   												// set the LED segment1 G pin number 

#define LED_A_1   (30)   												// set the LED segment2 A pin number 
#define LED_B_1   (29)   												// set the LED segment2 B pin number 
#define LED_C_1   (23)   												// set the LED segment2 C pin number 
#define LED_D_1   (22)   												// set the LED segment2 D pin number 
#define LED_E_1   (21)   												// set the LED segment2 E pin number 
#define LED_F_1   (5)   												// set the LED segment2 F pin number 
#define LED_G_1   (4)   												// set the LED segment2 G pin number 

#define ADC_POS (20)


#define Mask(x) (1U<<(x)) 										// define the mask function

// LED and Switches initialization 
void Leds_init(){
  SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTE_MASK;          //Initialize the clock for port A & C
  //LED's Segment1
	PORTC->PCR[LED_A] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_A
	PORTC->PCR[LED_A] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_A to GPIO mode
	PORTC->PCR[LED_B] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_B
	PORTC->PCR[LED_B] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_B to GPIO mode
	PORTC->PCR[LED_C] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_C
	PORTC->PCR[LED_C] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_C to GPIO mode
	PORTC->PCR[LED_D] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_D
	PORTC->PCR[LED_D] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_D to GPIO mode
	PORTC->PCR[LED_E] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_E
	PORTC->PCR[LED_E] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_E to GPIO mode
	PORTC->PCR[LED_F] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_F
	PORTC->PCR[LED_F] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_F to GPIO mode
	PORTC->PCR[LED_G] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_G
	PORTC->PCR[LED_G] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_G to GPIO mode
	
  //LED's Segment2
	PORTE->PCR[LED_A_1] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_A
	PORTE->PCR[LED_A_1] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_A to GPIO mode
	PORTE->PCR[LED_B_1] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_B
	PORTE->PCR[LED_B_1] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_B to GPIO mode
	PORTE->PCR[LED_C_1] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_C
	PORTE->PCR[LED_C_1] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_C to GPIO mode
	PORTE->PCR[LED_D_1] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_D
	PORTE->PCR[LED_D_1] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_D to GPIO mode
	PORTE->PCR[LED_E_1] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_E
	PORTE->PCR[LED_E_1] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_E to GPIO mode
	PORTE->PCR[LED_F_1] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_F
	PORTE->PCR[LED_F_1] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_F to GPIO mode
	PORTE->PCR[LED_G_1] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for LED_G
	PORTE->PCR[LED_G_1] |= PORT_PCR_MUX(1);        // Set the MUX field for LED_G to GPIO mode
	
	//gpio config
	PTC->PDDR |= Mask(LED_A)| Mask(LED_B)| Mask(LED_C)| Mask(LED_D)| Mask(LED_E)| Mask(LED_F)| Mask(LED_G); //Set LED pins as outputs
	// Set the initial state of LED's to off
	PTC->PCOR |= Mask(LED_A)| Mask(LED_B)| Mask(LED_C)| Mask(LED_D)| Mask(LED_E)| Mask(LED_F)| Mask(LED_G); //Set the LED's to off state intially
	
	//gpio config
	PTE->PDDR |= Mask(LED_A_1)| Mask(LED_B_1)| Mask(LED_C_1)| Mask(LED_D_1)| Mask(LED_E_1)| Mask(LED_F_1)| Mask(LED_G_1); //Set LED pins as outputs
  // Set the initial state of LED's to off
	PTE->PCOR |= Mask(LED_A_1)| Mask(LED_B_1)| Mask(LED_C_1)| Mask(LED_D_1)| Mask(LED_E_1)| Mask(LED_F_1)| Mask(LED_G_1); //Set the LED's to off state intially
}

// Function to control the sate of LED's on segment1
void LED_control_seg1(int A, int B, int C, int D, int E, int F, int G){

  if(A==1)
		PTC->PSOR = Mask(LED_A);	                     // Turn ON LED
	else
		PTC->PCOR = Mask(LED_A);                       // Turn OFF LED	

  if(B==1)
		PTC->PSOR = Mask(LED_B);	                     // Turn ON LED
	else 
		PTC->PCOR = Mask(LED_B);                       // Turn OFF LED
	
  if(C==1)
		PTC->PSOR = Mask(LED_C);	                     // Turn ON LED
	else
		PTC->PCOR = Mask(LED_C);                       // Turn OFF LED

  if(D==1)
		PTC->PSOR = Mask(LED_D);	                     // Turn ON LED
	else
		PTC->PCOR = Mask(LED_D);                       // Turn OFF LED	

  if(E==1)
		PTC->PSOR = Mask(LED_E);	                     // Turn ON LED
	else 
		PTC->PCOR = Mask(LED_E);                       // Turn OFF LED
	
  if(F==1)
		PTC->PSOR = Mask(LED_F);	                     // Turn ON LED
	else
		PTC->PCOR = Mask(LED_F);                       // Turn OFF LED
	
	 if(G==1)
		PTC->PSOR = Mask(LED_G);	                     // Turn ON LED
	else
		PTC->PCOR = Mask(LED_G);                       // Turn OFF LED
}

// Function to control the sate of LED's on segment1
void LED_control_seg2(int A_1, int B_1, int C_1, int D_1, int E_1, int F_1, int G_1){

  if(A_1==1)
		PTE->PSOR = Mask(LED_A_1);	                     // Turn ON LED
	else
		PTE->PCOR = Mask(LED_A_1);                       // Turn OFF LED	

  if(B_1==1)
		PTE->PSOR = Mask(LED_B_1);	                     // Turn ON LED
	else 
		PTE->PCOR = Mask(LED_B_1);                       // Turn OFF LED
	
  if(C_1==1)
		PTE->PSOR = Mask(LED_C_1);	                     // Turn ON LED
	else
		PTE->PCOR = Mask(LED_C_1);                       // Turn OFF LED

  if(D_1==1)
		PTE->PSOR = Mask(LED_D_1);	                     // Turn ON LED
	else
		PTE->PCOR = Mask(LED_D_1);                       // Turn OFF LED	

  if(E_1==1)
		PTE->PSOR = Mask(LED_E_1);	                     // Turn ON LED
	else 
		PTE->PCOR = Mask(LED_E_1);                       // Turn OFF LED
	
  if(F_1==1)
		PTE->PSOR = Mask(LED_F_1);	                     // Turn ON LED
	else
		PTE->PCOR = Mask(LED_F_1);                       // Turn OFF LED
	
	 if(G_1==1)
		PTE->PSOR = Mask(LED_G_1);	                     // Turn ON LED
	else
		PTE->PCOR = Mask(LED_G_1);                       // Turn OFF LED
}

// Time delay function 
void Delay(volatile unsigned int time){
	while(time --){;
	}
}

//This function checks the 7-segment LED's functionality after the mcu powered ON. 
void led_check(){
  LED_control_seg1(1, 0, 0, 0, 0, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control_seg1(0, 1, 0, 0, 0, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control_seg1(0, 0, 1, 0, 0, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control_seg1(0, 0, 0, 1, 0, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control_seg1(0, 0, 0, 0, 1, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control_seg1(0, 0, 0, 0, 0, 1, 0);
	Delay(200000);                                // Add time delay
	LED_control_seg1(0, 0, 0, 0, 0, 0, 1); 
	Delay(200000);                                // Add time delay
	LED_control_seg1(1, 1, 1, 1, 1, 1, 1); 
	Delay(2000000);                                // Add time delay
	LED_control_seg1(0, 0, 0, 0, 0, 0, 0);
	Delay(2000000);                                // Add time delay
	LED_control_seg1(1, 1, 1, 1, 1, 1, 1); 
	Delay(2000000);                                // Add time delay
	
	LED_control_seg2(1, 0, 0, 0, 0, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control_seg2(0, 1, 0, 0, 0, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control_seg2(0, 0, 1, 0, 0, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control_seg2(0, 0, 0, 1, 0, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control_seg2(0, 0, 0, 0, 1, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control_seg2(0, 0, 0, 0, 0, 1, 0);
	Delay(200000);                                // Add time delay
	LED_control_seg2(0, 0, 0, 0, 0, 0, 1); 
	Delay(200000);                                // Add time delay
	LED_control_seg2(1, 1, 1, 1, 1, 1, 1); 
	Delay(2000000);                                // Add time delay
	LED_control_seg2(0, 0, 0, 0, 0, 0, 0);
	Delay(2000000);                                // Add time delay
	LED_control_seg2(1, 1, 1, 1, 1, 1, 1); 
	Delay(2000000);                                // Add time delay
}

// This functions displays the values on the 7-segment display 1 based of the input values
void LED_input_display_seg1(int value){
	if(value==0)
	LED_control_seg1(1, 1, 1, 1, 1, 1, 0);	
	
  if(value==1)
	LED_control_seg1(0, 1, 1, 0, 0, 0, 0);	
	
	if(value==2)
	LED_control_seg1(1, 1, 0, 1, 1, 0, 1);	
	
  if(value==3)
	LED_control_seg1(1, 1, 1, 1, 0, 0, 1);	
	
	if(value==4)
	LED_control_seg1(0, 1, 1, 0, 0, 1, 1);	
	
  if(value==5)
	LED_control_seg1(1, 0, 1, 1, 0, 1, 1);	
	
	if(value==6)
	LED_control_seg1(1, 0, 1, 1, 1, 1, 1);	
	
  if(value==7)
	LED_control_seg1(1, 1, 1, 0, 0, 0, 0);	
	
	if(value==8)
	LED_control_seg1(1, 1, 1, 1, 1, 1, 1);	
	
  if(value==9)
	LED_control_seg1(1, 1, 1, 1, 0, 1, 1);	
	
	 if(value==10)
	LED_control_seg1(0, 0, 0, 0, 0, 0, 0);	
}

// This functions displays the values on the 7-segment display 2 based of the input values
void LED_input_display_seg2(int value){
	if(value==0)
	LED_control_seg2(1, 1, 1, 1, 1, 1, 0);	
	
  if(value==1)
	LED_control_seg2(0, 1, 1, 0, 0, 0, 0);	
	
	if(value==2)
	LED_control_seg2(1, 1, 0, 1, 1, 0, 1);	
	
  if(value==3)
	LED_control_seg2(1, 1, 1, 1, 0, 0, 1);	
	
	if(value==4)
	LED_control_seg2(0, 1, 1, 0, 0, 1, 1);	
	
  if(value==5)
	LED_control_seg2(1, 0, 1, 1, 0, 1, 1);	
	
	if(value==6)
	LED_control_seg2(1, 0, 1, 1, 1, 1, 1);	
	
  if(value==7)
	LED_control_seg2(1, 1, 1, 0, 0, 0, 0);	
	
	if(value==8)
	LED_control_seg2(1, 1, 1, 1, 1, 1, 1);	
	
  if(value==9)
	LED_control_seg2(1, 1, 1, 1, 0, 1, 1);	
	
	 if(value==10)
	LED_control_seg2(0, 0, 0, 0, 0, 0, 0);	
}

void Init_ADC(void) {
	
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK; 
	SIM->SCGC5 |= SIM_SCGC5_PORTE_MASK; 
	
	// Select analog for pin
	PORTE->PCR[ADC_POS] &= ~PORT_PCR_MUX_MASK;	
	PORTE->PCR[ADC_POS] |= PORT_PCR_MUX(0);	
	
	// Low power configuration, long sample time, 16 bit single-ended conversion, bus clock input
	ADC0->CFG1 = ADC_CFG1_ADLPC_MASK | ADC_CFG1_ADLSMP_MASK | ADC_CFG1_MODE(3) | ADC_CFG1_ADICLK(0);
	// Software trigger, compare function disabled, DMA disabled, voltage references VREFH and VREFL
	ADC0->SC2 = ADC_SC2_REFSEL(0);
}

float Measure_Temperature(void){
	float n;
	int temp;
	
	ADC0->SC1[0] = 0x00; // start conversion on channel 0
	
	// Wait for conversion to finish
	while (!(ADC0->SC1[0] & ADC_SC1_COCO_MASK));
	
	// Read result, convert to floating-point
	n = (float) ADC0->R[0];
	
	// Calculate temperature (Celsius) using polynomial equation
	// Assumes ADC is in 16-bit mode, has VRef = 3.3 V

	temp = -36.9861 + n*(0.0155762 + n*(-1.43216E-06 + n*(7.18641E-11 
		+ n*(-1.84630E-15 + n*(2.32656E-20 + n*(-1.13090E-25))))));
	return temp;
}

//Main routine
int main(void){
	int first_digit;                             // first digit of the measured temperature
	int second_digit;                            // second digit of the measured temperature  
	int t=0;                                     // initlize temperature to 0
	int cel=0;                                    // initlize the celicus to 0
	int old_value=0;
	Leds_init(); 											              // initialize  LED's 
 //	led_check();                                 // Test the LED's functionality
	Delay(200000);
	Init_ADC();                                    // initlize the ADC   
	
		while(1){		
	 t = Measure_Temperature();                     // read the temperature
	 cel = (5.0/9) * (t - 32);                        
	 if(cel!=old_value){
	 old_value=cel;		
	 first_digit=cel/10;                           // extract the first digit of temperature value            
	 second_digit=cel % 10;				                 // extract the second digit of temperature value
	 LED_input_display_seg1(first_digit);          // display first digit on segment 1
   LED_input_display_seg2(second_digit);		     // display second digit on segment 2
	 }
  }
}
