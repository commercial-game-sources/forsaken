#ifndef CDAUDIO_INCLUDED
#define CDAUDIO_INCLUDED

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
	Includes
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
#include "typedefs.h"
#include "d3dmain.h"

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
	Structures
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
#define MAX_AUDIO_TRACKS 16

typedef struct CDInfo {

    UINT			DeviceID;
	unsigned long	current_track; 
	DWORD			current_position;
	long			paused;
	long			loop;
	long			volume_id;
	long			IsPlaying;
	DWORD			num_tracks;
	DWORD			track_length[ MAX_AUDIO_TRACKS ];	// milliseconds
} CDInfo;

typedef struct CDSound {

	uint32			OriginalMusicVolume;

} CDSound;


#define CD_TITLE_TRACK 7

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
	Prototypes
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
void SoundInit( void );
void CloseCD( void );
void OpenCD( void );
void CdSetVolume( void );
void PlayAudioTrack( void );
void CdStop( void );
void CdUnPause( void );
void CdPause( void );
BOOL CdIsPlaying( void );

#endif
