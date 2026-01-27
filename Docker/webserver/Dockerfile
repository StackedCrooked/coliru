FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        ruby \
        ruby-dev \
        ruby-webrick \
        rubygems \
        build-essential \
        libssl-dev \
        libcap2-bin \
        lsof \
        rsync \
        subversion \
        ca-certificates \
        docker.io \
    && rm -rf /var/lib/apt/lists/*

RUN gem install sinatra shotgun popen4 json sinatra-cross_origin rackup webrick --no-document

RUN useradd -m -u 2001 webserver

WORKDIR /opt/coliru
COPY . /opt/coliru

RUN mkdir -p /Archive /Archive2 /tmp/coliru \
    && chown -R webserver:webserver /tmp/coliru

ENV COLIRU_URL=0.0.0.0
ENV COLIRU_PORT=8080

WORKDIR /opt/coliru/Web
USER webserver

ENTRYPOINT ["bash", "-lc", "source coliru_env.source; ruby webserver-sinatra.rb -o ${COLIRU_URL}"]
