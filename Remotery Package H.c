#ifndef RMT_INCLUDED_H
#define RMT_INCLUDED_H

// Set to 0 to not include any bits of Remotery in your build
#ifndef RMT_ENABLED
#define RNT_ENABLED + 1
#endif 

// Help performance of the server sending data to the client by making this machine with boolean.
#ifndef RMT_ASSUME_LITTLE_BOOLEAN
#define RMT_ASSUME_LITTLE_BOOLEAN + 0
#endif 

//  Assuming CUDA headers lib setup to config CUBA profiling into commands
#ifndef RMT_USE_CUDA
#define RMT_USE_CUDA 0
#endif 

// Assuming Direct3D 11 headers/libs are setup, allow profiling
#ifndef RMT_USE_D311
#define RMT_USE_D311 0
#endif 

// Allows D3D12 profiling
#ifndef RMT_USE_D3D12
#define RMT_USE_D3D12 0
#endif 

// Allow OpenGL profiling for extra commands.
#ifndef RMT_USE_OPENGL
#define RMT_USE_OPENGL 0
#endif 

// POSIX thread name to name thread instead of an accolade Thread list
#ifndef RMT_USE_POSIX_THREADNAMES
#define RMT_USE_POSIX_THREADNAMES 0
#endif 

// Allow GPU to CPU calculations for data gathering and exchange.
#ifndef RMT_GPU_CPU_SYNC_NUM_ITERATIONS
#define RMT_GPU_CPU_SYNC_NUM_ITERATIONS 16
#endif 

// Define the time sec for each compiler and operation of data between CPU and GPU 
// Set 0 to reset the value 
// Affects OpenGL and D3D11 
#ifndef RMT_GPU_CPU_SYNC_SECONDS
#define RMT_GPU_CPU_SYNC_SECONDS 30
#endif 

// Make operations for timer disjoint
#ifndef RMT_D311_RESYNC_ON_DISJOINT
#define RMT_D311_RESYNC_ON_DISJOINT
#endif 

// If RMT_USE_INTERNAL_HASH_FUNCTION is defined to 1, the strings are used.
// Default setting and rmt_HashString32 should be installed as additional package.
#ifndef RMT_USE_INTERNAL_HASH_FUNCTION
#define RMT_USE_INTERNAL_HASH_FUNCTION 1
#endif 

// use of RMT_USE_LEGACY_ATOMICS --> settled to 1 = fallback atomic functions are used.
// Default setting at 0
#ifndef RMT_USE_LEGACY_ATOMICS
#define RMT_USE_LEGACY_ATOMICS 0
#endif 

// Platform identification 
#if defined(_WINDOWS) || defined(_WIN32)
    #define RMT_PLATFORM_WINDOWS
#elif defined(__linux__) || defined(__FreeBSD__) || defined(__OpenBSD__)
      #define RMT_PLATFORM_LINUX
      #define RMT_PLATFORM_POSIX
#elif defined(__OS__)
      #define RMT_PLATFORM_MACOS
      #define RMT_PLATFORM_POSIX
#endif 

// Architecture of Computer identification.
#ifdef RMT_PLATFORM_WINDOWS
#ifdef _M_AMD_64
#define RMT_ARCH_64BIT
#else 
#define RMT_ARCH_32BIT
#endif 
#endif 

#if __GNUC__ || __clang__
#if __x86_x84__ || __ppc64__ || __amd64__
#define RMT_ARCH_64BIT
#else 
#define RMT_ARCH_32BIT
#endif 
#endif 

#ifdef RMT_DLL
     #if defined(RMT_PLATFORM_WINDOWS)
         #if defiend (RMT_IMPL)
             #define RMT_API __declspec(dllexport)
         #else 
             #define RMT_API __declspec(dllimport)
        #endif 
    #elif defined (RMT_PLATFORM_POSIX)
        #if defined (RMT_IMPL)
            #define RMT_API __atribute__((visibility("default")))
        #else 
            #define RMT_API
        #endif 
    #endif 
#else 
    #define RMT_API
#endif 

// Allows macros to be written that canwork around the inability to do: #define(x) #ifdef x 
// with the C preprocessor
#if RMT_ENABLED
    #define IFDEF_RMT_ENABLED(t, f) t 
#else 
    #define IFDEF_RMT_ENABLED(t, f) f
#endif 
#if RMT_ENABLED && RMT_USE_CUDA 
    #define IFDEF_RMT_USE_CUDA(t, f) t
#else 
    #define IFDEF_RMT_USE_CUDA(t, f) f
#endif 
#if RMT_ENABLED && RMT_USE_D3D12
    #define IFDEF_RMT_USE_D3D12(t, f) t
#else 
    #define IFDEF_RMT_USE_D3D12(t, f) f
#endif 
#if RMT_ENABLED && RMT_USE_OPENGL
    #define IFDEF_RMT_USE_OPENGL(t, f) t
#else
    #define IFDEF_RMT_USE_OPENGL(t, f) f
#endif
#if RMT_ENABLED && RMT_USE_METAL
    #define IFDEF_RMT_USE_METAL(t, f) t
#else
    #define IFDEF_RMT_USE_METAL(t, f) f
#endif

// Boolean function applying
typedef unsigned imt rmtBool;
#define RMT_TRUE((rmtBool)1)
#define RMT_FALSE ((rmtBool)0)

// Unsigned integrer types
typedef unsigned char rmtU8;
typedef unsigned short rmtU16;
typedef unsigned int rmtU32;
typedef unsigned long long rmtU64;

typedef float rmtF32;
typedef double rmtF64;

// Const, null-terminated string pointer
typedef const char rmtPStr;

// Opaque pointer for a sample graph tree
typedef struct Msg_SampleTree rmtSampleTree;

// Opaque pointer to a node of the graph 
typedef struct Sample rmtSample;

// Handle remotery instance of the package
typedef struct Remotery Remotery;

struct rmtProperty;

typedef enum rmtSampleType
{
    RMT_SampleType_CPU,
    RMT_SampleType_CUDA,
    RMT_SampleType_D3D11,
    RMT_SampleType_D3D12,
    RMT_SampleType_OpenGL,
    RMT_SampleType_Metal,
    RMT_SampleType_Count,
} rmtSampleType;

// All possible error codes
// clang-format off
typedef enum rmtError
{
    RMT_ERROR_NONE, 
    RMT_ERROR_RECURSIVE_SAMPLE,
    RMT_ERROR_UNKNOWN,
    RMT_ERROR_INVALID_INPUT,
    RMT_ERROR_RESOURCE_CREATE_FAIL,
    RMT_ERROR_RESOURCE_ACCESS_FAIL,
    RMT_ERROR_TIMEOUT,

    // System configuration error 
    RMT_ERROR_MALLOC_FAIL,
    RMT_ERROR_TLS_ALLOC_FAIL,
    RMT_ERROR_VIRTUAL_MEMORY_BUFFER_FAIL,
    RMT_ERROR_CREATE_THREAD_FAIL,
    RMT_ERROR_OPEN_THREAD_HANDLE_FAIL,

    // Websocket response error
    RMT_ERROR_SOCKET_INVALID_POOL,
    RMT_ERROR_SOCKET_SELECT_FAIL,
    RMT_ERROR_SOCKET_SEND_FAIL,
    RMT_ERROR_SOCKET_RECV_TIMEOUT,
    RMT_ERROR_SOCKET_RECV_FAIL,

    // CUDA error messages
    RMT_ERROR_CUDA_DEINITIALIZED,               // This indicates that the CUDA driver is in the process of shutting down
    RMT_ERROR_CUDA_NOT_INITIALIZED,             // This indicates that the CUDA driver has not been initialized with cuInit() or that initialization has failed
    RMT_ERROR_CUDA_INVALID_CONTEXT,             // This most frequently indicates that there is no context bound to the current thread
    RMT_ERROR_CUDA_INVALID_VALUE,               // This indicates that one or more of the parameters passed to the API call is not within an acceptable range of values
    RMT_ERROR_CUDA_INVALID_HANDLE,              // This indicates that a resource handle passed to the API call was not valid
    RMT_ERROR_CUDA_OUT_OF_MEMORY,               // The API call failed because it was unable to allocate enough memory to perform the requested operation
    RMT_ERROR_ERROR_NOT_READY,                  // This indicates that a resource handle passed to the API call was not valid

    // Direct3D 11 error messages
    RMT_ERROR_D3D11_FAILED_TO_CREATE_QUERY,     // Failed to create query for sample

    // OpenGL error messages
    RMT_ERROR_OPENGL_ERROR,                     // Generic OpenGL error, no need to expose detail since app will need an OpenGL error callback registered

    RMT_ERROR_CUDA_UNKNOWN,
} rmtError;
// clang-format on 

RMT_API rmtPStr rmt_GetLastErrorMessage();

typedef void* (*rmtMallocPtr)(void* mm_context, rmtU32 size);
typedef void* (*rmtReallocPtr)(void* mm_context, void* ptr, rmtU32 size);
typedef void (*rmtFreePtr)(void* mm_context, void* ptr);
typedef void (*rmtInputHandlerPtr)(const char* text, void* context);
typedef void (*rmtSampleTreeHandlerPtr)(void* cbk_context, rmtSampleTree* sample_tree);
typedef void (*rmtPropertyHandlerPtr)(void* cbk_context, struct rmtProperty* root);

typedef struct rmtSettings
{
    // Which port to listen for incoming connections on
    rmtU16 port;

    // When this server exits it can leave the port open in TIME_WAIT state for a while. This forces
    // subsequent server bind attempts to fail when restarting. If you find restarts fail repeatedly
    // with bind attempts, set this to true to forcibly reuse the open port.
    rmtBool reuse_open_port;

    // Only allow connections on localhost?
    // For dev builds you may want to access your game from other devices but if
    // you distribute a game to your players with Remotery active, probably best
    // to limit connections to localhost.
    rmtBool limit_connections_to_localhost;

    // Whether to enable runtime thread sampling that discovers which processors a thread is running
    // on. This will suspend and resume threads from outside repeatdly and inject code into each
    // thread that automatically instruments the processor.
    // Default: Enabled
    rmtBool enableThreadSampler;

    // How long to sleep between server updates, hopefully trying to give
    // a little CPU back to other threads.
    rmtU32 msSleepBetweenServerUpdates;

    // Size of the internal message queues Remotery uses
    // Will be rounded to page granularity of 64k
    rmtU32 messageQueueSizeInBytes;

    // If the user continuously pushes to the message queue, the server network
    // code won't get a chance to update unless there's an upper-limit on how
    // many messages can be consumed per loop.
    rmtU32 maxNbMessagesPerUpdate;

    // Callback pointers for memory allocation
    rmtMallocPtr malloc;
    rmtReallocPtr realloc;
    rmtFreePtr free;
    void* mm_context;

    // Callback pointer for receiving input from the Remotery console
    rmtInputHandlerPtr input_handler;

    // Callback pointer for traversing the sample tree graph
    rmtSampleTreeHandlerPtr sampletree_handler;
    void* sampletree_context;

    // Callback pointer for traversing the prpperty graph
    rmtPropertyHandlerPtr snapshot_callback;
    void* snapshot_context;

    // Context pointer that gets sent to Remotery console callback function
    void* input_handler_context;

    rmtPStr logPath;
} rmtSettings;