//
// vf_popfile.h
//
// Copyright (C) 1999 Sam Roberts
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 1, or (at your option)
//  any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
//  I can be contacted as sroberts@uniserve.com, or sam@cogent.ca.
//
// $Log$
// Revision 1.1  1999/09/26 23:40:21  sam
// Initial revision
//
// Revision 1.8  1999/09/26 22:50:27  sam
// reorganized the templatization, checking in prior to last cleanup
//
// Revision 1.7  1999/09/23 01:39:22  sam
// first cut at templatization running ok
//
// Revision 1.6  1999/09/19 22:24:47  sam
// implemented threading with a work team
//
// Revision 1.5  1999/08/09 15:19:38  sam
// Multi-threaded downloads! Pop servers usually lock the maildrop, so concurrent
// downloads are not possible, but stats and reads of already downloaded mail
// do not block on an ongoing download!
//
// Revision 1.4  1999/08/09 09:27:43  sam
// started to multi-thread, but fw didn't allow blocking, checking in to fix fw
//
// Revision 1.3  1999/07/21 16:00:17  sam
// the symlink extension wasn't working, commented it out
//
// Revision 1.2  1999/07/19 15:23:20  sam
// can make aribtrary info show up in the link target, now just need to get
// that info...
//
// Revision 1.1  1999/06/20 17:21:53  sam
// Initial revision
//

#ifndef VF_POPFILE_H
#define VF_POPFILE_H

#include <sys/types.h>

#include <pop3.h>

#include <vf_file.h>
#include <vf_fifo.h>

#include "url.h"

class VFPop;

class VFPopFile : public VFFileEntity
{
public:
	VFPopFile(int msg, VFPop& pop, int size);
	~VFPopFile();

	// These aren't implemented yet, I'm going to try and have the files
	// look like links to lstat(), but not to cat and vi, so I can reply
	// to readlink() with a subject/from field...
	int Stat(pid_t pid, const String* path, int lstat); // XXX
	int ReadLink(pid_t pid, const String& path); // XXX

	int Read(pid_t pid, size_t nbytes, off_t* offset);

	void Return(int status, istream* data);

private:
	int QueueRead(pid_t pid, int nbytes, off_t* offset);
	int ReplyRead(pid_t pid, int nbytes, off_t* offset);

	VFPop&		pop_;
	int			msg_;
	istream*	data_;
	int			size_;

	char*		description_;

	struct ReadRequest : public VFFifo<ReadRequest>::Link
	{
		ReadRequest(pid_t pid, int nbytes, off_t* offset) :
			pid(pid), nbytes(nbytes), offset(offset) {}

		pid_t	pid;
		int		nbytes;
		off_t*	offset;
	};

	VFFifo<ReadRequest>	readq_;
};

#endif

