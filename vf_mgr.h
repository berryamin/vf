//
// vf_fsys.h
//
// Copyright (c) 1998, Sam Roberts
// 
// $Log$
// Revision 1.2  1998/03/19 07:41:25  sroberts
// implimented dir stat, open, opendir, readdir, rewinddir, close
//
// Revision 1.1  1998/03/09 06:07:25  sroberts
// Initial revision
//

#ifndef VF_MGR_H
#define VF_MGR_H

#include "vf.h"

// temporary for OcbMap
#include <unistd.h>
#include <sys/fd.h>

union VFIoMsg
{
	msg_t	type;
	msg_t	status;

	struct _io_open 			open;
	struct _io_open_reply 		open_reply;

	struct _io_fstat_reply		fstat_reply;

	struct _io_readdir 			readdir;
	struct _io_readdir_reply 	readdir_reply;

	struct _io_close 			close;
	struct _io_close_reply 		close_reply;

	//struct _io_read 			read;
	//struct _io_read_reply 		read;
	//struct _io_write 			write;
	//struct _io_write_reply 		write;
	//struct _io_lseek 			lseek;
	//struct _io_lseek_reply 		lseek;
	//struct _io_config 			
	//struct _io_config_reply 			
	//struct _io_dup 			
	//struct _io_dup_reply 			
	//struct _io_fstat 			
	//struct _io_chmod 			
	//struct _io_chmod_reply 			
	//struct _io_chown 			
	//struct _io_chown_reply 			
	//struct _io_utime 			
	//struct _io_utime_reply 			
	//struct _io_flags 			
	//struct _io_flags_reply 			
	//struct _io_lock 			
	//struct _io_rewinddir 			
	//struct _io_rewinddir_reply 			
	//struct _io_ioctl 			
	//struct _io_ioctl_reply 			
	//struct _io_qioctl 			
	//struct _io_qioctl_reply 			
	//struct _select_set 			
	//struct _io_select 			
	//struct _io_select_reply 			

	// reserve space because struct _io_open and such have buffers of
	// unspecified length as members
	char reserve [1024];
};

class OcbMap;

class VFManager
{
public:
	Init(VFEntity *root, const char* mount, int verbosity = 1);

	int Handle(pid_t pid, VFIoMsg* msg);

	void Run();

private:
	VFOcbMap* ocbMap_;

	VFIoMsg msg_;

	VFEntity*   root_;
	const char* mount_;
};

#endif

