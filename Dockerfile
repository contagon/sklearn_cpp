FROM python:slim
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=America/Denver

RUN apt-get -y update
RUN apt-get -y upgrade
RUN apt-get install -qy build-essential git cmake g++ libhdf5-serial-dev

RUN git clone https://gitlab.com/libeigen/eigen.git
RUN cd eigen && mkdir build && cd build && cmake .. && make install

RUN git clone --recursive https://github.com/skulumani/fdcl-hdf5.git
RUN cd fdcl-hdf5 && mkdir build && cd build && cmake .. && make install
ENV CPATH="/usr/include/hdf5/serial/:${CPATH}"

RUN pip install scikit-learn h5py

CMD /bin/bash