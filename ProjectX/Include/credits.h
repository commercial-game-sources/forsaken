/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
	File	:	Credits.h
	Content	:	Credits.c include file
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
#ifndef CREDITS_INCLUDED
#define CREDITS_INCLUDED

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
	Defines
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
#define		CREDIT_FADEINTITLE		0		// Fade In Title & Page
#define		CREDIT_FADEINPAGE		1		// Fade In New Page, Same Title
#define		CREDIT_FADEOUTPAGE		2		// Fade Out Page, Same Title
#define		CREDIT_FADEOUTTITLE		3		// Fade Out Title & Page
#define		CREDIT_PAGEPAUSE		4		// Pause 
#define		CREDIT_BLANKPAUSE		5		// Blank Pause
#define		CREDIT_INITIALPAUSE		6		// Initial Pause

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
	Structures
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
typedef struct PAGE {

	uint16		NumNames;
	uint8	**	Names;

} PAGE; 

typedef struct CREDIT {

	uint8	*	TitleString;
	uint16		NumPages;
	PAGE	*	FirstPage;

} CREDIT; 

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
	Prototypes
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
void SetupCredits( void );
void SetupGameCompleteCredits( void );
void DisplayCredits( void );
void ReleaseCredits( void );
void FadeColourFloat( float * Colour, float WantedColour, float Step );
int16 GetStringLength( uint8 * String, int16 Font );
void CenterPrintString( int16 Font, int16 Xpos, int16 Ypos, uint8 * String, uint8 Red, uint8 Green, uint8 Blue, uint8 Trans );
void DisplayForsaken( int16 Xpos, int16 Ypos, uint8 Red, uint8 Green, uint8 Blue, uint8 Trans );
void DisplayForsakenAnyKey( void );
void SetupForsakenAnyKey( void );
void SetupCharTransTable( void );

#endif
