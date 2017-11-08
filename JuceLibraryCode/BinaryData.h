/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   ITCFranklinGothicStdBook_otf;
    const int            ITCFranklinGothicStdBook_otfSize = 30824;

    extern const char*   ITCFranklinGothicStdMed_otf;
    const int            ITCFranklinGothicStdMed_otfSize = 31544;

    extern const char*   ITCFranklinGothicStdBkCp_otf;
    const int            ITCFranklinGothicStdBkCp_otfSize = 29524;

    extern const char*   ITCFranklinGothicStdBkCd_otf;
    const int            ITCFranklinGothicStdBkCd_otfSize = 31348;

    extern const char*   ITCFranklinGothicStdBkXCp_otf;
    const int            ITCFranklinGothicStdBkXCp_otfSize = 30060;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 5;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}
