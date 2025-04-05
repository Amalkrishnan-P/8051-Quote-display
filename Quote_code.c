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

/* Array of 10 Quotes */
const char *quotes[10] = {
    "1. The greatest glory in living lies not in never falling, but in rising every time we fall. - Nelson Mandela",
    "2. The way to get started is to quit talking and begin doing. - Walt Disney",
    "3. Your time is limited, so don't waste it living someone else's life. - Steve Jobs",
    "4. If life were predictable it would cease to be life, and be without flavor. - Eleanor Roosevelt",
    "5. If you look at what you have in life, you'll always have more. - Oprah Winfrey",
    "6. If you set your goals ridiculously high and it's a failure, you will fail above everyone else's success. - James Cameron",
    "7. Life is what happens when you're busy making other plans. - John Lennon",
    "8. Spread love everywhere you go. Let no one ever come to you without leaving happier. - Mother Teresa",
    "9. When you reach the end of your rope, tie a knot in it and hang on. - Franklin D. Roosevelt",
    "10. Always remember that you are absolutely unique. Just like everyone else. - Margaret Mead"
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
                        LcdCommand(0x1c);/*Shift the entire display to the right*/
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
    LcdCommand(0x38);  /* 2 lines, 5x7 matrix */
    LcdCommand(0x0c);  /* Display on, cursor off */
    LcdCommand(0x01);  /* Clear display */
    LcdCommand(0x06);  /* Increment cursor, Left Align*/
}