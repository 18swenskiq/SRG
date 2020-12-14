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

  MagickCore image methods.
*/
#ifndef MAGICKCORE_IMAGE_H
#define MAGICKCORE_IMAGE_H

#define OpaqueAlpha  ((Quantum) QuantumRange)
#define TransparentAlpha  ((Quantum) 0)

typedef enum
{
  UndefinedAlphaChannel,
  ActivateAlphaChannel,
  AssociateAlphaChannel,
  BackgroundAlphaChannel,
  CopyAlphaChannel,
  DeactivateAlphaChannel,
  DiscreteAlphaChannel,
  DisassociateAlphaChannel,
  ExtractAlphaChannel,
  OffAlphaChannel,
  OnAlphaChannel,
  OpaqueAlphaChannel,
  RemoveAlphaChannel,
  SetAlphaChannel,
  ShapeAlphaChannel,
  TransparentAlphaChannel
} AlphaChannelOption;

typedef enum
{
  UndefinedType,
  BilevelType,
  GrayscaleType,
  GrayscaleAlphaType,
  PaletteType,
  PaletteAlphaType,
  TrueColorType,
  TrueColorAlphaType,
  ColorSeparationType,
  ColorSeparationAlphaType,
  OptimizeType,
  PaletteBilevelAlphaType
} ImageType;

typedef enum
{
  UndefinedInterlace,
  NoInterlace,
  LineInterlace,
  PlaneInterlace,
  PartitionInterlace,
  GIFInterlace,
  JPEGInterlace,
  PNGInterlace
} InterlaceType;

typedef enum
{
  UndefinedOrientation,
  TopLeftOrientation,
  TopRightOrientation,
  BottomRightOrientation,
  BottomLeftOrientation,
  LeftTopOrientation,
  RightTopOrientation,
  RightBottomOrientation,
  LeftBottomOrientation
} OrientationType;

typedef enum
{
  UndefinedResolution,
  PixelsPerInchResolution,
  PixelsPerCentimeterResolution
} ResolutionType;

typedef struct _PrimaryInfo
{
  double
    x,
    y,
    z;
} PrimaryInfo;

typedef struct _SegmentInfo
{
  double
    x1,
    y1,
    x2,
    y2;
} SegmentInfo;

typedef enum
{
  UndefinedTransmitType,
  FileTransmitType,
  BlobTransmitType,
  StreamTransmitType,
  ImageTransmitType
} TransmitType;

typedef struct _ChromaticityInfo
{
  PrimaryInfo
    red_primary,
    green_primary,
    blue_primary,
    white_point;
} ChromaticityInfo;

#include "./blob.h"
#include "./colorspace.h"
#include "./cache-view.h"
#include "./color.h"
#include "./composite.h"
#include "./compress.h"
#include "./effect.h"
#include "./geometry.h"
#include "./layer.h"
#include "./locale_.h"
#include "./monitor.h"
#include "./pixel.h"
#include "./profile.h"
#include "./quantum.h"
#include "./resample.h"
#include "./resize.h"
#include "./semaphore.h"
#include "./stream.h"
#include "./timer.h"

struct _Image
{
  ClassType
    storage_class;

  ColorspaceType
    colorspace;         /* colorspace of image data */

  CompressionType
    compression;        /* compression of image when read/write */

  size_t
    quality;            /* compression quality setting, meaning varies */

  OrientationType
    orientation;        /* photo orientation of image */

  MagickBooleanType
    taint;              /* has image been modified since reading */

  size_t
    columns,            /* physical size of image */
    rows,
    depth,              /* depth of image on read/write */
    colors;             /* Size of color table, or actual color count */
                        /* Only valid if image is not DirectClass */

  PixelInfo
    *colormap,
    alpha_color,        /* deprecated */
    background_color,   /* current background color attribute */
    border_color,       /* current bordercolor attribute */
    transparent_color;  /* color for 'transparent' color index in GIF */

  double
    gamma;

  ChromaticityInfo
    chromaticity;

  RenderingIntent
    rendering_intent;

  void
    *profiles;

  ResolutionType
    units;          /* resolution/density  ppi or ppc */

  char
    *montage,
    *directory,
    *geometry;

  ssize_t
    offset;         /* ??? */

  PointInfo
    resolution;     /* image resolution/density */

  RectangleInfo
    page,           /* virtual canvas size and offset of image */
    extract_info;

  double
    fuzz;           /* current color fuzz attribute - move to image_info */

  FilterType
    filter;         /* resize/distort filter to apply */

  PixelIntensityMethod
    intensity;      /* method to generate an intensity value from a pixel */

  InterlaceType
    interlace;

  EndianType
    endian;         /* raw data integer ordering on read/write */

  GravityType
    gravity;        /* Gravity attribute for positioning in image */

  CompositeOperator
    compose;        /* alpha composition method for layered images */

  DisposeType
    dispose;        /* GIF animation disposal method */

  size_t
    scene,          /* index of image in multi-image file */
    delay,          /* Animation delay time */
    duration;       /* Total animation duration sum(delay*iterations) */

  ssize_t
    ticks_per_second;  /* units for delay time, default 100 for GIF */

  size_t
    iterations,        /* number of interations for GIF animations */
    total_colors;

  ssize_t
    start_loop;        /* ??? */

  PixelInterpolateMethod
    interpolate;       /* Interpolation of color for between pixel lookups */

  MagickBooleanType
    black_point_compensation;

  RectangleInfo
    tile_offset;

  ImageType
    type;

  MagickBooleanType
    dither;            /* dithering on/off */

  MagickSizeType
    extent;            /* Size of image read from disk */

  MagickBooleanType
    ping;              /* no image data read, just attributes */

  MagickBooleanType
    read_mask,
    write_mask;

  PixelTrait
    alpha_trait;       /* is transparency channel defined and active */

  size_t
    number_channels,
    number_meta_channels,
    metacontent_extent;

  ChannelType
    channel_mask;

  PixelChannelMap
    *channel_map;

  void
    *cache;

  ErrorInfo
    error;

  TimerInfo
    timer;

  MagickProgressMonitor
    progress_monitor;

  void
    *client_data;

  Ascii85Info
    *ascii85;

  ProfileInfo
    *generic_profile;

  void
    *properties,       /* general settings, to save with image */
    *artifacts;        /* general operational/coder settings, not saved */

  char
    filename[MagickPathExtent],        /* images input filename */
    magick_filename[MagickPathExtent], /* given image filename (with read mods) */
    magick[MagickPathExtent];          /* images file format (file magic) */

  size_t
    magick_columns,     /* size of image when read/created */
    magick_rows;

  BlobInfo
    *blob;             /* image file as in-memory string of 'extent' */

  time_t
    timestamp;

  MagickBooleanType
    debug;             /* debug output attribute */

  volatile ssize_t
    reference_count;   /* image data sharing memory management */

  SemaphoreInfo
    *semaphore;

  struct _ImageInfo
    *image_info;       /* (Optional) Image belongs to this ImageInfo 'list'
                        * For access to 'global options' when no per-image
                        * attribute, properity, or artifact has been set.
                        */

  struct _Image
    *list,             /* Undo/Redo image processing list (for display) */
    *previous,         /* Image list links */
    *next;

  size_t
    signature;

  PixelInfo
    matte_color;        /* current mattecolor attribute */

  MagickBooleanType
    composite_mask;

  PixelTrait
    mask_trait;       /* apply the clip or composite mask */

  ChannelType
    channels;
};

/*
  ImageInfo structure:
    Stores an image list, as well as all global settings used by all images
    held, -- unless overridden for that specific image.  See SyncImagesettings()
    which maps any global setting that always overrides specific image settings.
*/
struct _ImageInfo
{
  CompressionType
    compression;        /* compression method when reading/saving image */

  OrientationType
    orientation;        /* orientation setting */

  MagickBooleanType
    temporary,          /* image file to be deleted after read "empemeral:" */
    adjoin,             /* save images to separate scene files */
    affirm,
    antialias;

  char
    *size,              /* image generation size */
    *extract,           /* crop/resize string on image read */
    *page,
    *scenes;            /* scene numbers that is to be read in */

  size_t
    scene,              /* starting value for image save numbering */
    number_scenes,      /* total number of images in list - for escapes */
    depth;              /* current read/save depth of images */

  InterlaceType
    interlace;          /* interlace for image write */

  EndianType
    endian;             /* integer endian order for raw image data */

  ResolutionType
    units;              /* denisty pixels/inch or pixel/cm */

  size_t
    quality;            /* compression quality */

  char
    *sampling_factor,   /* JPEG write sampling factor */
    *server_name,       /* X windows server name - display/animate */
    *font,              /* DUP for draw_info */
    *texture,           /* montage/display background tile */
    *density;           /* DUP for image and draw_info */

  double
    pointsize,
    fuzz;               /* current color fuzz attribute */

  PixelInfo
    alpha_color,        /* deprecated */
    background_color,   /* user set background color */
    border_color,       /* user set border color */
    transparent_color;  /* color for transparent index in color tables */
                        /* NB: fill color is only needed in draw_info! */
                        /* the same for undercolor (for font drawing) */

  MagickBooleanType
    dither,             /* dither enable-disable */
    monochrome;         /* read/write pcl,pdf,ps,xps as monocrome image */

  ColorspaceType
    colorspace;

  CompositeOperator
    compose;

  ImageType
    type;

  MagickBooleanType
    ping,                    /* fast read image attributes, not image data */
    verbose;                 /* verbose output enable/disable */

  ChannelType
    channel;

  void
    *options;                /* splay tree of global options */

  void
    *profile;

  MagickBooleanType
    synchronize;

  MagickProgressMonitor
    progress_monitor;

  void
    *client_data,
    *cache;

  StreamHandler
    stream;

  FILE
    *file;

  void
    *blob;

  size_t
    length;

  char
    magick[MagickPathExtent],    /* image file format (file magick) */
    unique[MagickPathExtent],    /* unique tempory filename - delegates */
    filename[MagickPathExtent];  /* filename when reading/writing image */

  MagickBooleanType
    debug;

  size_t
    signature;

  CustomStreamInfo
    *custom_stream;

  PixelInfo
    matte_color;        /* matte (frame) color */
};

ChannelType SetImageChannelMask(Image *,const ChannelType);

ExceptionType CatchImageException(Image *);

FILE *GetImageInfoFile(const ImageInfo *);

Image* AcquireImage(const ImageInfo*, ExceptionInfo*);
Image* AppendImages(const Image*, const MagickBooleanType, ExceptionInfo*);
Image* CloneImage(const Image*, const size_t, const size_t, const MagickBooleanType, ExceptionInfo*);
Image* DestroyImage(Image*);
Image* GetImageMask(const Image*, const PixelMask, ExceptionInfo*);
Image* NewMagickImage(const ImageInfo*, const size_t, const size_t, const PixelInfo*, ExceptionInfo*);
Image* ReferenceImage(Image*);
Image *SmushImages(const Image *,const MagickBooleanType,const ssize_t, ExceptionInfo *);

ImageInfo* AcquireImageInfo(void);
ImageInfo* CloneImageInfo(const ImageInfo*);
ImageInfo* DestroyImageInfo(ImageInfo*);

MagickBooleanType ClipImage(Image*, ExceptionInfo*);
MagickBooleanType ClipImagePath(Image*, const char*, const MagickBooleanType, ExceptionInfo*);
MagickBooleanType CopyImagePixels(Image*, const Image*, const RectangleInfo*, const OffsetInfo*, ExceptionInfo*);
MagickBooleanType IsTaintImage(const Image*);
MagickBooleanType IsHighDynamicRangeImage(const Image*, ExceptionInfo*);
MagickBooleanType IsImageObject(const Image*);
MagickBooleanType ListMagickInfo(FILE*, ExceptionInfo*);
MagickBooleanType ModifyImage(Image**, ExceptionInfo*);
MagickBooleanType ResetImagePage(Image*, const char*);
MagickBooleanType ResetImagePixels(Image*, ExceptionInfo*);
MagickBooleanType SetImageAlpha(Image*, const Quantum, ExceptionInfo*);
MagickBooleanType SetImageBackgroundColor(Image*, ExceptionInfo*);
MagickBooleanType SetImageColor(Image*, const PixelInfo*, ExceptionInfo*);
MagickBooleanType SetImageExtent(Image*, const size_t, const size_t, ExceptionInfo*);
MagickBooleanType SetImageInfo(ImageInfo*, const unsigned int, ExceptionInfo*);
MagickBooleanType SetImageMask(Image*, const PixelMask type, const Image*, ExceptionInfo*);
MagickBooleanType SetImageRegionMask(Image*, const PixelMask type, const RectangleInfo*, ExceptionInfo*);
MagickBooleanType SetImageStorageClass(Image*, const ClassType, ExceptionInfo*);
MagickBooleanType StripImage(Image*, ExceptionInfo*);
MagickBooleanType SyncImage(Image*, ExceptionInfo*);
MagickBooleanType SyncImageSettings(const ImageInfo*, Image*, ExceptionInfo*);
MagickBooleanType SyncImagesSettings(ImageInfo *,Image *,ExceptionInfo *);

size_t InterpretImageFilename(const ImageInfo *,Image *,const char *,int,char *, ExceptionInfo *);

ssize_t GetImageReferenceCount(Image *);

VirtualPixelMethod GetImageVirtualPixelMethod(const Image*);
VirtualPixelMethod SetImageVirtualPixelMethod(Image *,const VirtualPixelMethod,ExceptionInfo *);

void AcquireNextImage(const ImageInfo*, Image*, ExceptionInfo*);
void DestroyImagePixels(Image*);
void DisassociateImageStream(Image*);
void GetImageInfo(ImageInfo*);
void SetImageInfoBlob(ImageInfo*, const void*, const size_t);
void SetImageInfoFile(ImageInfo*, FILE*);
void SetImageInfoCustomStream(ImageInfo *,CustomStreamInfo *);

#endif
