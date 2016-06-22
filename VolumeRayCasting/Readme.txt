Build Instructions

====Mac OS====

1. Install Xcode from Mac App Store (located at /Applications/App Store.app)

2. Install Xcode command line tools (follow this guide: http://osxdaily.com/2014/02/12/install-command-line-tools-mac-os-x/)

3. Download and install Qt 5.x: http://qt-project.org/downloads
Use default options.

4. Open the project file VolumeRayCasting.pro in QtCreator

5. Follow the guide to config the project (there should be a configure button showing up at the beginning)

6. Press Ctrl+B to build

7. Press Ctrl+R to run

====Windows====

1. Install Visual Studio

2. Download and install Qt 5.x: http://qt-project.org/downloads
Make sure to select the right library version to install according to the Visual Studio version or compile the Qt library directly from the source.

3. Open the project file VolumeRayCasting.pro in QtCreator

4. Follow the guide to config the project (there should be a configure button showing up at the beginning)

5. In ‘Projects’ panel, choose ‘Add Build Step’ -> ‘Make’
Enter ‘install’ in the ‘Make arguments:’ box.

6. Press Ctrl+B to build

7. Press Ctrl+R to run

====Linux====

1. Install C++ compiler

2. Download and install Qt 5.x: http://qt-project.org/downloads
You may need to compile the Qt library from the source

3. You may need to install libglew-dev if you do not have it on your machine

4. Open the project file VolumeRayCasting.pro in QtCreator

5. In ‘Projects’ panel, choose ‘Add Build Step’ -> ‘Make’
Enter ‘install’ in the ‘Make arguments:’ box.

6. Press Ctrl+B to build

7. Press Ctrl+R to run
