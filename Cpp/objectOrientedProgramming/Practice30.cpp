// This file creates a MIDI file in C++
// Crazily awesome!
// Note: It also uses variadic templates to store bytes of data

#include <vector>   // For std::vector<>
#include <cstring>  // For std::strlen()
#include <cstdio>   // For std::fopen(), std::fwrite(), std::fclose()

// define byte as an unsigned char
typedef unsigned char byte;

// Creates a vector of bytes (std::vector<byte) with variadic templates to
// to add a varying amount of bytes within one function.
class MIDIvec: public std::vector<byte>
{
public:
    // Uses default constructor and default destructor

    // Methods for appending raw data into the vector:
    // Variadic Templates, take in 0 or more arguments of templateName Args
    // Takes in a byte of data and 0 or more arguments of type Args
    template<typename... Args>
    void AddBytes(byte data, Args...args)
    {
        push_back(data); // add the first data to the byte
        AddBytes(args...); // recursively call this function with remaining variables to add to byte
                            // Base case will be handled by void AddBytes below
    }

    // Variadic template to add a string
    template<typename... Args>
    void AddBytes(const char* s, Args...args)
    {
        insert(end(), s, s + std::strlen(s)); // insert a strength
        AddBytes(args...); // Add bytes of the remaining arguments after the string
    }
    // Add nothing to handle base case for above recursive functions that calls AddBytes with no arguments
    void AddBytes() { } // Does nothing
};

// This class encodes MIDI events into a track, it is the child of MIDIvec above
class MIDItrack: public MIDIvec
{
protected:
    // to know if running_status is occuring and keep track of delay
    unsigned delay, running_status;
public:
    // Constructor
    // Calls default constructor of parent, and set both delay and running_status to 0
    MIDItrack() : MIDIvec(), delay(0), running_status(0)
    {
    }

    // Methods to indicate elapsed time
    void AddDelay(unsigned amount) { delay += amount; }

    // Method to add byte of length t
    // used by method Flush() below
    void AddVarLen(unsigned t)
    {
        // If statement means it sends the higher order bits first, if they do not exist
        // it will skip the higher order bits and only shift the following higher order bits if they exist
        // Note: It appends 1 to the 7th bit (counting from 0) of each higher order byte except the lowest byte.
        // rightshift t, if it is not 0, means the length was longer than 21
        // Add first byte as (10000000 or ((rightshift t by 21)&(01111111)))
        if(t >> 21) AddBytes(0x80 | ((t >> 21) & 0x7F)); // always make sure the 7th bit counting from zero is a 1
        if(t >> 14) AddBytes(0x80 | ((t >> 14) & 0x7F)); // shift the remaining and append 1 to 7th bit
        if(t >>  7) AddBytes(0x80 | ((t >>  7) & 0x7F)); // shift the remaining and append 1 to 7th bit
        AddBytes(((t >> 0) & 0x7F)); // shift the remaining
    }

    // Method to add the delay to the byte of data and reset it to 0
    void Flush()
    {
        AddVarLen(delay);
        delay = 0;
    }

    // Track Events
    // Methods for appending events into the track:
    template<typename... Args>
    void AddEvent(byte data, Args...args)
    {
        // MIDI tracks event have the following structure:
         // { timestamp [metaevent ... ] event } ...
         // Each event is prefixed with a timestamp,
         // which is encoded in a variable-length format.
         //The timestamp describes the amount of time that
         // must be elapsed before this event can be handled.

         // After the timestamp, comes the event data.
         // The first byte of the event always has the high bit on,
         // and the remaining bytes always have the high bit off.
         // Running status => First byte same as previous command, so can be omitted
         // The event may furthermore beprefixed
         // with a number of meta events.
       Flush();
       if(data != running_status) // If the running status is not the same as the latest data sent
            AddBytes(running_status = data); // add the current data as well as assign
                                            // assign the latest data as the new running_status
       // However, if the data is same as the running status, ignore it and send the next bytes recursively
       AddBytes(args...); // Recursively add remaining data regardless if if condition above is true
    }
    // Base case for recursive call above
    void AddEvent() { }

    // A varidic template to add meta events in MIDI
    template<typename... Args>
    void AddMetaEvent(byte metatype, byte nbytes, Args...args)
    {
        Flush(); // flush previous messages before sending this MIDI message
        AddBytes(0xFF, metatype, nbytes, args...);
    }

    // Key-related parameters: channel number, note number, pressure
                                        // Or the channel number with 0x90, and append note number and pressure
    void KeyOn(int ch, int n, int p)    { if(n>=0)AddEvent(0x90|ch, n, p); }
    void KeyOff(int ch, int n, int p)   { if(n>=0)AddEvent(0x80|ch, n, p); }
    void KeyTouch(int ch, int n, int p) { if(n>=0)AddEvent(0xA0|ch, n, p); }
    // Events with other types of parameters:
                        // c=> controller number, v=> value controller set to
    void Control(int ch, int c, int v) { AddEvent(0xB0|ch, c, v); }
                                        // Program number = patchno
    void Patch(int ch, int patchno)    { AddEvent(0xC0|ch, patchno); }
    // value is amount of pitch to transpose by
    void Wheel(int ch, unsigned value)
    { AddEvent(0xE0|ch, value&0x7F, (value>>7)&0x7F); } // only append 7 bits of first byte with 7 bits of 2nd byte

    // Methods for appending metadata into the track:
    void AddText(int texttype, const char* text)
    {
        AddMetaEvent(texttype, std::strlen(text), text);
    }
};

// Class that is a child of the MIDIvec class, with methods needed to create a MIDI file
class MIDIfile: public MIDIvec
{
protected:
    std::vector<MIDItrack> tracks; // create a vector of tracks
    unsigned deltaticks, tempo; // Tempo is used to set tempo of song using Meta Event 0x51 command
public:
    // Constructor , call parent default constructor and MIDItracks's default constructor
    MIDIfile()
        : MIDIvec(), tracks(), deltaticks(1000), tempo(1000000)
    {
    }

    // These 2 functions adds a loopStart and loopEnd marker as Meta Events to the file
                                            // 6 => Marker Text
    void AddLoopStart()  { (*this)[0].AddText(6, "loopStart"); }
    void AddLoopEnd()    { (*this)[0].AddText(6, "loopEnd"); }

    // This MIDIfile class returns a MIDItrack reference when used with the [] operator
    // with parameter [trackno] to indicate the track number
    MIDItrack& operator[] (unsigned trackno)
    {
        if(trackno >= tracks.size())
        {
            tracks.reserve(16); // add more space to track vectors
            tracks.resize(trackno+1); // resize the track to be trackno+1 => 16 bytes
        }
        // Get the expected track
        MIDItrack& result = tracks[trackno];
        // If no result to return
        if(result.empty())
        {
            // Meta 0x58 (misc settings): // Time Signature
                //      time signature: 4/2
                //      ticks/metro:    24
                //      32nd per 1/4:   8
            result.AddMetaEvent(0x58,4,  4,2, 24,8);
            // Meta 0x51 (tempo): // Add Tempo
            result.AddMetaEvent(0x51,3,  tempo>>16, tempo>>8, tempo);
        }
        return result;
    }

    // What essentiall happens is it saves bunch of information on the track vectors
    // Then when you finally call Finish(), it appends  the "MThd" code at the beginning of bytes
    // continuously adds all tracks a little by a little
    // Override previous function from parent
    void Finish()
    {
        clear();
        // Call add bytes function with the Header Chunk
        // MIDI signature (MThd and number 6)
        // Header Chunk, "MThd"
        // 6 header length (4 bytes), 0,0,0,6
        // format of multi track (2bytes), 0,1
        // number of track (2bytes), track.size()>>8, track.size()
        // time division (2bytes), deltaticks>>8, deltaticks
        // Note: It passes in the upper bytes before the lower bytes  (BIG ENDIAN format)
        AddBytes("MThd", 0,0,0,6, 0,1, tracks.size() >> 8, tracks.size(), deltaticks >> 8, deltaticks);

        // For all the tracks
        for(unsigned a=0; a<tracks.size(); ++a)
        {
            // Add meta 0x2F to the track, indicating the track end:
            tracks[a].AddMetaEvent(0x2F, 0); // 0x2F => Track ends , 0=> 0 number of bytes left in this meta event
            // Add the track into the MIDI file:
            // "MTrk" (4bytes) => Indicates Track Chunk data
            // # of bytes in track (4 bytes)
            AddBytes("MTrk",tracks[a].size() >> 24,tracks[a].size() >> 16,tracks[a].size() >> 8,tracks[a].size() >> 0);
            // insert at the end of the current vector of bytes,
            // the beginning of current track till the end of current track
            insert(end(), tracks[a].begin(), tracks[a].end());
               // position to insert, the beginning of iterator values to insert, the end of iterator values to insert
        }
    }
};

// Creates a MIDI file with music
int main()
{
    // Begin with some chords.
    static const int chords[][3] =
    {
        { 12,4,7 }, // +C  E  G  = 0
        { 12,9,5 }, // +C  A  F  = 1
        { 12,8,3 }, // +C  G# D# = 2
        { 12,7,3 }, // +C  G  D# = 3
        { 12,5,8 }, // +C  F  G# = 4
        { 12,3,8 }, // +C  D# G# = 5
        { 11,2,7 }, //  B  D  G  = 6
        { 10,2,7 }, // A#  D  G  = 7
        { 14,7,5 }, // +D  G  F  = 8
        { 14,7,11 },// +D  G  B  = 9
        { 14,19,11 }// +D +G  B  = 10
    };
    const char x = 99; // Arbitrary value we use here to indicate "no note"
    static const char chordline[64] =
    {
        0,x,0,0,x,0,x, 1,x,1,x,1,1,x,1,x,  2,x,2,2,x,2,x, 3,x,3,x,3,3,x,3,x,
        4,x,4,4,x,4,x, 5,x,5,x,5,5,x,5,x,  6,7,6,x,8,x,9,x,10,x,x,x,x,x,x,x
    };
    static const char chordline2[64] =
    {
        0,x,x,x,x,x,x, 1,x,x,x,x,x,x,x,x,  2,x,x,x,x,x,x, 3,x,x,x,x,x,x,x,x,
        4,x,x,x,x,x,x, 5,x,x,x,x,x,x,x,x,  6,x,x,x,x,x,x,x, 6,x,x,x,x,x,x,x
    };
    static const char bassline[64] =
    {
        0,x,x,x,x,x,x, 5,x,x,x,x,x,x,x,x,  8,x,x,0,x,3,x, 7,x,x,x,x,x,x,x,x,
        5,x,x,x,x,x,x, 3,x,x,x,x,x,x,x,x,  2,x,x,x,x,x,x,-5,x,x,x,x,x,x,x,x
    };
    static const char fluteline[64] =
    {
        12,x,12,12, x,9, x, 17,x,16,x,14,x,12,x,x,
         8,x, x,15,14,x,12,  x,7, x,x, x,x, x,x,x,
         8,x, x, 8,12,x, 8,  x,7, x,8, x,3, x,x,x,
         5,x, 7, x, 2,x,-5,  x,5, x,x, x,x, x,x,x
    };
    // Step1: Create a MIDI file
    MIDIfile file;
    // Step 2: Add Meta Event 0x06 (Marker Text) to add a text as marker
    file.AddLoopStart(); // Indicate that a loop starts

    // Choose instruments ("patches") for each channel for all 16 channels
    static const char patches[16] =
    {
        0,0,0, 52,52,52, 48,48,48, 0,0,0,0,0, 35,74
        // 0=piano, 52=choir aahs, 48=strings, 35=fretless bass, 74=pan flute
    };
    // Step 3: Append patches to the file as a bunch of system messages to add patches (0xC0|c, patches[c])
    for(unsigned c=0; c<16; ++c)
        if(c != 10) // Patch any channel except the percussion channel.
            file[0].Patch(c, patches[c]);

    int keys_on[16] = {-1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1, -1,-1,-1,-1};

    // CONTINUE HERE
    // Step 4:
    for(unsigned loops=0; loops<2; ++loops)
    {
        for(unsigned row=0; row<128; ++row)
        {
            // For all patches
            for(unsigned c=0; c<16; ++c)
            {
                int note = x, add = 0, vol = 127;
                if(c < 3) // Piano chord
                {
                    int chord = chordline[row%64];
                    if(chord != x)
                        note = chords[chord][c%3], add=12*5, vol=0x4B;
                }

                else if(c >= 3 && c < 5) // Aux chord (choir)
                {
                    int chord = chordline2[row%64];
                    if(chord != x)
                        note = chords[chord][c%3], add=12*4, vol=0x50;
                }

                else if(c >= 6 && c < 8) // Aux chord (strings)
                {
                    int chord = chordline2[row%64];
                    if(chord != x)
                        note = chords[chord][c%3], add=12*5, vol=0x45;
                }

                else if(c == 14) // Bass
                    note = bassline[row%64], add=12*3, vol=0x6F;

                else if(c == 15 && row >= 64) // Flute
                    note = fluteline[row%64], add=12*5, vol=0x6F;

                if(note == x && (c<15 || row%31))
                    continue;
                file[0].KeyOff(c, keys_on[c], 0x20);
                keys_on[c] = -1;
                if(note == x)
                    continue;
                file[0].KeyOn(c, keys_on[c] = note+add, vol);
            }
            file[0].AddDelay(160); // Add a delay of 160 between each row
        }
        if(loops == 0)
            file.AddLoopEnd();
    }

    // Step 5: start appending all created tracks as binary data in a MIDI file format
    file.Finish();

    // Open a new file
    FILE* fp = std::fopen("Practice30.mid", "wb");
    // and write all binary data from the midi file to the file opened
    std::fwrite(&file.at(0), 1, file.size(), fp);
    // close the file
    std::fclose(fp);
    return 0;
}
