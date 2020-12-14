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

  MagickCore memory methods.
*/
#ifndef MAGICKCORE_MEMORY_H
#define MAGICKCORE_MEMORY_H

#include <errno.h>
#include <assert.h>


typedef struct _MemoryInfo
  MemoryInfo;

typedef void
  *(*AcquireMemoryHandler)(size_t) magick_alloc_size(1),
  (*DestroyMemoryHandler)(void *),
  *(*ResizeMemoryHandler)(void *,size_t) magick_alloc_size(2),
  *(*AcquireAlignedMemoryHandler)(const size_t,const size_t),
  (*RelinquishAlignedMemoryHandler)(void *);

MemoryInfo* AcquireVirtualMemory(const size_t, const size_t) magick_alloc_sizes(1, 2);
MemoryInfo* RelinquishVirtualMemory(MemoryInfo*);

size_t GetMaxMemoryRequest(void);

void* AcquireAlignedMemory(const size_t, const size_t) magick_attribute((__malloc__)) magick_alloc_sizes(1, 2);
void* AcquireMagickMemory(const size_t) magick_attribute((__malloc__)) magick_alloc_size(1);
void* AcquireCriticalMemory(const size_t);
void* AcquireQuantumMemory(const size_t, const size_t) magick_attribute((__malloc__)) magick_alloc_sizes(1, 2);
void* CopyMagickMemory(void* magick_restrict, const void* magick_restrict, const size_t) magick_attribute((__nonnull__));
void DestroyMagickMemory(void);
void GetMagickMemoryMethods(AcquireMemoryHandler*, ResizeMemoryHandler*, DestroyMemoryHandler*);
void* GetVirtualMemoryBlob(const MemoryInfo*);
void* RelinquishAlignedMemory(void*);
void* RelinquishMagickMemory(void*);
void* ResetMagickMemory(void*, int, const size_t);
void* ResizeMagickMemory(void*, const size_t) magick_attribute((__malloc__)) magick_alloc_size(2);
void* ResizeQuantumMemory(void*, const size_t, const size_t) magick_attribute((__malloc__)) magick_alloc_sizes(2, 3);
void SetMagickAlignedMemoryMethods(AcquireAlignedMemoryHandler, RelinquishAlignedMemoryHandler);
void SetMagickMemoryMethods(AcquireMemoryHandler,ResizeMemoryHandler, DestroyMemoryHandler);

static inline MagickBooleanType HeapOverflowSanityCheck(const size_t count,const size_t quantum)
{
  if ((count == 0) || (quantum == 0))
    return(MagickTrue);
  if (quantum != ((count*quantum)/count))
    {
      errno=ENOMEM;
      return(MagickTrue);
    }
  return(MagickFalse);
}

static inline MagickBooleanType HeapOverflowSanityCheckGetSize(
  const size_t count,const size_t quantum,size_t *const extent)
{
  size_t
    length;

  if ((count == 0) || (quantum == 0))
    return(MagickTrue);
  length=count*quantum;
  if (quantum != (length/count))
    {
      errno=ENOMEM;
      return(MagickTrue);
    }
  assert(extent != NULL);
  *extent=length;
  return(MagickFalse);
}


#endif
