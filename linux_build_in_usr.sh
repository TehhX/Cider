#! /bin/bash

# linux_build_in_usr.sh
# Builds Cider, places cider.h in /usr/include/ and libcider.so in /usr/lib/. Requires root to access /usr/.

if [ $UID != 0 ]
then
    echo "You must run this as root via su or sudo to access /usr/."
    exit 1
fi

# Must be ran in same directory.
if [ ! -f "linux_build_in_usr.sh" ]
then
    echo "You must run this script in the same directory as itself."
    exit 1
fi

# Builds as a shared library, as it is being put into /usr/lib.
cmake -DLIB_TYPE=SHARED -S ./ -B ./build
cmake --build ./build/

# Give user ownership of build folder after potentially creating with root owner.
chown -R $(logname) ./build/

# These are the commands for which root access is required.
cp -v build/libcider.so /usr/lib && cp -v include/cider.h /usr/include
