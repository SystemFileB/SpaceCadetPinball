#include "pch.h"
#include "midi.h"


#include "pb.h"


std::vector<Mix_Music*> midi::LoadedTracks{};
Mix_Music* midi::track1, * midi::track2, * midi::track3;
MidiTracks midi::active_track, midi::NextTrack;
int midi::Volume = MIX_MAX_VOLUME;
bool midi::IsPlaying = false, midi::MixOpen = false;

constexpr uint32_t FOURCC(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	return static_cast<uint32_t>((d << 24) | (c << 16) | (b << 8) | a);
}

int ToVariableLen(uint32_t value, uint32_t& dst)
{
	auto count = 1;
	dst = value & 0x7F;

	while ((value >>= 7))
	{
		dst <<= 8;
		dst |= ((value & 0x7F) | 0x80);
		count++;
	}

	return count;
}

void midi::music_play() // options.cpp,pb.cpp,winmain.cpp
{
	if (!IsPlaying)
	{
		IsPlaying = true;
		play_track(NextTrack, true);
		NextTrack = MidiTracks::None;
	}
}

void midi::music_stop() // options.cpp,pb.cpp,winmain.cpp
{
	if (IsPlaying)
	{
		IsPlaying = false;
		NextTrack = active_track;
		StopPlayback();
	}
}

void midi::StopPlayback()
{
	if (active_track != MidiTracks::None)
	{
		if (MixOpen)
			Mix_HaltMusic();
		active_track = MidiTracks::None;
	}
}

int midi::music_init(bool mixOpen, int volume) // winmain.cpp
{
	MixOpen = mixOpen;
	SetVolume(volume);
	active_track = MidiTracks::None;
	NextTrack = MidiTracks::None;
	IsPlaying = false;
	track1 = track2 = track3 = nullptr;

	if (pb::FullTiltMode)
	{
		track1 = load_track("TABA1");
		track2 = load_track("TABA2");
		track3 = load_track("TABA3");

		// FT demo .006 has only one music track, but it is nearly 9 min. long
		if (!track1 && pb::FullTiltDemoMode)
			track1 = load_track("DEMO");
	}
	else
	{
		// 3DPB has only one music track. PINBALL2.MID is a bitmap font, in the same format as PB_MSGFT.bin
		track1 = load_track("PINBALL");
	}

	return track1 != nullptr;
}

void midi::music_shutdown() // winmain.cpp
{
	music_stop();

	for (auto midi : LoadedTracks)
	{
		Mix_FreeMusic(midi);
	}
	active_track = MidiTracks::None;
	LoadedTracks.clear();
}

void midi::SetVolume(int volume) // winmain.cpp
{
	Volume = volume;
	if (MixOpen)
		Mix_VolumeMusic(volume);
}

Mix_Music* midi::load_track(std::string fileName)
{
	if (!MixOpen || pb::quickFlag)
		return nullptr;

	if (pb::FullTiltMode)
	{
		// FT sounds are in SOUND subfolder
		fileName.insert(0, 1, PathSeparator);
		fileName.insert(0, "SOUND");
	}

	auto audio = load_track_sub(fileName);
	if (!audio)
		audio = load_track_sub(fileName);

	if (!audio)
		return nullptr;

	LoadedTracks.push_back(audio);
	return audio;
}

Mix_Music* midi::load_track_sub(std::string fileName)
{
    // 直接加载OGG格式文件
    Mix_Music* audio = nullptr;
    fileName += ".ogg"; // 使用OGG后缀
    
    for (int i = 0; i < 2; i++)
    {
        if (i == 1)
            std::transform(fileName.begin(), fileName.end(), fileName.begin(),
                           [](unsigned char c) { return std::tolower(c); });
        
        auto filePath = pb::make_path_name(fileName);
        auto fileHandle = fopenu(filePath.c_str(), "rb");
        if (fileHandle)
        {
            fclose(fileHandle);
            auto rw = SDL_RWFromFile(filePath.c_str(), "rb");
            audio = Mix_LoadMUS_RW(rw, 1);
            break;
        }
    }

    return audio;
}

bool midi::play_track(MidiTracks track, bool replay) // control.cpp,TPinballTable.cpp
{
	auto midi = TrackToMidi(track);
	if (!midi || (!replay && active_track == track))
		return false;

	StopPlayback();

	if (!IsPlaying)
	{
		NextTrack = track;
		return false;
	}

	if (MixOpen && Mix_PlayMusic(midi, -1))
	{
		active_track = MidiTracks::None;
		return false;
	}

	// On Windows, MIDI volume can only be set during playback.
	// And it changes application master volume for some reason.
	SetVolume(Volume);
	active_track = track;
	return true;
}

MidiTracks midi::get_active_track()
{
	if (!IsPlaying)
		return NextTrack;
	else
		return active_track;
}

Mix_Music* midi::TrackToMidi(MidiTracks track)
{
	Mix_Music* midi;
	switch (track)
	{
	default:
	case MidiTracks::None:
		midi = nullptr;
		break;
	case MidiTracks::Track1:
		midi = track1;
		break;
	case MidiTracks::Track2:
		midi = track2;
		break;
	case MidiTracks::Track3:
		midi = track3;
		break;
	}
	return midi;
}