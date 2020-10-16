# lightConsole
part 2 contains the merging of sub controls into mainwindow.ui 

### docker image used 
-> docker pull vookimedlo/ubuntu-qt:latestDistroOfficial_gcc_xenial


// ubuntu

docker run -it -v /tmp/.X11-unix/:/tmp/.X11-unix -e DISPLAY=unix$DISPLAY  --name mCunt ubuntu


xhost +local:docker

// windows 
docker run -it --name mCunt vookimedlo/ubuntu-qt:latestDistroOfficial_gcc_xenial // to run w/o GUI

install -> https://sourceforge.net/projects/vcxsrv/files/latest/download


docker run --rm -it -e DISPLAY=192.168.10.9:0.0 --name mCunt vookimedlo/ubuntu-qt:latestDistroOfficial_gcc_xenial

docker cp build-LightProject-Desktop-Debug mCunt:/home/

// mac 

brew install socat
socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\"


brew install xquartz
open -a Xquartz

ip=$(ifconfig en0 | grep inet | awk '$1=="inet" {print $2}')

docker run  --name mCunt -it -e DISPLAY=$ip:0 -v /tmp/.X11-unix:/tmp/.X11-unix   vookimedlo/ubuntu-qt:latestDistroOfficial_gcc_xenial



// script to run on a already existing container

#/home/lightConsole/LightProject # runs the app

socat TCP-LISTEN:6000,reuseaddr,fork UNIX-CLIENT:\"$DISPLAY\" &

open -a Xquartz

docker start mCunt

docker exec mCunt /home/lightConsole/LightProject

