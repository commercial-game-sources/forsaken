#ifndef	QUAT_DEFS
#define	QUAT_DEFS

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
	Quaternion Structures
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
typedef struct QUAT {
	float	w;
	float	x;
	float	y;
	float	z;
} QUAT;
typedef struct SHORTQUAT {
	int16	w;
	int16	x;
	int16	y;
	int16	z;
} SHORTQUAT;


typedef struct {

	QUAT		start;		// Starting QUATERNION
	QUAT		end;		// Ending QUATERNION
	QUAT *		crnt;		// Current QUATERNION to change
	float		time;		// Time
	float		dir;		// Direction

} QUATLERP;

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�
	Prototypes
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴�*/
void MakeQuat( float XRot, float YRot, float ZRot, QUAT * qxyz );
void QuatMultiply( QUAT * q1, QUAT * q2, QUAT * q1q2 );
void QuatMultiplyX_Y( QUAT * qx, QUAT * qy, QUAT * qxy );
void QuatMultiplyXY_Z( QUAT * qxy, QUAT * qz, QUAT * qxyz );
void QuatNormalise( QUAT * q );
void QuatToMatrix( QUAT * q, MATRIX * m );
float QuatDotProduct( QUAT * q1, QUAT * q2 );
void QuatInterpolate( register QUATLERP * ql );
void QuatFromVector( VECTOR * Tv, QUAT * q );
void QuatFromVector2( VECTOR * Tv, QUAT * q );
void Quaternion_Slerp( float alpha, QUAT * a, QUAT * b, QUAT * q, int spin );
void QuatInverse( QUAT * s, QUAT * d );
void QuatMake( QUAT * destQuat, float x, float y, float z, float angle);
void QuatFrom2Vectors( QUAT * destQuat, VECTOR * v1, VECTOR * v2 );
void MatrixToQuat(QUAT * destQuat, MATRIX * srcMatrix);
void QuatFromDirAndUp( VECTOR * Dir, VECTOR * Up, QUAT * Quat );

#endif