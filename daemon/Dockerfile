FROM ubuntu:latest

WORKDIR /task

COPY deb/dbus-framework.deb dbus-framework.deb

RUN apt update && apt install dbus libdbus-1-dev

#RUN g++ /src/main.cpp -std=c++20 -ldbus-1 -I/usr/include/dbus-1.0 -I/usr/lib64/dbus-1.0/include -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -ldbus-1 -Werror -Wall -Wextra

#ENTRYPOINT ["service dbus start"]