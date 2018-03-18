FROM ubuntu:18.04

RUN apt-get update
RUN apt-get install -y language-pack-ja-base language-pack-ja
ENV LANG=ja_JP.UTF-8

RUN apt-get -y install git wget

WORKDIR /opt
RUN wget https://github.com/ku-nlp/jumanpp/releases/download/v2.0.0-rc2/jumanpp-2.0.0-rc2.tar.xz
RUN apt-get -y install xz-utils
RUN tar xf jumanpp-2.0.0-rc2.tar.xz
WORKDIR jumanpp-2.0.0-rc2
RUN mkdir cmake-build-dir
WORKDIR cmake-build-dir

RUN apt-get -y install cmake
#RUN echo "deb http://ftp.debian.org/debian/ stretch main" >> /etc/apt/sources.list

RUN apt-get -y install protobuf-compiler
RUN apt-get -y install g++

RUN cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr
RUN make install

