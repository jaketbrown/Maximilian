FROM debian:stable-slim as builder


RUN \
  apt-get update && \
  apt-get install -y build-essential llvm cmake clang


COPY . /Maximilian
RUN mkdir -p /Maximilian/build
WORKDIR /Maximilian/build

RUN cmake -DCMAKE_CXX_STANDARD=20 -DMAXI_BUILD_FUZZER=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
RUN cmake --build .

FROM  debian:stable-slim
COPY --from=builder /AudioFile/build/mayhem/testsuite/ /mayhem/testsuite
COPY --from=builder /AudioFile/build/mayhem/Maximilian_fuzz /Maximilian_fuzz
