#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{

    /*
     * SSEL = SMCLK
     * MC = cont�nuo
     */

    /*
     * CAP = 1
     * CCIS = CCIA
     * CM = RisingEdge
     */

    int edgeCnt = 0;
    int freq;

	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	
	//P1.1 -> ACLK, P1.6 -> TB0CCIA.1
	P1DIR |= BIT1;
	P1DIR &= ~BIT6;

	P1SEL0 &= ~(BIT6 | BIT1);
	P1SEL1 |= (BIT6 | BIT1);

	TB0CTL = TBSSEL__SMCLK | MC__CONTINUOUS;

	TB0CCTL1 = CAP_1 | CCIS__CCIA | CM__RISING;
	//                      ^ P1.6

	while(1){
	    edgeCnt = 16;
	    TB0CTL |= TBCLR;
	    while(edgeCnt--){                  // condicional do diagrama
	        while(!(TB0CTL & CCIFG));     // aguardar o flanco
	        TB0CCTL1 &= ~CCIFG;
	    }

	    freq = 1048576/(TB0CCR1 >> 4); // >> 4 � /16

	    // final do diagrama!

	    // ap�s 16 repeti��es CCR1 possui o numero de batidas do inicio at�
	    // o d�cimo sexto flanco. Assim, Fi = Fclk/dN
	    // dN � a m�dia de 16 per�odos para compensar por um erro de medi��o

	}

	return 0;
}
