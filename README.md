# Install cmake
1. Use package manager to install cmake or get from: 
    https://cmake.org/download/

# Install SFML
1. Download SFML 2.4.2 from:
    https://github.com/SFML/SFML/archive/2.4.2.tar.gz
2. Extract SFML (tar -xvzf SFML-2.4.2.tar.gz)
3. cd into SFML-2.4.2
4. mkdir build
5. cd build
6. cmake ../
7. make
8. sudo make install

# Install TGUI
1. Download TGUI 0.7.4 from:
    https://github.com/texus/TGUI/archive/0.7.4.tar.gz
2. Extract TGUI (tar -xvzf TGUI-0.7.4.tar.gz)
3. cd into TGUI-0.7.4
4. mkdir build
5. cd build
6. cmake ../
7. make
8. sudo make install

# Build this project
1. mkdir build
2. cd build
3. cmake ../
4. make

# To run singleplayer:
1. ./client
2. Select second button up from bottom 'Play Locally'

# To run multiplayer:
1. Start server: ./server   (separate window)
2. Start client 1: ./client (separate window)
3. Start client 2: ./client (separate window)
4. In client 1: type 'localhost' for address, '1' for player number, then hit connect
5. In client 2: type 'localhost' for address, '2' for player number, then hit connet
