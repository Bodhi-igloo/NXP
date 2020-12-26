#include <MKL25Z4.h>

#define Audio_pin (1)   												// set the pin number 
#define Mask(x) (1U<<(x)) 											// define the mask function

// Function to initialize the speaker driver
void Speaker_driver_init(){
	SIM->SCGC5 |=SIM_SCGC5_PORTA_MASK;						// enable the clock for PORT A
	PORTA->PCR[Audio_pin] &= ~ PORT_PCR_MUX_MASK; // clear the mux filed in the PCR
	PORTA->PCR[Audio_pin] |= PORT_PCR_MUX(1); 		// Set the MUX field to "1" i.e GPIO mode
	PTA->PDDR |= Mask(Audio_pin); 								// set the GPIO direction as output
	PTA->PCOR |= Mask(Audio_pin); 								// Set the pin 1 after initialization
}

// Time delay function 
void Delay(volatile unsigned int time){
	while(time --){;
	}
}

//Main routine
int main(void){
	Speaker_driver_init(); 											 // initialize  the speaker driver
		while(1){
			PTA->PTOR = Mask(Audio_pin);             // set the toggle register
			Delay(2000000);                           // Add time delay
		}
		
}
