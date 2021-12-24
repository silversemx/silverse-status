ARG CMONGO_VERSION=1.0b-13
ARG CERVER_VERSION=2.0b-40

ARG BUILD_DEPS='ca-certificates git libssl-dev libcurl4-openssl-dev'
ARG RUNTIME_DEPS='ca-certificates libssl-dev libcurl4-openssl-dev'

FROM ermiry/mongoc:builder as builder

WORKDIR /opt

ARG BUILD_DEPS
RUN apt-get update && apt-get install -y ${BUILD_DEPS}

# build cmongo with production flags
ARG CMONGO_VERSION
RUN mkdir /opt/cmongo && cd /opt/cmongo \
    && wget -q --no-check-certificate https://github.com/ermiry-com/cmongo/archive/${CMONGO_VERSION}.zip \
    && unzip ${CMONGO_VERSION}.zip \
    && cd cmongo-${CMONGO_VERSION} \
    && make TYPE=production -j4 && make TYPE=production install

# build cerver with production flags
ARG CERVER_VERSION
RUN mkdir /opt/cerver && cd /opt/cerver \
    && wget -q --no-check-certificate https://github.com/ermiry/cerver/archive/${CERVER_VERSION}.zip \
    && unzip ${CERVER_VERSION}.zip \
    && cd cerver-${CERVER_VERSION} \
    && make TYPE=production -j4 && make TYPE=production install

RUN ldconfig

# silverse
WORKDIR /opt/silverse
COPY . .
RUN make TYPE=production -j4

############
FROM ermiry/mongoc:latest

ARG RUNTIME_DEPS
RUN apt-get update && apt-get install -y ${RUNTIME_DEPS}

# cmongo
ARG CMONGO_VERSION
COPY --from=builder /opt/cmongo/cmongo-${CMONGO_VERSION}/bin/libcmongo.so /usr/local/lib/
COPY --from=builder /opt/cmongo/cmongo-${CMONGO_VERSION}/include/cmongo /usr/local/include/cmongo

# cerver
ARG CERVER_VERSION
COPY --from=builder /opt/cerver/cerver-${CERVER_VERSION}/bin/libcerver.so /usr/local/lib/
COPY --from=builder /opt/cerver/cerver-${CERVER_VERSION}/include/cerver /usr/local/include/cerver

RUN ldconfig

# silverse
WORKDIR /home/silverse
COPY ./start.sh .
COPY --from=builder /opt/silverse/bin ./bin

CMD ["/bin/bash", "start.sh"]
