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

  MagickCore cache view methods.
*/
#ifndef MAGICKCORE_CACHE_VIEW_H
#define MAGICKCORE_CACHE_VIEW_H

#include "./pixel.h"

typedef enum
{
  UndefinedVirtualPixelMethod,
  BackgroundVirtualPixelMethod,
  DitherVirtualPixelMethod,
  EdgeVirtualPixelMethod,
  MirrorVirtualPixelMethod,
  RandomVirtualPixelMethod,
  TileVirtualPixelMethod,
  TransparentVirtualPixelMethod,
  MaskVirtualPixelMethod,
  BlackVirtualPixelMethod,
  GrayVirtualPixelMethod,
  WhiteVirtualPixelMethod,
  HorizontalTileVirtualPixelMethod,
  VerticalTileVirtualPixelMethod,
  HorizontalTileEdgeVirtualPixelMethod,
  VerticalTileEdgeVirtualPixelMethod,
  CheckerTileVirtualPixelMethod
} VirtualPixelMethod;

typedef struct _CacheView
  CacheView;

CacheView* AcquireAuthenticCacheView(const Image*, ExceptionInfo*);
CacheView* AcquireVirtualCacheView(const Image*, ExceptionInfo*);
CacheView* CloneCacheView(const CacheView*);
CacheView* DestroyCacheView(CacheView*);

ClassType GetCacheViewStorageClass(const CacheView *) magick_attribute((__pure__));

ColorspaceType GetCacheViewColorspace(const CacheView *) magick_attribute((__pure__));

Image *GetCacheViewImage(const CacheView *) magick_attribute((__pure__));

const Quantum* GetCacheViewVirtualPixels(const CacheView*, const ssize_t, const ssize_t, const size_t, const size_t, ExceptionInfo*) magick_hot_spot;
const Quantum *GetCacheViewVirtualPixelQueue(const CacheView *) magick_hot_spot;

const void *GetCacheViewVirtualMetacontent(const CacheView *) magick_attribute((__pure__));

MagickBooleanType GetOneCacheViewAuthenticPixel(const CacheView*, const ssize_t, const ssize_t, Quantum*, ExceptionInfo*);
MagickBooleanType GetOneCacheViewVirtualMethodPixel(const CacheView*, const VirtualPixelMethod, const ssize_t, const ssize_t, Quantum*, ExceptionInfo*);
MagickBooleanType GetOneCacheViewVirtualPixel(const CacheView*, const ssize_t, const ssize_t, Quantum*, ExceptionInfo*);
MagickBooleanType GetOneCacheViewVirtualPixelInfo(const CacheView*, const ssize_t, const ssize_t, PixelInfo*, ExceptionInfo*);
MagickBooleanType SetCacheViewStorageClass(CacheView*, const ClassType, ExceptionInfo*);
MagickBooleanType SetCacheViewVirtualPixelMethod(CacheView* magick_restrict, const VirtualPixelMethod);
MagickBooleanType SyncCacheViewAuthenticPixels(CacheView *magick_restrict,ExceptionInfo *) magick_hot_spot;

MagickSizeType GetCacheViewExtent(const CacheView *) magick_attribute((__pure__));

Quantum* GetCacheViewAuthenticPixelQueue(CacheView*) magick_hot_spot;
Quantum* GetCacheViewAuthenticPixels(CacheView*, const ssize_t, const ssize_t, const size_t, const size_t, ExceptionInfo*) magick_hot_spot;
Quantum *QueueCacheViewAuthenticPixels(CacheView *,const ssize_t,const ssize_t, const size_t,const size_t,ExceptionInfo *) magick_hot_spot;

void *GetCacheViewAuthenticMetacontent(CacheView *);


#endif
