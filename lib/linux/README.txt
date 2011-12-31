The only package built is for this is AntTweakBar (see Libraries/Linux/AntTweakBar). The library file (libAntTweakBar.so) should be copied to the appropriate directories - usually /usr/local/lib. The folder should also contain a system link (called libAntTweakBar.so.1) the library. To perform these operations, from within "Libraries/Linux/AntTweakBar/lib" execute:
        sudo cp libAntTweakBar.so /usr/local/lib
        sudo ln -s /usr/local/lib/libAntTweakBar.so /usr/local/lib/libAntTweakBar.so.1
        
You must ensure LD_LIBRARY_PATH contains /usr/local/lib to get this working:
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
        
It may be wise to add the above line to ~/.bashrc so it always exists.

You must install OpenGL, GLEW and GLUT manually (plus compiler g++).
Under Ubuntu, the compilers and basic libs can be installed with the command:
        sudo apt-get install build-essential

To install OpenGL libraries:
        sudo apt-get install libgl1-mesa-dev libgl1-mesa-glx

To install GLEW:
        sudo apt-get install libglew1.5 libglew1.5-dev
        
To install freeglut:
        sudo apt-get install freeglut3 freeglut3-dev
        
To install GLU:
        sudo apt-get install libglu1-mesa libglu1-mesa-dev

It should be possible to compile under Linux with:
        g++ *.cpp -lGL -lGLU -lGLEW -lglut -lAntTweakBar -lrt -msse3 -I ../Libraries/Linux/AntTweakBar/include/ -o app

Note: library names are case sensitive. In the command, -msse3 is used to enable SSE3 support, -lrt is for clock support (used by PerfTimer) and the folder after -I points to the AntTweakBar include file. The build command is contained in buildlinux.sh (in oglscratch source directory) for ease (and speed) of building
        
