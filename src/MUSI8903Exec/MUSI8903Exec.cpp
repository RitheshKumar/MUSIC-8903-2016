
#include <iostream>
#include <ctime>
#include <fstream>

#include "MUSI8903Config.h"

#include "AudioFileIf.h"

using std::cout;
using std::endl;

// local function declarations
void    showClInfo ();

/////////////////////////////////////////////////////////////////////////////////
// main function
int main(int argc, char* argv[])
{
    std::string             sInputFilePath,                 //!< file paths
                            sOutputFilePath;

    long long               iInFileLength       = 0;        //!< length of input file

    clock_t                 time                = 0;

    float                   **ppfAudioData      = 0;

    CAudioFileIf            *phAudioFile        = 0;
    std::ofstream           fileOut("/Users/Rithesh/Desktop/fileOut.txt"); //Give absolute paths only!!

    showClInfo ();

    //////////////////////////////////////////////////////////////////////////////
    // parse command line arguments
    
    //////////////////////////////////////////////////////////////////////////////
    // variable declarations
    sInputFilePath = "/Users/Rithesh/Documents/MIR/Projects/Onset Detection/dev2/sine_100.wav";
    CAudioFileIf::FileSpec_t fileSpecs; //= new CAudioFileIf::FileSpec_t;
    CAudioFileIf::FileIoType_t eIoType = CAudioFileIf::kFileRead;
    Error_t errorMsg;
    int numChannels=0;
    
    //Get path manually
    //std::cin >> sInputFilePath;
    //////////////////////////////////////////////////////////////////////////////
    // allocate memory
    CAudioFileIf::create (phAudioFile);
    
    //////////////////////////////////////////////////////////////////////////////
    // open the input wave file
    errorMsg = phAudioFile->openFile ( sInputFilePath, eIoType );
    if ( errorMsg == kFileOpenError) {
        cout<< "Can't open file"<<endl;
    }
    
    
    // get audio data
    phAudioFile->getFileSpec(fileSpecs);
    phAudioFile->getLength(iInFileLength);
    numChannels= fileSpecs.iNumChannels;
    
    cout<<"Length:"<<iInFileLength<<endl;
    cout<<"NumChannels:"<<numChannels<<endl;
    
    ppfAudioData = new float*[numChannels];
    
    for (int i=0; i<numChannels; i++) {
        ppfAudioData[i] = new float[iInFileLength];
    }
    
    errorMsg = phAudioFile->readData (ppfAudioData, iInFileLength);
    if ( errorMsg == kFileAccessError) {
        cout<< "Can't read file"<<endl;
    }
    
    //////////////////////////////////////////////////////////////////////////////
    // get audio info and print it to std out
    
    for ( int i = 0; i<numChannels; i++) {
        for (int j=0; j<iInFileLength; j++) {
            cout<< ppfAudioData[i][j] << endl;
            fileOut << ppfAudioData[i][j] << endl;
        }
    }

    //////////////////////////////////////////////////////////////////////////////
    // do processing
    cout << "Hello there!" << endl << endl;

    //////////////////////////////////////////////////////////////////////////////
    // clean-up
    
    for (int i=0; i<numChannels; i++) {
        delete [] ppfAudioData[i];
    }

    delete [] ppfAudioData;
    
    CAudioFileIf::destroy(phAudioFile);
    
    

    return 0;
    
}


void     showClInfo()
{
    cout << "GTCMT MUSI8903" << endl;
    cout << "(c) 2016 by Alexander Lerch" << endl;
    cout  << endl;

    return;
}

