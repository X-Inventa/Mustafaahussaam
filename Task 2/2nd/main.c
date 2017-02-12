#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>


#define EN 5
#define RW 7
#define RS 2

uint8_t y,m,z=0, pressed;
void BUSY(void);
void ENABLE(void);
void Send_A_Command(unsigned char command);
void Send_A_Character(unsigned char character);
void Send_A_String(unsigned char *stringcharacter);
void key1(void);
void key2(void);
void key3(void);
void key4(void);
void key5(void);
void key6(void);
void key7(void);
void key8(void);
char pad[9]={0b11111110,0b11111101,0b11111011,0b11110111,0b11101111,0b11011111,0b10111111,0b01111111,0b11111111} ;

int main(void)
	{
		DDRD |= 1<<EN | 1<<RW | 1<<RS;			//Make PORTD as an output to give it orders.
		_delay_ms(15);

		Send_A_Command(0b00000001);
		_delay_ms(3);
		Send_A_Command(0x38);
		_delay_us(50);
		Send_A_Command(0b00001110);
		_delay_us(50);
		

		DDRA = 0x00;
		PORTA= 0xFF;
		TCCR1B = 1<<CS10 | 1<<CS11 ;
		
		
		
		while(1)
 {   
		pressed=0;
 		if (PINA==pad[0])   key1(); 
        if (PINA==pad[1])   key2();
	    if (PINA==pad[2])   key3();	
		if (PINA==pad[3])	key4();
		if (PINA==pad[4])   key5();
		if (PINA==pad[5])   key6();
		if (PINA==pad[6])	key7();
		if (PINA==pad[7])	key8();
 }     
	 
}

	void BUSY()
	{
		DDRB = 0x00;                            //Make PORTB input to read fro it if its busy or not .
		PORTD |= 1<<RW;							// We turn RW on so we can read.
		PORTD &= ~1<<RS;                        // Command mode.

		while (PORTB>= 0x80)
		{
			ENABLE();
		}
		DDRB = 0xFF;							//Make PORTB in output mode so we can write on it after that
	}

	void ENABLE()
	{
		PORTD |= 1<<EN;
		asm volatile ("nop");
		asm volatile ("nop");				    // A Time to make the lcd read the process
		PORTD &= ~1<<EN;
	}

	void Send_A_Command(unsigned char command)
	{
		BUSY();
		PORTB = command;						// Writing the command from the data sheet.
		PORTD &= ~ ((1<<RW)|(1<<RS));			// We turn RW off so we can write and We turn RS off for command mode .
		ENABLE();                               // We turn on the enable and then turn it off.
		PORTB = 0x00;
	}

	void Send_A_Character(unsigned char character)
	{
		BUSY();
		PORTB = character;					    // Writing the character from the data sheet.
		PORTD &= ~ (1<<RW);						// We turn RW off so we can write.
		PORTD |= 1<<RS;							// We turn RS off for command mode and on for character mode.
		ENABLE();								// We turn on the enable and then turn it off.
		PORTB= 0x00;
	}
	void Send_A_String(unsigned char *stringcharacter)
	{
		while(*stringcharacter>0)
		{
			Send_A_Character(*stringcharacter++) ;
		}
	}
	// keys code ,                                                       key 1

void key1()
{
	uint8_t x=150 ;
	pressed=1 ;
	_delay_ms(x);
	while(pressed==1)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("a");
		
		if (PINA==pad[0])
		{
			pressed=2;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while (pressed==2)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("b");
		
		if(PINA==pad[0])
		{
			pressed=3;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==3)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("c");
		
		if(PINA==pad[0])
		{
			pressed=4;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==4)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("d");
		
		if(PINA==pad[0])
		{
			pressed=1;
			_delay_ms(30);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==5&&PINA==pad[8])
	{
		z++;
		Send_A_Command(0x80+z)  ;
		TCNT1 = 0 ;
		pressed=0 ;
	}
}
void key2()  
{   
	uint8_t x=150 ;
	pressed=1 ;
	_delay_ms(x);
	while(pressed==1)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("e");
		
		if (PINA==pad[1])
		{
			pressed=2;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while (pressed==2)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("f");
		
		if(PINA==pad[1])
		{
			pressed=3;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==3)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("g");
		
		if(PINA==pad[1])
		{
			pressed=4;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==4)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("h");
		
		if(PINA==pad[1])
		{
			pressed=1;
			_delay_ms(30);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==5&&PINA==pad[8])
	{
		z++;
		Send_A_Command(0x80+z)  ;
		TCNT1 = 0 ;
		pressed=0 ;
	}

}
void key3() 
{
	uint8_t x=150 ;
	pressed=1 ;
	_delay_ms(x);
	while(pressed==1)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("i");
		
		if (PINA==pad[2])
		{
			pressed=2;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while (pressed==2)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("j");
		
		if(PINA==pad[2])
		{
			pressed=3;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==3)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("k");
		
		if(PINA==pad[2])
		{
			pressed=4;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==4)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("l");
		
		if(PINA==pad[2])
		{
			pressed=1;
			_delay_ms(30);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==5&&PINA==pad[8])
	{
		z++;
		Send_A_Command(0x80+z)  ;
		TCNT1 = 0 ;
		pressed=0 ;
	}

}
void key4() {
uint8_t x=150 ;
	pressed=1 ;
	_delay_ms(x);
	while(pressed==1)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("m");
		
		if (PINA==pad[3])
		{
			pressed=2;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while (pressed==2)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("n");
		
		if(PINA==pad[3])
		{
			pressed=3;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==3)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("o");
		
		if(PINA==pad[3])
		{
			pressed=4;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==4)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("p");
		
		if(PINA==pad[3])
		{
			pressed=1;
			_delay_ms(30);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==5&&PINA==pad[8])
	{
		z++;
		Send_A_Command(0x80+z)  ;
		TCNT1 = 0 ;
		pressed=0 ;
	}}
void key5() {uint8_t x=150 ;
	pressed=1 ;
	_delay_ms(x);
	while(pressed==1)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("q");
		
		if (PINA==pad[4])
		{
			pressed=2;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while (pressed==2)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("r");
		
		if(PINA==pad[4])
		{
			pressed=3;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==3)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("s");
		
		if(PINA==pad[4])
		{
			pressed=4;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==4)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("t");
		
		if(PINA==pad[4])
		{
			pressed=1;
			_delay_ms(30);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==5&&PINA==pad[8])
	{
		z++;
		Send_A_Command(0x80+z)  ;
		TCNT1 = 0 ;
		pressed=0 ;
	}}
void key6() {uint8_t x=150 ;
	pressed=1 ;
	_delay_ms(x);
	while(pressed==1)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("u");
		
		if (PINA==pad[5])
		{
			pressed=2;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while (pressed==2)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("v");
		
		if(PINA==pad[5])
		{
			pressed=3;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==3)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("w");
		
		if(PINA==pad[5])
		{
			pressed=4;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==4)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("x");
		
		if(PINA==pad[5])
		{
			pressed=1;
			_delay_ms(30);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==5&&PINA==pad[8])
	{
		z++;
		Send_A_Command(0x80+z)  ;
		TCNT1 = 0 ;
		pressed=0 ;
	}}
void key7() 
{
	uint8_t x=150 ;
	pressed=1 ;
	_delay_ms(x);
	while(pressed==1)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("y");
		
		if (PINA==pad[6])
		{
			pressed=2;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while (pressed==2)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("z");
		
		if(PINA==pad[6])
		{
			pressed=3;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==3)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("-");
		
		if(PINA==pad[6])
		{
			pressed=4;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==4)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String("#") ;
		
		if(PINA==pad[6])
		{
			pressed=1;
			_delay_ms(30);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==5&&PINA==pad[8])
	{
		z++;
		Send_A_Command(0x80+z)  ;
		TCNT1 = 0 ;
		pressed=0 ;
	}}
void key8() {
    uint8_t x=150 ;
	pressed=1 ;
	_delay_ms(x);
	while(pressed==1)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String(" ");
		
		if (PINA==pad[7])
		{
			pressed=2;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while (pressed==2)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String(" ");
		
		if(PINA==pad[7])
		{
			pressed=3;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==3)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String(" ");
		
		if(PINA==pad[7])
		{
			pressed=4;
			_delay_ms(x);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==4)
	{
		Send_A_Command(0x80+z) ;
		Send_A_String(" ");
		
		if(PINA==pad[7])
		{
			pressed=1;
			_delay_ms(30);
		}
		
		else if (PINA==pad[8]&&TCNT1>65000)
		pressed=5;
	}
	while(pressed==5&&PINA==pad[8])
	{
		z++;
		Send_A_Command(0x80+z)  ;
		TCNT1 = 0 ;
		pressed=0 ;
	}}