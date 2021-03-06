/*
 * DC-API: Distributed Computing Platform for Master-Worker Applications
 *
 * Common definitions for both the master and client side
 *
 * Authors:
 * 	Gabor Gombas <gombasg@sztaki.hu>
 *
 * Copyright MTA SZTAKI, 2006
 */
#ifndef __DC_COMMON_H_
#define __DC_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _WIN32
#include <dc_win32.h>
#else
#include <sys/syslog.h>
#endif

#include <string.h>
#include <stdarg.h>

/********************************************************************
 * Constant definitions
 */

/* API error codes */
typedef enum {
	DC_OK,			/* No error */
	DC_ERR_CONFIG,		/* Configuration error */
	DC_ERR_DATABASE,	/* Error with the internal data base */
	DC_ERR_NOTIMPL,		/* Not implemented by the API or by the
				   underlying grid infrastructure */
	DC_ERR_UNKNOWN_WU,	/* Unknown WU identifier */
	DC_ERR_TIMEOUT,		/* Timeout */
	DC_ERR_BADPARAM,	/* Bad function parameter */
	DC_ERR_SYSTEM,		/* A system call has failed, check errno */
	DC_ERR_INTERNAL,	/* Internal error */
} DC_ErrorCode;

/* Flags describing what capabilities does the underlying grid system
 * support */
typedef enum {
	DC_GC_EXITCODE		= (1 << 0),	/* DC_Result contains the
						   client's exit code */
	DC_GC_STDOUT		= (1 << 1),	/* The client's standard output
						   is available for the
						   master */
	DC_GC_STDERR		= (1 << 2),	/* Client's standard error is
						   available for the master */
	DC_GC_LOG		= (1 << 3),	/* Log file generated by the
						   execution environment is
						   available for the master */
	DC_GC_SUSPEND		= (1 << 4),	/* DC_suspendWU() works */
	DC_GC_SUBRESULT		= (1 << 5),	/* Sub-results work */
	DC_GC_MESSAGING		= (1 << 6)	/* Message sending works */
} DC_GridCapabilities;

/* File classification when passing a physical file name to DC-API */
typedef int DC_FileMode;
#define DC_FILE_REGULAR           (0)      /* Not persistent, needs copy */
#define DC_FILE_PERSISTENT        (1)      /* Persistent, link is enough */
#define DC_FILE_VOLATILE          (2)      /* DC-API should remove the original */
#define DC_FILE_REMOTE            (3)      /* HTTP files physically not present */
#define DC_FILE_PERSISTENT_CLIENT (1 << 7) /* FLAG: Persistent on client */

#define DC_OUTFILE_OPTIONAL       (1 << 8) /* FLAG: Output file is optional */  

/* Default name of the configuration file */
#define DC_CONFIG_FILE		"dc-api.conf"

/* Logical names for special files */
#define DC_LABEL_STDOUT		"dc_stdout.txt"
#define DC_LABEL_STDERR		"dc_stderr.txt"
#define DC_LABEL_CLIENTLOG	"dc_clientlog.txt"


/********************************************************************
 * Data types
 */

/* Descriptor of a physical file */
typedef struct _DC_PhysicalFile	DC_PhysicalFile;
struct _DC_PhysicalFile
{
	char			*label;
	char			*path;
	DC_FileMode		mode;
	char			*physicalfilename;
	char			*physicalfilehash;
    int             persistentonclient;
};

/* Descriptor of a remote file */
typedef struct _DC_RemoteFile	DC_RemoteFile;
struct _DC_RemoteFile
{
	char			*label;
	char			*url;
	char			*remotefilehash;
	size_t			remotefilesize;
    int             persistentonclient;
};


/********************************************************************
 * Function prototypes
 */

#ifndef __GNUC__
#define __attribute__(x)
#endif

/* Determines the maximum allowed message length. */
int DC_getMaxMessageSize(void);

/* Determines the maximum number of sub-results. */
int DC_getMaxSubresults(void);

/* Determines the basic capabilities of the underlying grid infrastructure. */
unsigned DC_getGridCapabilities(void);

/* Prints a message to the log file. */
void DC_log(int level, const char *fmt, ...)
	__attribute__((format(printf, 2, 3)));
void DC_vlog(int level, const char *fmt, va_list args)
	__attribute__((format(printf, 2, 0)));

/* Returns the value associated with the specified key in the config. file */
char *DC_getCfgStr(const char *name);

/* Returns the integer value associated with the specified key in the config.
 * file */
int DC_getCfgInt(const char *name, int defaultValue);

/* Returns the boolean value associated with the specified key in the config.
 * file */
int DC_getCfgBool(const char *name, int defaultValue);

#ifdef __cplusplus
}
#endif

#endif /* __DC_COMMON_H_ */
