//
// vf_dir.h
//
// Copyright (c) 1998, Sam Roberts
// 
// $Log$
// Revision 1.5  1998/04/06 06:49:05  sroberts
// implemented write(), implemented FileEntity factory, and removed unused
// close() memthod
//
// Revision 1.4  1998/04/05 23:54:41  sroberts
// added support for mkdir(), and a factory class for dir and file entities
//
// Revision 1.3  1998/03/19 07:41:25  sroberts
// implimented dir stat, open, opendir, readdir, rewinddir, close
//
// Revision 1.2  1998/03/15 22:07:49  sroberts
// implemented insertion
//
// Revision 1.1  1998/03/09 06:07:25  sroberts
// Initial revision
//

#ifndef VF_DIR_H
#define VF_DIR_H

#include <sys/stat.h>

#include <wchash.h>
#include <wcvector.h>

#include "vf.h"

class VFDirFactory
{
public:
	VFDirFactory(mode_t mode = 0555);

	virtual VFEntity* NewDir(_fsys_mkspecial* req = 0);
	virtual VFEntity* NewFile(_io_open* req = 0);

protected:
	mode_t mode_;
};

class VFDirEntity : public VFEntity
{
public:
	VFDirEntity(mode_t mode, VFDirFactory* factory = 0);
	~VFDirEntity();

	VFOcb* Open(const String& path, _io_open* req, _io_open_reply* reply);
	int Stat(const String& path, _io_open* req, _io_fstat_reply* reply);
	int ChDir(const String& path, _io_open* req, _io_open_reply* reply);
	int Unlink();
	int MkDir(const String& path, _fsys_mkspecial* req, _fsys_mkspecial_reply* reply);

	bool Insert(const String& path, VFEntity* entity);
	struct stat* Stat();

private:
	friend class VFDirOcb;

    // position -> entity/name map
	struct EntityNamePair
	{
		// default ctor required by Watcom vector
		EntityNamePair() : entity(0) { }
		EntityNamePair(VFEntity* entity_, const String& name_) :
			entity(entity_), name(name_)
		{
		}

		VFEntity* entity;
		String name;
	};

	typedef WCValHashDict<String, VFEntity*> EntityMap;
	typedef WCPtrVector<EntityNamePair> EntityIndex;

	EntityMap   map_;
	EntityIndex index_;

	struct stat stat_;

	VFDirFactory* factory_;

	void SplitPath(const String& path, String& lead, String& tail);
	void InitStat(mode_t mode);

	// used by the WC hash dictionary
	static unsigned Hash(const String& key);
};

class VFDirOcb : public VFOcb
{
public:
	VFDirOcb(VFDirEntity* dir);
	~VFDirOcb();

	int Stat();
	int Read();
	int Write(pid_t pid, _io_write* req, _io_write_reply* reply);
	int Seek();
	int Chmod();
	int Chown();

	int ReadDir(_io_readdir* req, _io_readdir_reply* reply);
	int RewindDir(_io_rewinddir* req, _io_rewinddir_reply* reply);

private:

	VFDirEntity* dir_;

	int readIndex_;
};

#endif

