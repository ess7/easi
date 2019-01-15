/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// (C) 1999 Emagic Soft- und Hardware GmbH
// All rights are reserved. Reproduction in whole or in part is prohibited
// without the written consent of the copyright owner.
//
// Emagic reserves the right to make changes without notice at any time.
// Emagic makes no warranty, expressed, implied or statutory, including but
// not limited to any implied warranty of merchantibility of fitness for any
// particular purpose, or that the use will not infringe any third party
// patent, copyright or trademark. Emagic must not be liable for any loss
// or damage arising from its use.
// -----------------------------------------------------------------------------
// File:        EASI.hpp
// Description: EASI - enhanced audio streaming interface.
// History:     Felix Bertram, 23-Feb-99, Created.
//              Felix Bertram, 19-May-99, Version 1.0
/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8

#ifndef __EASI_HPP__
#define __EASI_HPP__

//==============================================================================
// * * *   b a s i c   t y p e s   &   f o r w a r d s   * * * * * * * * * * * *
//==============================================================================

#define EASIversion           1                   // EASI API version

class EASIplugin;                                 // generic EASI plugin class
class EASIhost;                                   // generic EASI host class
class EASIctorInfo;                               // generic EASI construction info
class EASIdlgInfo;                                // EASI dialog box info

typedef void*                 EASIhandle;         // callback handle
typedef long                  EASIframes;         // # of samples/ frames
typedef long                  EASIindex;          // # of channels, samplerates etc.
typedef unsigned long         EASIiomask;         // mask w/ activity bits
typedef float                 EASIvolume;         // volumes
typedef long                  EASIsrate;          // sample rate

typedef enum _EASIerror                           // error codes
{ EASIerror_success=          0,                  // successful operation
  EASIerror_notsupported=     1,                  // feature not supported
  EASIerror_hardwarenotfound= 2,                  // hardware not found
  EASIerror_hardwarefailure=  3,                  // hardware failure
  EASIerror_hardwarebusy=     4,                  // hardware is busy
  EASIerror_cpuoverload=      5,                  // cpu overload
  EASIerror_outofrange=       6,                  // parameter out of range
  EASIerror_unknown=          -1                  // unknown error
} EASIerror;

typedef enum _EASIiomode                          // i/o modes
{ EASIiomode_play,                                // playback
  EASIiomode_rec                                  // recording (full-duplex)
} EASIiomode;

typedef enum
{ EASIfmt_raw=                0,                  // raw bytes
  EASIfmt_i8=                 1,                  // 8 bit integer
  EASIfmt_i16=                2,                  // 16bit integer
  EASIfmt_i24=                3,                  // 24bit integer
  EASIfmt_i32=                4,                  // 32bit integer
  EASIfmt_f32=                5,                  // 32bit float
  EASIfmt_f64=                6,                  // 64bit double
} EASIfmt;

typedef struct _EASIxfer                          // data xfer descriptor
{ void*       pBuf;                               // pointer to frames/ items
  long        hBuf;                               // handle of data buffer
  long        lItemsPerFrame;                     // # of eFmt items per frame
  long        lNumFrames;                         // # of frames in this xfer
  EASIfmt     eFmt;                               // dataformat id
  float       xFmt;                               // dataformat nominal value
} EASIxfer;

extern const EASIvolume EASIvolume_0dB;           // nominal level/ 0dB
extern const EASIvolume EASIvolume_silence;       // no signal/ silence
extern const EASIvolume EASIvolume_illegal;       // illegal volume

extern const EASIiomask EASIiomask_all;           // mask w/ all channels active
extern const EASIiomask EASIiomask_none;          // mask w/ no channels active

//==============================================================================
// * * *   t a r g e t   o s   s t u f f   * * * * * * * * * * * * * * * * * * *
//==============================================================================

#if TARGET_OS_WIN32
  // target is Win32
  #include "EASIwin32.hpp"
#elif TARGET_OS_MAC
  // target is MacOS
  #include "EASImacos.hpp"
#else
  // undefined target os
  #include "EASInoos.hpp"
#endif

//==============================================================================
// * * *   E A S I p l u g i n   * * * * * * * * * * * * * * * * * * * * * * * *
//==============================================================================

class EASIplugin: public EASIpluginBase
{ //=== transport ==============================
  public:
    EASIapi(EASIerror)        // - error code
    Init                      // Open plug-in.
    ( void)                   // -
                                                =0;
    EASIapi(EASIerror)        // - error code
    SetPosition               // Set device position.
    ( EASIframes)             // - position [frames]
                                                =0;
    EASIapi(EASIerror)        // - error code
    BeforeStart               // Prepeare for audio streaming.
    ( EASIiomask,             // - channel mask playback
      EASIiomask)             // - channel mask recording
                                                =0;
    EASIapi(EASIerror)        // - error code
    GetReady                  // Prepare for zero-latency start-in.
    ( void)                   // -
                                                =0;
    EASIapi(EASIerror)        // - error code
    Start                     // Start audio streaming.
    ( void)                   // -
                                                =0;
    EASIapi(EASIframes)       // - position [frames]
    GetPosition               // Query current device position.
    ( void)                   // -
                                                =0;
    EASIapi(EASIerror)        // - error code
    GetInternalError          // Query and reset streaming error.
    ( void)                   // -
                                                =0;
    EASIapi(EASIerror)        // - error code
    Stop                      // Stop audio streaming.
    ( void)                   // -
                                                =0;
    EASIapi(EASIerror)        // - error code
    AfterStop                 // Cleanup after audio streaming.
    ( void)                   // -
                                                =0;
    EASIapi(EASIerror)        // - error code
    Cleanup                   // Close plug-in.
    ( void)                   // -
                                                =0;
  //=== capabilities ===========================
  public:
    EASIapi(EASIindex)        // - number
    GetNumChannels            // Query number of physical i/os.
    ( EASIiomode)             // - i/o mode
                                                =0;
    EASIapi(const char*)      // - name
    GetChannelName            // Query name of physical i/o.
    ( EASIiomode,             // - i/o mode
      EASIindex)              // - physical i/o
                                                =0;
    EASIapi(EASIindex)        // - number
    GetNumTracks              // Query number of virtual tracks.
    ( void)                   // -
                                                =0;
    EASIapi(EASIindex)        // - number
    GetNumSampleRates         // Query number of supported samplerates.
    ( void)                   // -
                                                =0;
    EASIapi(EASIsrate)        // - samplerate [Hz]
    GetSampleRate             // Query nominal samplerate from index.
    ( EASIindex)              // - samplerate [index]
                                                =0;
    EASIapi(bool)             // - true, if pitchable
    GetPitchRange             // Query pitch range from indexed samplerate.
    ( EASIindex,              // - samplerate [index]
      EASIsrate*,             // - min deviation [Hz]
      EASIsrate*)             // - max deviation [Hz]
                                                =0;
    EASIapi(bool)             // - true, if const
    IsConst                   // Check for constant xfer field.
    ( EASIiomode,             // - i/o mode
      EASIindex)              // - offsetof xfer field
                                                =0;
    EASIapi(const EASIxfer*)  // - xfer
    GetStdXfer                // Query constant xfer descriptor fields.
    ( EASIiomode)             // - i/o mode
                                                =0;
    EASIapi(EASIindex)        // - EASI version
    GetVersion                // Query version number.
    ( void)                   // -
                                                ;
  //=== streaming ==============================
  public:
    EASIapi(bool)             // - true, if sync'ed
    IsSynchronous             // Check for synchronous processing.
    ( EASIhandle)             // - callback handle
                                                =0;
    EASIapi(EASIframes)       // - position [frames]
    GetPosition               // Query streaming position.
    ( EASIhandle,             // - callback handle
      EASIiomode)             // - i/o mode
                                                =0;
    EASIapi(void)             // -
    NotifyDone                // Async completion notification.
    ( EASIhandle,             // - callback handle
      EASIiomode)             // - i/o mode
                                                =0;
    EASIapi(const EASIxfer*)  // - xfer
    GetXfer                   // Query xfer descriptor.
    ( EASIhandle,             // - callback handle
      EASIiomode,             // - i/o mode
      EASIindex)              // - physical i/o or virtual track
                                                =0;
    EASIapi(EASIframes)       // - length [frames]
    GetXferLength             // Query common xfer length.
    ( EASIhandle)             // - callback handle
                                                =0;
  //=== control ================================
  public:
    EASIapi(EASIerror)        // - error code
    SetSampleRate             // Assign new samplerate.
    ( EASIindex)              // - samplerate [index]
                                                =0;
    EASIapi(EASIerror)        // - error code
    SetPitch                  // Assign new frequency deviation.
    ( EASIsrate)              // - deviation [Hz]
                                                =0;
    EASIapi(EASIvolume)       // - level
    GetLevelmeter             // Query current input level.
    ( EASIiomode,             // - i/o mode
      EASIindex)              // - physical input or virtual track
                                                =0;
    EASIapi(EASIerror)        // - error code
    SetRouting                // Set output routing.
    ( EASIiomode,             // - i/o mode
      EASIindex,              // - physical input or virtual track
      EASIindex,              // - physical output: left
      EASIindex)              // - physical output: right
                                                =0;
    EASIapi(EASIerror)        // - error code
    SetGain                   // Set mixer gains.
    ( EASIiomode,             // - i/o mode
      EASIindex,              // - physical input or virtual track
      EASIvolume,             // - mixer gain: left
      EASIvolume)             // - mixer gain: right
                                                =0;
    EASIapi(bool)             // - true, to request re-init
    SetupDialog               // Open setup dialog box
    ( const EASIdlgInfo*)     // - additional dialog box info
                                                =0;
  //=== plugin creation ========================
  protected:
    EASIplugin                // Constructor.
    ( EASIhost*)              // - EASI host
                                                ;
};

//==============================================================================
// * * *   E A S I h o s t   * * * * * * * * * * * * * * * * * * * * * * * * * *
//==============================================================================

class EASIhost: public EASIhostBase
{ public:
    EASIapi(EASIerror)        // - error code
    Streaming                 // Data streaming callback.
    ( EASIhandle)             // - callback handle
                                                =0;
    EASIapi(EASIerror)        // - error code
    Monitoring                // Monitoring/ metering callback.
    ( EASIhandle)             // - callback handle
                                                =0;
    EASIapi(EASIindex)        // - EASI version
    GetVersion                // Query version number.
    ( void)                   // -
                                                ;
//=== host creation ==========================
  protected:
    EASIhost                  // Constructor.
    ( const EASIctorInfo*,    // - [in] construction info
      EASIplugin**)           // - [out] EASI plugin
                                                ;
};

#endif

/////////1/////////2/////////3/////////4/////////5/////////6/////////7/////////8
// end of file
