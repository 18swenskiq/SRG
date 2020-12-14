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

  MagickCore Binary Large OBjects methods.
*/
#ifndef MAGICKCORE_BLOB_H
#define MAGICKCORE_BLOB_H

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#define MagickMaxBufferExtent  81920
#define MagickMinBufferExtent  16384

typedef enum
{
  ReadMode,
  WriteMode,
  IOMode,
  PersistMode
} MapMode;

typedef ssize_t
  (*CustomStreamHandler)(unsigned char *,const size_t,void *);

typedef MagickOffsetType
  (*CustomStreamSeeker)(const MagickOffsetType,const int,void *);

typedef MagickOffsetType
  (*CustomStreamTeller)(void *);

typedef struct _CustomStreamInfo
CustomStreamInfo;

#include "./image.h"
#include "./stream.h"

CustomStreamInfo *AcquireCustomStreamInfo(ExceptionInfo *);
CustomStreamInfo *DestroyCustomStreamInfo(CustomStreamInfo *);

FILE *GetBlobFileHandle(const Image *) magick_attribute((__pure__));

Image *BlobToImage(const ImageInfo*, const void*, const size_t, ExceptionInfo*);
Image *PingBlob(const ImageInfo*, const void*, const size_t, ExceptionInfo*);
Image *CustomStreamToImage(const ImageInfo*, ExceptionInfo*);

MagickBooleanType BlobToFile(char*, const void*, const size_t, ExceptionInfo*);
MagickBooleanType FileToImage(Image*, const char*, ExceptionInfo*);
MagickBooleanType GetBlobError(const Image*) magick_attribute((__pure__));
MagickBooleanType ImageToFile(Image*, char*, ExceptionInfo*);
MagickBooleanType InjectImageBlob(const ImageInfo*, Image*, Image*, const char*, ExceptionInfo*);
MagickBooleanType IsBlobExempt(const Image*) magick_attribute((__pure__));
MagickBooleanType IsBlobSeekable(const Image*) magick_attribute((__pure__));
MagickBooleanType IsBlobTemporary(const Image *) magick_attribute((__pure__));

MagickSizeType GetBlobSize(const Image *);

StreamHandler GetBlobStreamHandler(const Image *) magick_attribute((__pure__));

void* GetBlobStreamData(const Image*) magick_attribute((__pure__));
void DestroyBlob(Image*);
void DuplicateBlob(Image*, const Image*);
void* FileToBlob(const char*, const size_t, size_t*, ExceptionInfo*);
void* ImageToBlob(const ImageInfo*, Image*, size_t*, ExceptionInfo*);
void ImageToCustomStream(const ImageInfo*, Image*, ExceptionInfo*);
void* ImagesToBlob(const ImageInfo*, Image*, size_t*, ExceptionInfo*);
void ImagesToCustomStream(const ImageInfo*, Image*, ExceptionInfo*);
void SetBlobExempt(Image*, const MagickBooleanType);
void SetCustomStreamData(CustomStreamInfo*, void*);
void SetCustomStreamReader(CustomStreamInfo*, CustomStreamHandler);
void SetCustomStreamSeeker(CustomStreamInfo*, CustomStreamSeeker);
void SetCustomStreamTeller(CustomStreamInfo*, CustomStreamTeller);
void SetCustomStreamWriter(CustomStreamInfo *,CustomStreamHandler);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif
