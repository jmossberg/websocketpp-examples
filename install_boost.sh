#!/bin/bash

BOOST_VERSION=$1

BOOST_VERSION_UNDERSCORE=$(echo ${BOOST_VERSION} | sed 's/\./_/g')
BOOST_TAR_BZ2_FILE=boost_${BOOST_VERSION_UNDERSCORE}.tar.bz2
BOOST_SRC_DIR=${HOME}/src/boost
BOOST_LIB_DIR=${HOME}/lib/boost

echo "Install Boost ${BOOST_VERSION} to ${BOOST_LIB_DIR}/boost_${BOOST_VERSION_UNDERSCORE}"

mkdir -p ${BOOST_SRC_DIR}
mkdir -p ${BOOST_LIB_DIR} 

wget https://dl.bintray.com/boostorg/release/${BOOST_VERSION}/source/${BOOST_TAR_BZ2_FILE} --directory-prefix=${BOOST_SRC_DIR}
tar -xj -C ${BOOST_SRC_DIR} -f ${BOOST_SRC_DIR}/${BOOST_TAR_BZ2_FILE}
rm ${BOOST_SRC_DIR}/${BOOST_TAR_BZ2_FILE}
pushd ${BOOST_SRC_DIR}/boost_${BOOST_VERSION_UNDERSCORE}
./bootstrap.sh --with-libraries=system --prefix=${BOOST_LIB_DIR}/boost_${BOOST_VERSION_UNDERSCORE}
./b2 install
popd