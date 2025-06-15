FROM mxe/mxe:latest

WORKDIR /build
COPY . /build

RUN mkdir build && \
    cmake -S . -B build \
      -DCMAKE_TOOLCHAIN_FILE=/usr/x86_64-w64-mingw32.shared/share/cmake/mxe-conf.cmake \
      -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build -j$(nproc)

CMD ["bash"]
