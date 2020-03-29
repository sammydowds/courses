// Helper functions for music

#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    float num = fraction[0] - '0';

    float den = fraction[2] - '0';

    float frac = (float) (num/den);

    float one_eight = 1.00/8.00;

    int fract = (int) (frac/ one_eight);

    return fract;

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    int len_note = strlen(note);
    int b = note[1] - '0';
    printf("%c", b);
    int octave = 0;
    bool sharp_flat = false;
    //finding octave and if there is a sharp or flat
    if (len_note < 3)
    {
        octave = note[1] - '0';
    }
    else
    {
        octave = note[2] - '0';
        sharp_flat = true;
    }

    //finding difference between octaves, and caclulating frequency relative to not A with 4th octave
    int diff_octave = abs(octave - 4) + 1;
    float freq = 0;
    if (octave >= 4)
    {
        freq = 440 * diff_octave;
    }
    else if (octave < 4)
    {
        freq = 440 / diff_octave;
    }




    //if the note had flat or sharp, impliment this into the frequency found above
    float semi_note = pow((float) 2, (float) 1/12);

    if (sharp_flat == true)
    {
        char flat = 'b';
        char sharp = '#';

        if (note[1] == flat)
        {
            freq= freq / semi_note;
        }
        else if (note[1] == sharp)
        {
            freq = freq * semi_note;
        }


    }

    //Hardcoding the difference between notes for adjusting by difference of note relative to A (how many semitones different)

    if (note[0] == 'B')
    {
        freq = freq * (pow((float) 2, (float) 1/12));
    }

    else if (note[0] == 'G')
    {
        freq = freq / (pow((float) 2, (float) 2/12));
    }
    else if (note[0] == 'F')
    {
        freq = freq / (pow((float) 2, (float) 4/12));
    }
    else if (note[0] == 'E')
    {
        freq = freq / (pow((float) 2, (float) 5/12));
    }
    else if (note[0] == 'D')
    {
        freq = freq / (pow((float) 2, (float) 7/12));
    }
    else if (note[0] == 'C')
    {
        freq = freq / (pow((float) 2, (float) 9/12));
    }

    return (int) freq;



}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    bool check = false;
    if (s[0] == '\0')
    {
        check = true;
        return true;
    }
    else
    {
        return false;
    }
}
