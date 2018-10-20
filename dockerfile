FROM ubuntu:18.10

RUN apt update && apt install --no-install-recommends -y \
    build-essential \
    cmake \
    git \
    python

ENTRYPOINT [ "/bin/bash" ]
