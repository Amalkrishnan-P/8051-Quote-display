#include <reg51.h>
#include <string.h>

#define LCD P2  /* Attached LCD on Port 2 */

sbit rs = P3^0; /* Configure RS Pin */
sbit rw = P3^1; /* Configure R/W Pin */
sbit e  = P3^2; /* Configure Latch Enable Pin */

/* Function to write command on Lcd */
void LcdCommand(const char command);

/* Function to display quote on Lcd */
void DisplayQuote(const char *quote);

/* Function to initialize Lcd */
void LcdInit(void);

/* Function to provide delay */
void Delay(unsigned int);

/* Array of 33 Legendary Quotes */
const char *quotes[33] = {
    "No Money, No Honey - Vyshnav R"
    "Do nothing which is of no use-Musashi",
    "It's not over till it's over.-Rocky"
    "Victory is in the mind.-Musashi",
    "Love is all you need-John Lennon",
    "Love is not enough.-Trent Reznor",
    "Adapt to changing situations.-Musashi",
    "Vision creates destiny.-Arnold ",
    "Emptiness is the beginning.-Musashi",
    "Don't just dream, do-Arnold ",
    "Perception is reality.-Musashi",
    "Strategy is life.-Musashi",
    "Train to failure, grow.-Mike Mentzer",
    "Pain is temporary, quitting lasts.-Rock",
    "Know thyself, know thy enemy.-Musashi",
    "Initiative is key to victory.-Musashi",
    "Stillness is movement.-Musashi",
    "True victory is self-victory.-Musashi",
    "Believe in yourself.-Arnold ",
    "Work hard, play hard.-Arnold ",
    "Reality's distorted, truth's hidden-Murakami",
    "Memories fade, but emotions linger-Murakami",
    "It's not over till it's over.-Rocky",
    "Get back up!-Rocky",
    "Life's tough, kid.-Rocky",
    "Keep moving forward, always.-Rocky",
    "Heavy weights, low reps.-Mike Mentzer",
    "Be the hardest worker.- Rock",
    "Pain is inevitable, suffering optional-Murakami",
    "Reality's distorted, truth's hidden-Murakami",
    "Memories fade, but emotions linger-Murakami",
    "To love oneself is beginning.-Oscar W",
    "Your network is your net worth-Andrew Tate"
};

int main()
{
    short Quote_Character = 0;
    short Quote_Index     = 0;
    short Quote_length    = 0;
    LcdInit();  /* Initialize the LCD */

    while(1)
    {
        /* Display each quote  */
        for (Quote_Index = 0; Quote_Index < 10; Quote_Index++) 
        {
            LcdCommand(0x01);  /* Clear the LCD */
            Delay(10);         /* Short delay for the LCD to clear */
            LcdCommand(0x80);  /* Set the DDRAM address to start displaying from the first line */

            Quote_length = strlen(quotes[Quote_Index]); /* Obtain length of quote*/

            /* Display the current quote */
            DisplayQuote(quotes[Quote_Index]);

                for(Quote_Character=0; Quote_Character < Quote_length; Quote_Character++)
                    {
                        LcdCommand(0x18);/*Shift the entire display to the left*/
                        Delay(25);
                    }
                    /* Wait for 1 second */
                    Delay(1000);  
        }
    }
}

/* Function to write command on Lcd */
void LcdCommand(const char command)
{
    rs = 0;
    rw = 0;
    e  = 1;
    LCD = command;
    Delay(1);
    e = 0;
    Delay(10);
}

/* Function to Display message on Lcd */
void DisplayQuote(const char *quote)
{
    rs = 1;
    rw = 0;
    while(*quote != '\0')
    {
        e  = 1;
        LCD = *quote;
        Delay(1);
        e = 0;
        quote++;
        Delay(10);
    }
}

/* Function to provide delay */
void Delay(unsigned int i)
{
    int j, k;
    for (j = 0; j < i; j++)
    {
        for (k = 0; k < 1275; k++);  /* Approximate 1 ms delay per loop */
    }
}

/* Initialize the LCD */
void LcdInit(void)
{
    LcdCommand(0x30);  /* 1 line, 5x7 matrix */
    LcdCommand(0x0c);  /* Display on, cursor off */
    LcdCommand(0x01);  /* Clear display */
    LcdCommand(0x06);  /* Increment cursor, Left Align*/
}