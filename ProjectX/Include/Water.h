/*
 * w a t e r . h
 *
 *
 * Copyright (c) 1997 Probe Entertainment Limited
 * All Rights Reserved
 *
 * $Revision: 8 $
 *
 * $Header: /PcProjectX/Include/Water.h 8     5/01/98 10:39 Collinsd $
 *
 * $Log: /PcProjectX/Include/Water.h $
 * 
 * 8     5/01/98 10:39 Collinsd
 * Water Splash is now tinted by water colour.
 * 
 * 7     12/06/97 3:12p Phillipd
 * 
 * 6     12/04/97 4:55p Phillipd
 * 
 * 5     10/24/97 5:54p Phillipd
 * 
 * 4     10/21/97 5:07p Phillipd
 * 
 * 3     10/07/97 12:00p Phillipd
 * 
 * 2     10/06/97 7:20p Phillipd
 * 
 * 1     10/06/97 5:09p Phillipd
 *
 */
 
#ifndef WATER_H
#define WATER_H

#define	ROOTTWO  (1.0F / (float)sqrt(2.0F))
#define	SPECIALROOTTWO (1.0F / (4.0F+(1.0F / (float)sqrt(2.0F))*4.0F))
#define	MAXMESHX 32
#define	MAXMESHY 32
#define WATER_IMPACT	(-4.0F)
#define	ONEOVER255	(1.0F/255.0F)

#define	WATERSTATE_NOWATER 0
#define	WATERSTATE_SOMEWATER 1
#define	WATERSTATE_ALLWATER 2

#define	WATERSTATUS_STATIC		0
#define	WATERSTATUS_DRAINING	1
#define	WATERSTATUS_FILLING		2

typedef struct WATEROBJECT{
	uint32	AnimOncePerFrame;	// used for stuff that is displayed more than once in a single frame..or maybe called for multiple cameras..
	uint16	Status;
	uint16	Group;
	VECTOR	Pos;
	float	offset;
	float	XSize;
	float	YSize;
	float	uTL,vTL;			// uv coords Top Left
	float	uBR,vBR;			// uv coords Bottom Right
	float	uRange;
	float	vRange;
	int		YVerts;
	int		XVerts;
	int		num_of_verts;
	float *	Verts;				// Y positions...		
	float *	Vels;				// Y Velocities..

	float	Red;
	float	Green;
	float	Blue;

	LPDIRECT3DEXECUTEBUFFER	lpExBuf;
struct WATEROBJECT * GroupLink;

	float	MaxLevel;
	float	MinLevel;
	float	FillRate;
	float	DrainRate;
	float	Density;
	float	MaxWaveSize;
	uint16	Trigger_WhenFilled;
	uint16	Trigger_WhenDrained;
	float	Damage;


}WATEROBJECT;




//--------------------------------------------------------------------------
// Prototypes
//--------------------------------------------------------------------------
void GroupWaterProcessDisplay( uint16 group );
BOOL PreWaterLoad( char * Filename );
BOOL WaterLoad( void );
BOOL PreWaterLoad( char * Filename );
void WaterRelease( void );
void AddWaterLink(WATEROBJECT * WO);
void WaterProcess( void );
void TriggerWaterDrain( uint16 * Data );
void TriggerWaterFill( uint16 * Data );
BOOL SingleWaterObjectCollide( WATEROBJECT * Wo, VECTOR *Origin, VECTOR *Offset, VECTOR *CollidePos , float Damage);
BOOL InWater( uint16 group , VECTOR *OrgPos , float * Damage);
BOOL WaterObjectCollide( uint16 group , VECTOR *Origin, VECTOR *Offset, VECTOR *CollidePos , float Damage );
void GetWaterColour( uint16 Group, uint8 * Red, uint8 * Green, uint8 * Blue );

#endif // WATER_H
