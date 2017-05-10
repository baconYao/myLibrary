# FROM：開指定的image
FROM ubuntu:14.04
# 作者
MAINTAINER Pei-Yao Chang  "bacon735392@gmail.com"
# 最新更新日期，只要改動此行，下面都會重建(越容易變動的東西都要寫在越下面)
ENV VERSION "2017-05-10 V1.0"

RUN \
  apt-get update && \
  apt-get install -y vim gcc g++ make

RUN mkdir -p /myLibrary

COPY . /myLibrary

# Define working directory.
# 進container時，所在的目錄．
WORKDIR /myLibrary


