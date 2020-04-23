ARG VER=0.4.2

FROM rrbutani/arm-llvm-toolchain:${VER}

ARG VER

RUN : \
 && apt-get update -y \
    -qq 2>/dev/null \
 && apt-get install -y \
      net-tools git

RUN : \
 && apt-get install -y \
      iproute2 sudo screen

RUN : \
 && curl -L https://raw.githubusercontent.com/rrbutani/tm4c-llvm-toolchain/${VER}/env/install.sh | bash \
 && curl -L https://raw.githubusercontent.com/posborne/cmsis-svd/master/data/TexasInstruments/TM4C123GH6PM.svd > /opt/TM4C123GH6PM.svd \
 && update-alternatives --install /usr/bin/arm-none-eabi-gdb arm-none-eabi-gdb $(which gdb-multiarch) 2


