#include <MKL25Z4.h>
#define LED_A   (3)   												// set the LED segment A pin number 
#define LED_B   (4)   												// set the LED segment B pin number 
#define LED_C   (5)   												// set the LED segment C pin number 
#define LED_D   (6)   												// set the LED segment D pin number 
#define LED_E   (10)   												// set the LED segment E pin number 
#define LED_F   (0)   												// set the LED segment F pin number 
#define LED_G   (7)   												// set the LED segment G pin number 
#define SW1    (12)   												// set the SW1 switch pin number
#define SW2    (13)   												// set the SW2 switch pin number
#define SW3    (16)   												// set the SW3 switch pin number
#define SW4    (17)   												// set the SW4 switch pin number

#define Mask(x) (1U<<(x)) 										// define the mask function

int8_t input_value=0;                         // Stores the button input, set the initial value to '0'
int32_t counter=0;                            // counter to segment display function 

// LED and Switches initialization 
void Leds_switches_init(){
  SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTC_MASK;          //Initialize the clock for port A & C
  //LED's
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
	
	//Switches
	PORTA->PCR[SW1] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for SW1
	PORTA->PCR[SW1] |= PORT_PCR_MUX(1);        // Set the MUX field for SW1 to GPIO mode
	PORTA->PCR[SW2] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for SW2
	PORTA->PCR[SW2] |= PORT_PCR_MUX(1);        // Set the MUX field for SW2 to GPIO mode
	PORTA->PCR[SW3] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for SW3
	PORTA->PCR[SW3] |= PORT_PCR_MUX(1);        // Set the MUX field for SW3 to GPIO mode
	PORTA->PCR[SW4] &= ~PORT_PCR_MUX_MASK;     // Clear the MUX field for SW4
	PORTA->PCR[SW4] |= PORT_PCR_MUX(1);        // Set the MUX field for SW4 to GPIO mode
	
	//gpio config
	PTC->PDDR |= Mask(LED_A)| Mask(LED_B)| Mask(LED_C)| Mask(LED_D)| Mask(LED_E)| Mask(LED_F)| Mask(LED_G); //Set LED pins as outputs
  PTA->PDDR &= ~ (Mask(SW1)| Mask(SW2)| Mask(SW3)| Mask(SW4));        // Set the Switch pins as inputs
	
	// Set the initial state of LED's to off
	PTC->PCOR |= Mask(LED_A)| Mask(LED_B)| Mask(LED_C)| Mask(LED_D)| Mask(LED_E)| Mask(LED_F)| Mask(LED_G); //Set the LED's to off state intially
	
}

// Function to control the sate of LED's
void LED_control(int A, int B, int C, int D, int E, int F, int G){

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

// Time delay function 
void Delay(volatile unsigned int time){
	while(time --){;
	}
}

//This function checks the 7-segment LED's functionality after the mcu powered ON. 
void led_check(){
  LED_control(1, 0, 0, 0, 0, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control(0, 1, 0, 0, 0, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control(0, 0, 1, 0, 0, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control(0, 0, 0, 1, 0, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control(0, 0, 0, 0, 1, 0, 0);
	Delay(200000);                                // Add time delay
	LED_control(0, 0, 0, 0, 0, 1, 0);
	Delay(200000);                                // Add time delay
	LED_control(0, 0, 0, 0, 0, 0, 1); 
	Delay(200000);                                // Add time delay
	LED_control(1, 1, 1, 1, 1, 1, 1); 
	Delay(2000000);                                // Add time delay
	LED_control(0, 0, 0, 0, 0, 0, 0);
	Delay(2000000);                                // Add time delay
	LED_control(1, 1, 1, 1, 1, 1, 1); 
	Delay(2000000);                                // Add time delay
}

// This functions displays the values on the 7-segment display based of the input values
void LED_input_display(int value){
	if(value==0)
	LED_control(1, 1, 1, 1, 1, 1, 0);	
	
  if(value==1)
	LED_control(0, 1, 1, 0, 0, 0, 0);	
	
	if(value==2)
	LED_control(1, 1, 0, 1, 1, 0, 1);	
	
  if(value==3)
	LED_control(1, 1, 1, 1, 0, 0, 1);	
	
	if(value==4)
	LED_control(0, 1, 1, 0, 0, 1, 1);	
	
  if(value==5)
	LED_control(1, 0, 1, 1, 0, 1, 1);	
	
	if(value==6)
	LED_control(1, 0, 1, 1, 1, 1, 1);	
	
  if(value==7)
	LED_control(1, 1, 1, 0, 0, 0, 0);	
	
	if(value==8)
	LED_control(1, 1, 1, 1, 1, 1, 1);	
	
  if(value==9)
	LED_control(1, 1, 1, 1, 0, 1, 1);	
	
	 if(value==10)
	LED_control(0, 0, 0, 0, 0, 0, 0);	
}


//Main routine
int main(void){
	Leds_switches_init(); 											 // initialize  the speaker driver
 	led_check();                                 // Test the LED's functionality
	Delay(200000);
	
		while(1){		
			
			if(!(PTA->PDIR & Mask(SW1)))             // if SW1 is pressed, left shift by 3 positions and 'OR' the input_value
			input_value|= 1U<<3;
			
		  if(!(PTA->PDIR & Mask(SW2)))             // if SW2 is pressed, left shift by 2 positions and 'OR' the input_value
		  input_value|= 1U<<2;  
			
      if(!(PTA->PDIR & Mask(SW3)))            // if SW3 is pressed, left shift by 1 positions and 'OR' the input_value					
      input_value|= 1U<<1;					
			
		  if(!(PTA->PDIR & Mask(SW4)))            // if SW4 is pressed, no shift and 'OR' the input_value
			input_value|= 1U<<0;
			
      counter++;                              // incremnet the counter
			
			 if(counter==1000000){			            //check if the counter reachs 1000000 
				 LED_input_display(input_value);      // Call the display function to display the input_value that was grnerate after bitwise operations 
				 Delay(200000);  	                    
         input_value=0;				                // set the input_value back to zero  
				 counter=0;                           // set the counter back to zero for diaplaying the next set of inputs from switches 
			 }			
  }
}
