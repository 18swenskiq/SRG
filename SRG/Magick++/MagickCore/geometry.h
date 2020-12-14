/*
  Copyright 1999-2020 ImageMagick Studio LLC, a non-profit organization
  dedicated to making software imaging solutions freely available.

  You may not use this file except in compliance with the License.  You may
  obtain a copy of the License at

    https://imagemagick.org/script/license.php

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  MagickCore image geometry methods.
*/
#ifndef MAGICKCORE_GEOMETRY_H
#define MAGICKCORE_GEOMETRY_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef enum
{
#undef NoValue
  NoValue = 0x0000,
#undef XValue
  XValue = 0x0001,
  XiValue = 0x0001,
#undef YValue
  YValue = 0x0002,
  PsiValue = 0x0002,
#undef WidthValue
  WidthValue = 0x0004,
  RhoValue = 0x0004,
#undef HeightValue
  HeightValue = 0x0008,
  SigmaValue = 0x0008,
  ChiValue = 0x0010,
  XiNegative = 0x0020,
#undef XNegative
  XNegative = 0x0020,
  PsiNegative = 0x0040,
#undef YNegative
  YNegative = 0x0040,
  ChiNegative = 0x0080,
  PercentValue = 0x1000,    /* '%'  percentage of something */
  AspectValue = 0x2000,     /* '!'  resize no-aspect - special use flag */
  NormalizeValue = 0x2000,  /* '!'  ScaleKernelValue() in morphology.c */
  LessValue = 0x4000,       /* '<'  resize smaller - special use flag */
  GreaterValue = 0x8000,    /* '>'  resize larger - spacial use flag */
  MinimumValue = 0x10000,   /* '^'  special handling needed */
  CorrelateNormalizeValue = 0x10000, /* '^' see ScaleKernelValue() */
  AreaValue = 0x20000,      /* '@'  resize to area - special use flag */
  DecimalValue = 0x40000,   /* '.'  floating point numbers found */
  SeparatorValue = 0x80000, /* 'x'  separator found  */
  AspectRatioValue = 0x100000,    /* '~'  special handling needed  */
#undef AllValues
  AllValues = 0x7fffffff
} GeometryFlags;

#if defined(ForgetGravity)
#undef ForgetGravity
#undef NorthWestGravity
#undef NorthGravity
#undef NorthEastGravity
#undef WestGravity
#undef CenterGravity
#undef EastGravity
#undef SouthWestGravity
#undef SouthGravity
#undef SouthEastGravity
#endif

typedef enum
{
  UndefinedGravity,
  ForgetGravity = 0,
  NorthWestGravity = 1,
  NorthGravity = 2,
  NorthEastGravity = 3,
  WestGravity = 4,
  CenterGravity = 5,
  EastGravity = 6,
  SouthWestGravity = 7,
  SouthGravity = 8,
  SouthEastGravity = 9
} GravityType;

typedef struct _AffineMatrix
{
  double
    sx,
    rx,
    ry,
    sy,
    tx,
    ty;
} AffineMatrix;

typedef struct _GeometryInfo
{
  double
    rho,
    sigma,
    xi,
    psi,
    chi;
} GeometryInfo;

typedef struct _OffsetInfo
{
  ssize_t
    x,
    y;
} OffsetInfo;

typedef struct _PointInfo
{
  double
    x,
    y;
} PointInfo;

typedef struct _RectangleInfo
{
  size_t
    width,
    height;

  ssize_t
    x,
    y;
} RectangleInfo;

char *GetPageGeometry(const char *);

MagickBooleanType IsGeometry(const char*);
MagickBooleanType IsSceneGeometry(const char *,const MagickBooleanType);

MagickStatusType GetGeometry(const char*, ssize_t*, ssize_t*, size_t*, size_t*);
MagickStatusType ParseAbsoluteGeometry(const char*, RectangleInfo*);
MagickStatusType ParseAffineGeometry(const char*, AffineMatrix*, ExceptionInfo*);
MagickStatusType ParseGeometry(const char*, GeometryInfo*);
MagickStatusType ParseGravityGeometry(const Image*, const char*, RectangleInfo*, ExceptionInfo*);
MagickStatusType ParseMetaGeometry(const char*, ssize_t*, ssize_t*, size_t*, size_t*);
MagickStatusType ParsePageGeometry(const Image*, const char*, RectangleInfo*, ExceptionInfo*);
MagickStatusType ParseRegionGeometry(const Image*, const char*, RectangleInfo*, ExceptionInfo*);

void GravityAdjustGeometry(const size_t, const size_t, const GravityType, RectangleInfo*);
void SetGeometry(const Image*, RectangleInfo*);
void SetGeometryInfo(GeometryInfo *);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
