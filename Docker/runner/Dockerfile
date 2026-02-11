FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        clang \
        libc++-dev \
        libc++abi-dev \
        ca-certificates \
        curl \
        python3

RUN useradd -m -u 2001 runner

COPY entrypoint.sh /runner/entrypoint.sh
RUN chmod +x /runner/entrypoint.sh

WORKDIR /job

#
# Additional dependencies
#

# OpenSSL
RUN apt-get install -y --no-install-recommends \
    libssl-dev

# Boost
ARG BOOST_VERSION=1.88.0
RUN set -eux; \
    boost_version_underscore="$(printf '%s' "${BOOST_VERSION}" | tr '.' '_')"; \
    boost_archive="boost_${boost_version_underscore}.tar.gz"; \
    boost_url="https://archives.boost.io/release/${BOOST_VERSION}/source/${boost_archive}"; \
    cd /tmp; \
    curl -fsSLO "${boost_url}"; \
    tar -xzf "${boost_archive}"; \
    cd "boost_${boost_version_underscore}"; \
    ./bootstrap.sh; \
    ./b2 --layout=system variant=release threading=multi link=static toolset=gcc -j"$(nproc)" install; \
    cd /; \
    rm -rf "/tmp/boost_${boost_version_underscore}" "/tmp/${boost_archive}"
