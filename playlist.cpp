// compile with -lwinmm to work
// -std=c++11

#include <windows.h>
#include <MMSystem.h>
#pragma comment(lib, "winmm.lib")

#include <iostream>
#include <conio.h>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>

/**********************************
Later Ideas
*class function to skip tracks (check)
*class function to choose track to play (check)
*figure out why file name can't be less than 4 characters & fix that(do later)
*figure out how to play next song automatically if they dont press anything
*make a friend class function for volume at some point
*************************************/

class Playlist {
  private:
    int num;
    std::vector<std::string> str;

  public:
//Default constructor
    Playlist(){
      num = 1;
      str.resize(num);
      for (int i=0; i < str.size(); ++i) {
        str.at(i) = "Loop99.wav";
        std::cout<<"Now playing Default Track:"<<std::endl;
        std::cout<<str.at(i)<<std::endl;
      }
    }

//read in names of .wav files if given through command line
    Playlist(std::vector<std::string> name){
      num = name.size();
      str.resize(num);
    //could also do this with pushback and .reserve() vector function

      for (int i=0; i < str.size(); ++i) {//i=size()-1 because of argc
        str.at(i) = name.at(i);
        std::cout<<str.at(i)<<std::endl;
      }
    }

//read in names of .wav files if given through a text file
    Playlist(std::ifstream& name){
      name >> num;
      str.resize(num);
    //could also do this with pushback and .reserve() vector function

      for (int i=0; i < str.size(); ++i) {
        name>> str.at(i);
        std::cout<<str.at(i)<<std::endl;
      }
    }

//Destructor
    ~Playlist(){}

//plays music
    void PlayMusic(int tracknum){
      int len;
      char choice;
      for(int i=tracknum; i < str.size(); ++i) {
        len = 0;
        len = str.at(i).size();
        std::cout<<"Playing Track "<<i+1<<std::endl;
//Checks if user wrote filename with a .wav at the end or not
        if (str.at(i).substr(len-4, 4) == ".wav"){
          PlaySound((str.at(i)).c_str(), NULL, SND_FILENAME|SND_ASYNC);
        }
        else {
          PlaySound((str.at(i) + ".wav").c_str(), NULL, SND_FILENAME|SND_ASYNC);
        }

//Allows you to pick what song to play next
        std::cin>>choice;

        switch(choice) {
          case 'a':
            PlayMusic(i-1);
            exit(-1);
          case 'w':
            PlayMusic(0);
            exit(-1);
          case 's':
            PlayMusic(str.size()-1);
            exit(-1);
        }
      }
    }

  //protected:
};

int main(int argc, char* argv[]) {
//if you don't put song names in command line
  if(argc < 2) {
    std::string choice;
    std::cout<<"Type 'yes' if you are going to be reading from a file"<<std::endl;
    std::cin>> choice;

    if(choice == "yes"){
        std::string namefile;
        std::cout<<std::endl<<"Type the name of the file"<<std::endl;
        std::cin>>namefile;

        //if they write it without .txt
        //if file name is less than 4 char, you must write .txt
        if(namefile.substr(namefile.size()-4, 4) != ".txt"){
          namefile.append(".txt");
        }

        std::ifstream file;
        file.open(namefile);
        if(!file.is_open()){
          std::cout<<"No file of that name exists in your folder"<<std::endl;
          std::cout<<"Exiting..."<<std::endl;
          return 1;
        }

        Playlist sndtrack3(file);
        std::cout<<"Press any key to skip to the next song"<<std::endl;
        std::cout<<"Press 'a' key to skip to the previous song"<<std::endl;
        std::cout<<"Press 'w' key to skip to the first song"<<std::endl;
        std::cout<<"Press 's' key to skip to the last song"<<std::endl;
        sndtrack3.PlayMusic(0);
    }

    else {
      Playlist sndtrack2;
      sndtrack2.PlayMusic(0);
    }

    return 0;
  }

  std::vector<std::string> Name(argc-1);

  for (int i=0; i < Name.size(); ++i) {
    Name.at(i) = argv[i+1];
  }

  Playlist sndtrack(Name);
  std::cout<<"Press any key to skip to the next song"<<std::endl;
  std::cout<<"Press 'a' key to skip to the previous song"<<std::endl;
  std::cout<<"Press 'w' key to skip to the first song"<<std::endl;
  std::cout<<"Press 's' key to skip to the last song"<<std::endl;
  sndtrack.PlayMusic(0);

  return 0;
}
