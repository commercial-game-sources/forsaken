/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
	File	:	Restart.h
	Content	:	Restart.c include file
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
#ifndef RESTART_INCLUDED
#define RESTART_INCLUDED

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
	Defines
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
#define	ENABLE_RESTART		0

#define	RESTARTTYPE_MODEL	0
#define	RESTARTTYPE_FACEME	1

#define MAXRESTARTPOINTS	128

#define	RESTARTSEQ_Inactive		0
#define	RESTARTSEQ_Activating	1
#define	RESTARTSEQ_Active		2
#define	RESTARTSEQ_Deactivating	3

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
	Structures
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
typedef struct RESTART {
	
	uint16		Sequence;
	uint16		Index;
	uint16		Group;
	VECTOR		Pos;
	VECTOR		DirVector;
	VECTOR		UpVector;
	uint16		FmPoly;
	MATRIX		Matrix;
	float		Time;
	float		OverallTime;
	COMP_OBJ		*	Components;
	struct	RESTART	*	PrevUsed;
	struct	RESTART	*	NextUsed;
	struct	RESTART	*	PrevFree;
	struct	RESTART	*	NextFree;
	struct	RESTART	*	NextInGroup;
	struct	RESTART	*	PrevInGroup;

} RESTART;

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
	Prototypes
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
void InitRestartPoints( void );
RESTART * FindFreeRestartPoint( void );
void KillUsedRestartPoint( RESTART * Object );
void ReleaseAllRestartPoints( void );
BOOL LoadStartPoints( void );
BOOL PreLoadRestartPoints( void );
BOOL LoadRestartPoints( void );
RESTART * InitOneFaceMeRestartPoint( uint16 Group, VECTOR * Pos, VECTOR * DirVector, VECTOR * UpVector );
RESTART * InitOneRestartPoint( uint16 Group, VECTOR * Pos, VECTOR * DirVector, VECTOR * UpVector,
							  COMP_OBJ * CompObj, float OverallTime );
void ProcessRestartPoints( void );
void SetupRestartPointGroups( void );
void AddRestartPointToGroup( RESTART * Object, uint16 Group );
void RemoveRestartPointFromGroup( RESTART * Object, uint16 Group );
void MoveRestartPointToGroup( RESTART * Object, uint16 OldGroup, uint16 NewGroup );
void ActivateRestartPoint( uint16 NewStartPos, uint16 OldStartPos );
FILE * SaveStartRestartPoints( FILE * fp );
FILE * LoadStartRestartPoints( FILE * fp );
void DisplayStartPoints( void );

#endif


