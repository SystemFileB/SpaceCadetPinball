#include <vector>
#include <cstdint>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cassert>

#ifndef MDS2MIDI_DEPS_H
#define MDS2MIDI_DEPS_H

// ..........以下来自SpaceCadetPinball/pch.h..........
#ifdef _WIN32
extern FILE* fopenu(const char* path, const char* opt);
#else
inline FILE* fopenu(const char* path, const char* opt)
{
	return fopen(path, opt);
}
#endif

#define assertm(exp, msg) assert(((void)msg, exp))

#endif // MDS2MIDI_DEPS_H