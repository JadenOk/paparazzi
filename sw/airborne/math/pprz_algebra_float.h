/*
 * $Id$
 *
 * Copyright (C) 2008  Antoine Drouin
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#ifndef PPRZ_ALGEBRA_FLOAT_H
#define PPRZ_ALGEBRA_FLOAT_H

#include "pprz_algebra.h"

#include <math.h>
#include <float.h> // for FLT_MIN

struct FloatVect2 {
  float x;
  float y;
};

struct FloatVect3 {
  float x;
  float y;
  float z;
};

struct FloatQuat {
  float qi;
  float qx;
  float qy;
  float qz;
};

struct FloatMat33 {
  float m[3*3];
};

struct FloatRMat {
  float m[3*3];
};

struct FloatEulers {
  float phi;
  float theta;
  float psi;
};

struct FloatRates {
  float p;
  float q;
  float r;
};

#define FLOAT_ANGLE_NORMALIZE(_a) {				\
    while (_a >  M_PI) _a -= (2.*M_PI);				\
    while (_a < -M_PI) _a += (2.*M_PI);				\
  }


/*
 * Dimension 2 Vectors
 */

#define FLOAT_VECT2_ZERO(_v) VECT2_ASSIGN(_v, 0., 0.)

/* a =  {x, y} */
#define FLOAT_VECT2_ASSIGN(_a, _x, _y) VECT2_ASSIGN(_a, _x, _y)

/* a = b */
#define FLOAT_VECT2_COPY(_a, _b) VECT2_COPY(_a, _b)

/* a += b */
#define FLOAT_VECT2_ADD(_a, _b)  VECT2_ADD(_a, _b)

/* c = a + b */
#define FLOAT_VECT2_SUM(_c, _a, _b) VECT2_SUM(_c, _a, _b)

/* c = a - b */
#define FLOAT_VECT2_DIFF(_c, _a, _b) VECT2_DIFF(_c, _a, _b)

/* a -= b */
#define FLOAT_VECT2_SUB(_a, _b) VECT2_SUB(_a, _b)

/* _vo = _vi * _s */
#define FLOAT_VECT2_SMUL(_vo, _vi, _s) VECT2_SMUL(_vo, _vi, _s)


/*
 * Dimension 3 Vectors
 */

#define FLOAT_VECT3_ZERO(_v) VECT3_ASSIGN(_v, 0., 0., 0.)

#define FLOAT_VECT3_ASSIGN(_a, _x, _y, _z) VECT3_ASSIGN(_a, _x, _y, _z)

/* c = a - b */
#define FLOAT_VECT3_DIFF(_c, _a, _b) VECT3_DIFF(_c, _a, _b)

/* a -= b */
#define FLOAT_VECT3_SUB(_a, _b) VECT3_SUB(_a, _b)

/* _vo = _vi * _s */
#define FLOAT_VECT3_SMUL(_vo, _vi, _s) VECT3_SMUL(_vo, _vi, _s)

#define FLOAT_VECT3_NORM(_v) (sqrtf((_v).x*(_v).x + (_v).y*(_v).y + (_v).z*(_v).z))

#define FLOAT_VECT3_CROSS_PRODUCT(vo, v1, v2) {				\
    vo.x = v1.y*v2.z - v1.z*v2.y;					\
    vo.y = v1.z*v2.x - v1.x*v2.z;					\
    vo.z = v1.x*v2.y - v1.y*v2.x;					\
  }

#define FLOAT_VECT3_NORMALIZE(_v) {		\
    const float n = FLOAT_VECT3_NORM(_v);	\
    FLOAT_VECT3_SMUL(_v, _v, 1./n);		\
  }

#define FLOAT_RATES_ZERO(_r) {			\
    RATES_ASSIGN(_r, 0., 0., 0.);		\
  }

#define FLOAT_RATES_NORM(_v) (sqrtf((_v).p*(_v).p + (_v).q*(_v).q + (_v).r*(_v).r))


/*
 * 3x3 matrices
 */
#define FLOAT_MAT33_ZERO(_m) {						\
    MAT33_ELMT(_m, 0, 0) = 0.;						\
    MAT33_ELMT(_m, 0, 1) = 0.;						\
    MAT33_ELMT(_m, 0, 2) = 0.;                                          \
    MAT33_ELMT(_m, 1, 0) = 0.;						\
    MAT33_ELMT(_m, 1, 1) = 0.;						\
    MAT33_ELMT(_m, 1, 2) = 0.;						\
    MAT33_ELMT(_m, 2, 0) = 0.;						\
    MAT33_ELMT(_m, 2, 1) = 0.;						\
    MAT33_ELMT(_m, 2, 2) = 0.;						\
  }

#define FLOAT_MAT33_DIAG(_m, _d00, _d11, _d22) {			\
    MAT33_ELMT(_m, 0, 0) = _d00;					\
    MAT33_ELMT(_m, 0, 1) = 0.;						\
    MAT33_ELMT(_m, 0, 2) = 0.;						\
    MAT33_ELMT(_m, 1, 0) = 0.;						\
    MAT33_ELMT(_m, 1, 1) = _d11;					\
    MAT33_ELMT(_m, 1, 2) = 0.;						\
    MAT33_ELMT(_m, 2, 0) = 0.;						\
    MAT33_ELMT(_m, 2, 1) = 0.;						\
    MAT33_ELMT(_m, 2, 2) = _d22;					\
  }


/*
 * Rotation Matrices
 */

/* initialises a matrix to identity */
#define FLOAT_RMAT_ZERO(_rm) FLOAT_MAT33_DIAG(_rm, 1., 1., 1.)

/* initialises a rotation matrix from unit vector axis and angle */
#define FLOAT_RMAT_OF_AXIS_ANGLE(_rm, _uv, _an) {			\
    									\
    const float ux2  = _uv.x*_uv.x;					\
    const float uy2  = _uv.y*_uv.y;					\
    const float uz2  = _uv.z*_uv.z;					\
    const float uxuy = _uv.x*_uv.y;					\
    const float uyuz = _uv.y*_uv.z;					\
    const float uxuz = _uv.x*_uv.z;					\
    const float can  = cosf(_an);					\
    const float san  = sinf(_an);					\
    const float one_m_can = (1. - can);					\
    									\
    RMAT_ELMT(_rm, 0, 0) = ux2 + (1.-ux2)*can;				\
    RMAT_ELMT(_rm, 0, 1) = uxuy*one_m_can + _uv.z*san;			\
    RMAT_ELMT(_rm, 0, 2) = uxuz*one_m_can - _uv.y*san;			\
    RMAT_ELMT(_rm, 1, 0) = uxuy*one_m_can - _uv.z*san;			\
    RMAT_ELMT(_rm, 1, 1) = uy2 + (1.-uy2)*can;				\
    RMAT_ELMT(_rm, 1, 2) = uyuz*one_m_can + _uv.x*san;			\
    RMAT_ELMT(_rm, 2, 0) = uxuz*one_m_can + _uv.y*san;			\
    RMAT_ELMT(_rm, 2, 1) = uyuz*one_m_can - _uv.x*san;			\
    RMAT_ELMT(_rm, 2, 2) = uz2 + (1.-uz2)*can;				\
    									\
  }

/* multiply _vin by _rmat, store in _vout */
#define FLOAT_RMAT_VECT3_MUL(_vout, _rmat, _vin) RMAT_VECT3_MUL(_vout, _rmat, _vin)

#define FLOAT_RMAT_TRANSP_RATEMULT(_vb, _m_b2a, _va) {				                         \
    (_vb).p = ( (_m_b2a).m[0]*(_va).p + (_m_b2a).m[3]*(_va).q + (_m_b2a).m[6]*(_va).r); \
    (_vb).q = ( (_m_b2a).m[1]*(_va).p + (_m_b2a).m[4]*(_va).q + (_m_b2a).m[7]*(_va).r); \
    (_vb).r = ( (_m_b2a).m[2]*(_va).p + (_m_b2a).m[5]*(_va).q + (_m_b2a).m[8]*(_va).r); \
  }

#define FLOAT_RMAT_RATEMULT(_vb, _m_a2b, _va) {				                         \
    (_vb).p = ( (_m_a2b).m[0]*(_va).p + (_m_a2b).m[1]*(_va).q + (_m_a2b).m[2]*(_va).r); \
    (_vb).q = ( (_m_a2b).m[3]*(_va).p + (_m_a2b).m[4]*(_va).q + (_m_a2b).m[5]*(_va).r); \
    (_vb).r = ( (_m_a2b).m[6]*(_va).p + (_m_a2b).m[7]*(_va).q + (_m_a2b).m[8]*(_va).r); \
  }

/* _m_a2c = _m_a2b comp _m_b2c , aka  _m_a2c = _m_b2c * _m_a2b */
#define FLOAT_RMAT_COMP(_m_a2c, _m_a2b, _m_b2c) {			\
    _m_a2c.m[0] = (_m_b2c.m[0]*_m_a2b.m[0] + _m_b2c.m[1]*_m_a2b.m[3] + _m_b2c.m[2]*_m_a2b.m[6]); \
    _m_a2c.m[1] = (_m_b2c.m[0]*_m_a2b.m[1] + _m_b2c.m[1]*_m_a2b.m[4] + _m_b2c.m[2]*_m_a2b.m[7]); \
    _m_a2c.m[2] = (_m_b2c.m[0]*_m_a2b.m[2] + _m_b2c.m[1]*_m_a2b.m[5] + _m_b2c.m[2]*_m_a2b.m[8]); \
    _m_a2c.m[3] = (_m_b2c.m[3]*_m_a2b.m[0] + _m_b2c.m[4]*_m_a2b.m[3] + _m_b2c.m[5]*_m_a2b.m[6]); \
    _m_a2c.m[4] = (_m_b2c.m[3]*_m_a2b.m[1] + _m_b2c.m[4]*_m_a2b.m[4] + _m_b2c.m[5]*_m_a2b.m[7]); \
    _m_a2c.m[5] = (_m_b2c.m[3]*_m_a2b.m[2] + _m_b2c.m[4]*_m_a2b.m[5] + _m_b2c.m[5]*_m_a2b.m[8]); \
    _m_a2c.m[6] = (_m_b2c.m[6]*_m_a2b.m[0] + _m_b2c.m[7]*_m_a2b.m[3] + _m_b2c.m[8]*_m_a2b.m[6]); \
    _m_a2c.m[7] = (_m_b2c.m[6]*_m_a2b.m[1] + _m_b2c.m[7]*_m_a2b.m[4] + _m_b2c.m[8]*_m_a2b.m[7]); \
    _m_a2c.m[8] = (_m_b2c.m[6]*_m_a2b.m[2] + _m_b2c.m[7]*_m_a2b.m[5] + _m_b2c.m[8]*_m_a2b.m[8]); \
  }


/* _m_a2b = _m_a2c comp_inv _m_b2c , aka  _m_a2b = inv(_m_b2c) * _m_a2c */
#define FLOAT_RMAT_COMP_INV(_m_a2b, _m_a2c, _m_b2c) {			\
    _m_a2b.m[0] = (_m_b2c.m[0]*_m_a2c.m[0] + _m_b2c.m[3]*_m_a2c.m[3] + _m_b2c.m[6]*_m_a2c.m[6]); \
    _m_a2b.m[1] = (_m_b2c.m[0]*_m_a2c.m[1] + _m_b2c.m[3]*_m_a2c.m[4] + _m_b2c.m[6]*_m_a2c.m[7]); \
    _m_a2b.m[2] = (_m_b2c.m[0]*_m_a2c.m[2] + _m_b2c.m[3]*_m_a2c.m[5] + _m_b2c.m[6]*_m_a2c.m[8]); \
    _m_a2b.m[3] = (_m_b2c.m[1]*_m_a2c.m[0] + _m_b2c.m[4]*_m_a2c.m[3] + _m_b2c.m[7]*_m_a2c.m[6]); \
    _m_a2b.m[4] = (_m_b2c.m[1]*_m_a2c.m[1] + _m_b2c.m[4]*_m_a2c.m[4] + _m_b2c.m[7]*_m_a2c.m[7]); \
    _m_a2b.m[5] = (_m_b2c.m[1]*_m_a2c.m[2] + _m_b2c.m[4]*_m_a2c.m[5] + _m_b2c.m[7]*_m_a2c.m[8]); \
    _m_a2b.m[6] = (_m_b2c.m[2]*_m_a2c.m[0] + _m_b2c.m[5]*_m_a2c.m[3] + _m_b2c.m[8]*_m_a2c.m[6]); \
    _m_a2b.m[7] = (_m_b2c.m[2]*_m_a2c.m[1] + _m_b2c.m[5]*_m_a2c.m[4] + _m_b2c.m[8]*_m_a2c.m[7]); \
    _m_a2b.m[8] = (_m_b2c.m[2]*_m_a2c.m[2] + _m_b2c.m[5]*_m_a2c.m[5] + _m_b2c.m[8]*_m_a2c.m[8]); \
  }


/* _m_b2a = inv(_m_a2b) = transp(_m_a2b) */
#define FLOAT_RMAT_INV(_m_b2a, _m_a2b) {			\
    RMAT_ELMT(_m_b2a, 0, 0) = RMAT_ELMT(_m_a2b, 0, 0);		\
    RMAT_ELMT(_m_b2a, 0, 1) = RMAT_ELMT(_m_a2b, 1, 0);		\
    RMAT_ELMT(_m_b2a, 0, 2) = RMAT_ELMT(_m_a2b, 2, 0);		\
    RMAT_ELMT(_m_b2a, 1, 0) = RMAT_ELMT(_m_a2b, 0, 1);		\
    RMAT_ELMT(_m_b2a, 1, 1) = RMAT_ELMT(_m_a2b, 1, 1);		\
    RMAT_ELMT(_m_b2a, 1, 2) = RMAT_ELMT(_m_a2b, 2, 1);		\
    RMAT_ELMT(_m_b2a, 2, 0) = RMAT_ELMT(_m_a2b, 0, 2);		\
    RMAT_ELMT(_m_b2a, 2, 1) = RMAT_ELMT(_m_a2b, 1, 2);		\
    RMAT_ELMT(_m_b2a, 2, 2) = RMAT_ELMT(_m_a2b, 2, 2);		\
  }

#define FLOAT_RMAT_NORM(_m) (						\
    sqrtf(SQUARE((_m).m[0])+ SQUARE((_m).m[1])+ SQUARE((_m).m[2])+	\
	  SQUARE((_m).m[3])+ SQUARE((_m).m[4])+ SQUARE((_m).m[5])+	\
	  SQUARE((_m).m[6])+ SQUARE((_m).m[7])+ SQUARE((_m).m[8]))	\
    )

#define FLOAT_RMAT_OF_EULERS(_rm, _e) FLOAT_RMAT_OF_EULERS_321(_rm, _e)

/* C n->b rotation matrix */
#define FLOAT_RMAT_OF_EULERS_321(_rm, _e) {				\
    									\
    const float sphi   = sinf((_e).phi);				\
    const float cphi   = cosf((_e).phi);				\
    const float stheta = sinf((_e).theta);				\
    const float ctheta = cosf((_e).theta);				\
    const float spsi   = sinf((_e).psi);				\
    const float cpsi   = cosf((_e).psi);				\
    									\
    RMAT_ELMT(_rm, 0, 0) = ctheta*cpsi;					\
    RMAT_ELMT(_rm, 0, 1) = ctheta*spsi;					\
    RMAT_ELMT(_rm, 0, 2) = -stheta;					\
    RMAT_ELMT(_rm, 1, 0) = sphi*stheta*cpsi - cphi*spsi;		\
    RMAT_ELMT(_rm, 1, 1) = sphi*stheta*spsi + cphi*cpsi;		\
    RMAT_ELMT(_rm, 1, 2) = sphi*ctheta;					\
    RMAT_ELMT(_rm, 2, 0) = cphi*stheta*cpsi + sphi*spsi;		\
    RMAT_ELMT(_rm, 2, 1) = cphi*stheta*spsi - sphi*cpsi;		\
    RMAT_ELMT(_rm, 2, 2) = cphi*ctheta;					\
    									\
  }


#define FLOAT_RMAT_OF_EULERS_312(_rm, _e) {				\
    									\
    const float sphi   = sinf((_e).phi);				\
    const float cphi   = cosf((_e).phi);				\
    const float stheta = sinf((_e).theta);				\
    const float ctheta = cosf((_e).theta);				\
    const float spsi   = sinf((_e).psi);				\
    const float cpsi   = cosf((_e).psi);				\
    									\
    RMAT_ELMT(_rm, 0, 0) =  ctheta*cpsi - sphi * stheta * spsi;		\
    RMAT_ELMT(_rm, 0, 1) =  ctheta*spsi + sphi * stheta * cpsi;		\
    RMAT_ELMT(_rm, 0, 2) = -cphi * stheta;				\
    RMAT_ELMT(_rm, 1, 0) = -cphi * spsi;				\
    RMAT_ELMT(_rm, 1, 1) =  cphi * cpsi;				\
    RMAT_ELMT(_rm, 1, 2) =  sphi;					\
    RMAT_ELMT(_rm, 2, 0) =  stheta*cpsi + sphi*ctheta*spsi;		\
    RMAT_ELMT(_rm, 2, 1) =  stheta*spsi - sphi*ctheta*cpsi;		\
    RMAT_ELMT(_rm, 2, 2) =  cphi*ctheta;				\
    									\
  }


/* C n->b rotation matrix */
#define FLOAT_RMAT_OF_QUAT(_rm, _q) {	                                \
    const float qx2  = (_q).qx*(_q).qx;					\
    const float qy2  = (_q).qy*(_q).qy;					\
    const float qz2  = (_q).qz*(_q).qz;					\
    const float qiqx = (_q).qi*(_q).qx;					\
    const float qiqy = (_q).qi*(_q).qy;					\
    const float qiqz = (_q).qi*(_q).qz;					\
    const float qxqy = (_q).qx*(_q).qy;					\
    const float qxqz = (_q).qx*(_q).qz;					\
    const float qyqz = (_q).qy*(_q).qz;					\
    /* dcm00 = 1.0 - 2.*(  qy2 +  qz2 ); */				\
    RMAT_ELMT(_rm, 0, 0) =  1. - 2.*(  qy2 +  qz2 );			\
    /* dcm01 =       2.*( qxqy + qiqz ); */				\
    RMAT_ELMT(_rm, 0, 1) = 2.*( qxqy + qiqz );				\
    /* dcm02 =       2.*( qxqz - qiqy ); */				\
    RMAT_ELMT(_rm, 0, 2) = 2.*( qxqz - qiqy );				\
    /* dcm10 = 2.*( qxqy - qiqz );       */				\
    RMAT_ELMT(_rm, 1, 0) = 2.*( qxqy - qiqz );				\
    /* dcm11 = 1.0 - 2.*(qx2+qz2);       */				\
    RMAT_ELMT(_rm, 1, 1) = 1.0 - 2.*(qx2+qz2);				\
    /* dcm12 =       2.*( qyqz + qiqx ); */				\
    RMAT_ELMT(_rm, 1, 2) = 2.*( qyqz + qiqx );				\
    /* dcm20 =       2.*( qxqz + qiqy ); */				\
    RMAT_ELMT(_rm, 2, 0) = 2.*( qxqz + qiqy );				\
    /* dcm21 =       2.*( qyqz - qiqx ); */				\
    RMAT_ELMT(_rm, 2, 1) = 2.*( qyqz - qiqx );				\
    /* dcm22 = 1.0 - 2.*(  qx2 +  qy2 ); */				\
    RMAT_ELMT(_rm, 2, 2) = 1.0 - 2.*(  qx2 +  qy2 );			\
  }




/*
 * Quaternions
 */

#define FLOAT_QUAT_ZERO(_q) QUAT_ASSIGN(_q, 1., 0., 0., 0.)

/* _q += _qa */
#define FLOAT_QUAT_ADD(_qo, _qi) QUAT_ADD(_qo, _qi)

/* _qo = _qi * _s */
#define FLOAT_QUAT_SMUL(_qo, _qi, _s) QUAT_SMUL(_qo, _qi, _s)

#define FLOAT_QUAT_EXPLEMENTARY(b,a) QUAT_EXPLEMENTARY(b,a)

#define FLOAT_QUAT_COPY(_qo, _qi) QUAT_COPY(_qo, _qi)

#define FLOAT_QUAT_NORM(_q) (sqrtf(SQUARE(_q.qi) + SQUARE(_q.qx)+	\
				   SQUARE(_q.qy) + SQUARE(_q.qz)))	\
    
#define FLOAT_QUAT_NORMALISE(q) {		                        \
    float norm = FLOAT_QUAT_NORM(q);					\
    if (norm > FLT_MIN) {						\
	    q.qi = q.qi / norm;						\
      q.qx = q.qx / norm;						\
      q.qy = q.qy / norm;						\
      q.qz = q.qz / norm;						\
	  }								\
  }

#define FLOAT_QUAT_INVERT(_qo, _qi) QUAT_INVERT(_qo, _qi)

#define FLOAT_QUAT_WRAP_SHORTEST(q) {					\
    if (q.qi < 0.)							\
      QUAT_EXPLEMENTARY(q,q);						\
  }

/* _a2c = _a2b comp _b2c , aka  _a2c = _a2b * _b2c */
#define FLOAT_QUAT_COMP_NORM_SHORTEST(_a2c, _a2b, _b2c) {		\
    FLOAT_QUAT_COMP(_a2c, _a2b, _b2c);					\
    FLOAT_QUAT_WRAP_SHORTEST(_a2c);					\
    FLOAT_QUAT_NORMALISE(_a2c);						\
  }

/* _a2c = _a2b comp _b2c , aka  _a2c = _a2b * _b2c */
#define FLOAT_QUAT_COMP(_a2c, _a2b, _b2c) {				\
    (_a2c).qi = (_a2b).qi*(_b2c).qi - (_a2b).qx*(_b2c).qx - (_a2b).qy*(_b2c).qy - (_a2b).qz*(_b2c).qz; \
    (_a2c).qx = (_a2b).qi*(_b2c).qx + (_a2b).qx*(_b2c).qi + (_a2b).qy*(_b2c).qz - (_a2b).qz*(_b2c).qy; \
    (_a2c).qy = (_a2b).qi*(_b2c).qy - (_a2b).qx*(_b2c).qz + (_a2b).qy*(_b2c).qi + (_a2b).qz*(_b2c).qx; \
    (_a2c).qz = (_a2b).qi*(_b2c).qz + (_a2b).qx*(_b2c).qy - (_a2b).qy*(_b2c).qx + (_a2b).qz*(_b2c).qi; \
  }

#define FLOAT_QUAT_MULT(_a2c, _a2b, _b2c) FLOAT_QUAT_COMP(_a2c, _a2b, _b2c)

/* _a2b = _a2c comp_inv _b2c , aka  _a2b = _a2c * inv(_b2c) */
#define FLOAT_QUAT_COMP_INV_NORM_SHORTEST(_a2b, _a2c, _b2c) {		\
    FLOAT_QUAT_COMP_INV(_a2b, _a2c, _b2c);				\
    FLOAT_QUAT_WRAP_SHORTEST(_a2b);					\
    FLOAT_QUAT_NORMALISE(_a2b);						\
  }

/* _a2b = _a2c comp_inv _b2c , aka  _a2b = _a2c * inv(_b2c) */
#define FLOAT_QUAT_COMP_INV(_a2b, _a2c, _b2c) {				\
    (_a2b).qi =  (_a2c).qi*(_b2c).qi + (_a2c).qx*(_b2c).qx + (_a2c).qy*(_b2c).qy + (_a2c).qz*(_b2c).qz; \
    (_a2b).qx = -(_a2c).qi*(_b2c).qx + (_a2c).qx*(_b2c).qi - (_a2c).qy*(_b2c).qz + (_a2c).qz*(_b2c).qy; \
    (_a2b).qy = -(_a2c).qi*(_b2c).qy + (_a2c).qx*(_b2c).qz + (_a2c).qy*(_b2c).qi - (_a2c).qz*(_b2c).qx; \
    (_a2b).qz = -(_a2c).qi*(_b2c).qz - (_a2c).qx*(_b2c).qy + (_a2c).qy*(_b2c).qx + (_a2c).qz*(_b2c).qi; \
  }

/* _b2c = _a2b inv_comp _a2c , aka  _b2c = inv(_a2b) * _a2c */
#define FLOAT_QUAT_INV_COMP_NORM_SHORTEST(_b2c, _a2b, _a2c) {		\
    FLOAT_QUAT_INV_COMP(_b2c, _a2b, _a2c);				\
    FLOAT_QUAT_WRAP_SHORTEST(_b2c);					\
    FLOAT_QUAT_NORMALISE(_b2c);						\
  }

/* _b2c = _a2b inv_comp _a2c , aka  _b2c = inv(_a2b) * _a2c */
#define FLOAT_QUAT_INV_COMP(_b2c, _a2b, _a2c) {				\
    (_b2c).qi = (_a2b).qi*(_a2c).qi + (_a2b).qx*(_a2c).qx + (_a2b).qy*(_a2c).qy + (_a2b).qz*(_a2c).qz; \
    (_b2c).qx = (_a2b).qi*(_a2c).qx - (_a2b).qx*(_a2c).qi - (_a2b).qy*(_a2c).qz + (_a2b).qz*(_a2c).qy; \
    (_b2c).qy = (_a2b).qi*(_a2c).qy + (_a2b).qx*(_a2c).qz - (_a2b).qy*(_a2c).qi - (_a2b).qz*(_a2c).qx; \
    (_b2c).qz = (_a2b).qi*(_a2c).qz - (_a2b).qx*(_a2c).qy + (_a2b).qy*(_a2c).qx - (_a2b).qz*(_a2c).qi; \
  }

#define FLOAT_QUAT_DIFFERENTIAL(q_out, w, dt) {			      \
    const float v_norm = sqrt((w).p*(w).p + (w).q*(w).q + (w).r*(w).r); \
    const float c2 = cos(dt*v_norm/2.0);				\
    const float s2 = sin(dt*v_norm/2.0);				\
    if (v_norm < 1e-8) {						\
      (q_out).qi = 1;							\
      (q_out).qx = 0;							\
      (q_out).qy = 0;							\
      (q_out).qz = 0;							\
    } else {								\
      (q_out).qi = c2;							\
      (q_out).qx = (w).p/v_norm * s2;					\
      (q_out).qy = (w).q/v_norm * s2;					\
      (q_out).qz = (w).r/v_norm * s2;					\
    }									\
  }

#define FLOAT_QUAT_ROTATE_FRAME(q_out, q_in, q_rot) {                   \
    struct FloatQuat q_temp;						\
    FLOAT_QUAT_INV_COMP(q_temp, q_rot, q_in);				\
    print_quat(q_temp);							\
    FLOAT_QUAT_COMP(q_out, q_temp, q_rot);				\
  }

#define FLOAT_QUAT_VMULT(v_out, q, v_in) {				\
    const float qi2  = q.qi*q.qi;					\
    const float qiqx = q.qi*q.qx;					\
    const float qiqy = q.qi*q.qy;					\
    const float qiqz = q.qi*q.qz;					\
    const float qx2  = q.qx*q.qx;					\
    const float qxqy = q.qx*q.qy;					\
    const float qxqz = q.qx*q.qz;					\
    const float qy2  = q.qy*q.qy;					\
    const float qyqz = q.qy*q.qz;					\
    const float qz2 = q.qz*q.qz;					\
    const float m00 = qi2 + qx2 - qy2 - qz2;				\
    const float m01 = 2 * ( qxqy + qiqz );				\
    const float m02 = 2 * ( qxqz - qiqy );				\
    const float m10 = 2 * ( qxqy - qiqz );				\
    const float m11 = qi2 - qx2 + qy2 - qz2;				\
    const float m12 = 2 * ( qyqz + qiqx );				\
    const float m20 = 2 * ( qxqz + qiqy );				\
    const float m21 = 2 * ( qyqz - qiqx );				\
    const float m22 = qi2 - qx2 - qy2 + qz2;				\
    v_out.x = m00 * v_in.x + m01 * v_in.y + m02 * v_in.z;		\
    v_out.y = m10 * v_in.x + m11 * v_in.y + m12 * v_in.z;		\
    v_out.z = m20 * v_in.x + m21 * v_in.y + m22 * v_in.z;		\
  }

/* _qd = -0.5*omega(_r) * _q  */
#define FLOAT_QUAT_DERIVATIVE(_qd, _r, _q) {				\
    (_qd).qi = -0.5*( (_r).p*(_q).qx + (_r).q*(_q).qy + (_r).r*(_q).qz); \
    (_qd).qx = -0.5*(-(_r).p*(_q).qi - (_r).r*(_q).qy + (_r).q*(_q).qz); \
    (_qd).qy = -0.5*(-(_r).q*(_q).qi + (_r).r*(_q).qx - (_r).p*(_q).qz); \
    (_qd).qz = -0.5*(-(_r).r*(_q).qi - (_r).q*(_q).qx + (_r).p*(_q).qy); \
  }

/* _qd = -0.5*omega(_r) * _q  */
#define FLOAT_QUAT_DERIVATIVE_LAGRANGE(_qd, _r, _q) {			\
    const float K_LAGRANGE = 1.;					\
    const float c = K_LAGRANGE * ( 1 - FLOAT_QUAT_NORM(_q)) / -0.5;	\
    (_qd).qi = -0.5*(      c*(_q).qi + (_r).p*(_q).qx + (_r).q*(_q).qy + (_r).r*(_q).qz); \
    (_qd).qx = -0.5*(-(_r).p*(_q).qi +      c*(_q).qx - (_r).r*(_q).qy + (_r).q*(_q).qz); \
    (_qd).qy = -0.5*(-(_r).q*(_q).qi + (_r).r*(_q).qx +      c*(_q).qy - (_r).p*(_q).qz); \
    (_qd).qz = -0.5*(-(_r).r*(_q).qi - (_r).q*(_q).qx + (_r).p*(_q).qy +      c*(_q).qz); \
  }

#define FLOAT_QUAT_OF_EULERS(_q, _e) {					\
    									\
    const float phi2   = (_e).phi/2.0;					\
    const float theta2 = (_e).theta/2.0;				\
    const float psi2   = (_e).psi/2.0;					\
    									\
    const float s_phi2   = sinf( phi2 );				\
    const float c_phi2   = cosf( phi2 );				\
    const float s_theta2 = sinf( theta2 );				\
    const float c_theta2 = cosf( theta2 );				\
    const float s_psi2   = sinf( psi2 );				\
    const float c_psi2   = cosf( psi2 );				\
									\
    (_q).qi =  c_phi2 * c_theta2 * c_psi2 + s_phi2 * s_theta2 * s_psi2; \
    (_q).qx = -c_phi2 * s_theta2 * s_psi2 + s_phi2 * c_theta2 * c_psi2; \
    (_q).qy =  c_phi2 * s_theta2 * c_psi2 + s_phi2 * c_theta2 * s_psi2; \
    (_q).qz =  c_phi2 * c_theta2 * s_psi2 - s_phi2 * s_theta2 * c_psi2; \
    									\
  }

#define FLOAT_QUAT_OF_AXIS_ANGLE(_q, _uv, _an) {		\
    const float san = sinf(_an/2.);				\
    _q.qi = cosf(_an/2.);					\
    _q.qx = san * _uv.x;					\
    _q.qy = san * _uv.y;					\
    _q.qz = san * _uv.z;					\
  }

#define FLOAT_QUAT_OF_RMAT(_q, _r) {					\
    const float tr = RMAT_TRACE(_r);					\
    if (tr > 0) {							\
      const float two_qi = sqrtf(1.+tr);				\
      const float four_qi = 2. * two_qi;				\
      _q.qi = 0.5 * two_qi;						\
      _q.qx =  (RMAT_ELMT(_r, 1, 2)-RMAT_ELMT(_r, 2, 1))/four_qi;	\
      _q.qy =  (RMAT_ELMT(_r, 2, 0)-RMAT_ELMT(_r, 0, 2))/four_qi;	\
      _q.qz =  (RMAT_ELMT(_r, 0, 1)-RMAT_ELMT(_r, 1, 0))/four_qi;	\
      /*printf("tr > 0\n");*/						\
    }									\
    else {								\
      if (RMAT_ELMT(_r, 0, 0) > RMAT_ELMT(_r, 1, 1) &&			\
	  RMAT_ELMT(_r, 0, 0) > RMAT_ELMT(_r, 2, 2)) {			\
	const float two_qx = sqrtf(RMAT_ELMT(_r, 0, 0) -RMAT_ELMT(_r, 1, 1) \
				   -RMAT_ELMT(_r, 2, 2) + 1);		\
	const float four_qx = 2. * two_qx;				\
	_q.qi = (RMAT_ELMT(_r, 1, 2)-RMAT_ELMT(_r, 2, 1))/four_qx;	\
	_q.qx = 0.5 * two_qx;						\
	_q.qy = (RMAT_ELMT(_r, 0, 1)+RMAT_ELMT(_r, 1, 0))/four_qx;	\
	_q.qz = (RMAT_ELMT(_r, 2, 0)+RMAT_ELMT(_r, 0, 2))/four_qx;	\
	/*printf("m00 largest\n");*/					\
      }									\
      else if (RMAT_ELMT(_r, 1, 1) > RMAT_ELMT(_r, 2, 2)) {		\
	const float two_qy =						\
	  sqrtf(RMAT_ELMT(_r, 1, 1) - RMAT_ELMT(_r, 0, 0) - RMAT_ELMT(_r, 2, 2) + 1); \
	const float four_qy = 2. * two_qy;				\
	_q.qi = (RMAT_ELMT(_r, 2, 0) - RMAT_ELMT(_r, 0, 2))/four_qy;	\
	_q.qx = (RMAT_ELMT(_r, 0, 1) + RMAT_ELMT(_r, 1, 0))/four_qy;	\
	_q.qy = 0.5 * two_qy;						\
	_q.qz = (RMAT_ELMT(_r, 1, 2) + RMAT_ELMT(_r, 2, 1))/four_qy;	\
	/*printf("m11 largest\n");*/					\
      }									\
      else {								\
	const float two_qz =						\
	  sqrtf(RMAT_ELMT(_r, 2, 2) - RMAT_ELMT(_r, 0, 0) - RMAT_ELMT(_r, 1, 1) + 1); \
	const float four_qz = 2. * two_qz;				\
	_q.qi = (RMAT_ELMT(_r, 0, 1)- RMAT_ELMT(_r, 1, 0))/four_qz;	\
	_q.qx = (RMAT_ELMT(_r, 2, 0)+ RMAT_ELMT(_r, 0, 2))/four_qz;	\
	_q.qy = (RMAT_ELMT(_r, 1, 2)+ RMAT_ELMT(_r, 2, 1))/four_qz;	\
	_q.qz = 0.5 * two_qz;						\
     	/*printf("m22 largest\n");*/					\
      }									\
    }									\
  }


/*
 *  Euler angles
 */

#define FLOAT_EULERS_ZERO(_e) EULERS_ASSIGN(_e, 0., 0., 0.);

#define FLOAT_EULERS_NORM(_e) (sqrtf(SQUARE((_e).phi)+SQUARE((_e).theta)+SQUARE((_e).psi))) ;

#define FLOAT_EULERS_OF_RMAT(_e, _rm) {					\
    									\
    const float dcm00 = (_rm).m[0];					\
    const float dcm01 = (_rm).m[1];					\
    const float dcm02 = (_rm).m[2];					\
    const float dcm12 = (_rm).m[5];					\
    const float dcm22 = (_rm).m[8];					\
    (_e).phi   = atan2f( dcm12, dcm22 );				\
    (_e).theta = -asinf( dcm02 );					\
    (_e).psi   = atan2f( dcm01, dcm00 );				\
									\
  }

#define FLOAT_EULERS_OF_QUAT(_e, _q) {					\
									\
    const float qx2  = (_q).qx*(_q).qx;					\
    const float qy2  = (_q).qy*(_q).qy;					\
    const float qz2  = (_q).qz*(_q).qz;					\
    const float qiqx = (_q).qi*(_q).qx;					\
    const float qiqy = (_q).qi*(_q).qy;					\
    const float qiqz = (_q).qi*(_q).qz;					\
    const float qxqy = (_q).qx*(_q).qy;					\
    const float qxqz = (_q).qx*(_q).qz;					\
    const float qyqz = (_q).qy*(_q).qz;					\
    const float dcm00 = 1.0 - 2.*(  qy2 +  qz2 );			\
    const float dcm01 =       2.*( qxqy + qiqz );			\
    const float dcm02 =       2.*( qxqz - qiqy );			\
    const float dcm12 =       2.*( qyqz + qiqx );			\
    const float dcm22 = 1.0 - 2.*(  qx2 +  qy2 );			\
									\
    (_e).phi = atan2f( dcm12, dcm22 );					\
    (_e).theta = -asinf( dcm02 );					\
    (_e).psi = atan2f( dcm01, dcm00 );					\
									\
  }





#endif /* PPRZ_ALGEBRA_FLOAT_H */
