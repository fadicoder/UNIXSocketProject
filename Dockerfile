FROM gcc:latest

COPY . /usr/app

WORKDIR /usr/app

RUN cd lib && make clean && make
RUN cd client && make clean && make
RUN cd server && make clean && make
