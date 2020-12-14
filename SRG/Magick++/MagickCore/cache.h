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

  MagickCore cache methods.
*/
#ifndef MAGICKCORE_CACHE_H
#define MAGICKCORE_CACHE_H

#include "./blob.h"

typedef enum
{
  UndefinedCache,
  DiskCache,
  DistributedCache,
  MapCache,
  MemoryCache,
  PingCache
} CacheType;

CacheType GetImagePixelCacheType(const Image *);

const char *GetPixelCacheFilename(const Image *);

const Quantum* GetVirtualPixels(const Image*, const ssize_t, const ssize_t, const size_t, const size_t, ExceptionInfo*) magick_hot_spot;
const Quantum *GetVirtualPixelQueue(const Image *) magick_hot_spot;

const void *GetVirtualMetacontent(const Image *);

MagickBooleanType GetOneAuthenticPixel(Image*, const ssize_t, const ssize_t, Quantum*, ExceptionInfo*);
MagickBooleanType GetOneVirtualPixel(const Image*, const ssize_t, const ssize_t, Quantum*, ExceptionInfo*);
MagickBooleanType GetOneVirtualPixelInfo(const Image*, const VirtualPixelMethod, const ssize_t, const ssize_t, PixelInfo*, ExceptionInfo*);
MagickBooleanType PersistPixelCache(Image*, const char*, const MagickBooleanType, MagickOffsetType*, ExceptionInfo*);
MagickBooleanType SyncAuthenticPixels(Image *,ExceptionInfo *) magick_hot_spot;

MagickSizeType GetImageExtent(const Image *);

extern MagickExport Quantum
Quantum* GetAuthenticPixels(Image*, const ssize_t, const ssize_t, const size_t, const size_t, ExceptionInfo*) magick_hot_spot;
Quantum* GetAuthenticPixelQueue(const Image*) magick_hot_spot;
Quantum *QueueAuthenticPixels(Image *,const ssize_t,const ssize_t,const size_t, const size_t,ExceptionInfo *) magick_hot_spot;

void* AcquirePixelCachePixels(const Image*, size_t*, ExceptionInfo*);
void* GetAuthenticMetacontent(const Image*);
void *GetPixelCachePixels(Image *,MagickSizeType *,ExceptionInfo *);

#endif
