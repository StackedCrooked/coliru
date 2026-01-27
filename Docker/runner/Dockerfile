FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        clang \
        libc++-dev \
        libc++abi-dev \
        ca-certificates \
        python3 \
    && rm -rf /var/lib/apt/lists/*

RUN useradd -m -u 2001 runner

WORKDIR /job
