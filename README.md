Herbsters - HERBS
========================
Install Tutorials & Download Source on Windows and Linux and Android

Home Page: http://herbsters.com

Web Wallet - Receive and Withdraw: http://herbswallet.com

Mining Pool - Stratum : USB, ASIC: http://pool.herbsters.com

Block Explorer - Height, TX, Address: http://explorer.herbsters.com

Android App in the Play Store: HerbsWallet

Faucet - Earn HERBS coins; refill hourly: http://herbsfaucet.com

API Data - Latest Statistics: http://api.herbsters.com

Casino - Bonus, Claim, Roulette, BlackJack, Poker, Slots: http://herbscasino.com

What is herbsters?
----------------

herbsters is an experimental digital currency that enables instant payments to
anyone, anywhere in the world. herbsters uses peer-to-peer technology to operate
with no central authority: managing transactions and issuing money are carried
out collectively by the network. herbsters Core is the name of open source
software which enables the use of this currency.

For more information, as well as an immediately useable, binary version of
the herbsters Core software, see [http://herbsters.com](http://herbsters.com).

License
-------

herbsters Core is released under the terms of the MIT license. See [COPYING](COPYING) for more
information or see https://opensource.org/licenses/MIT.

Development Process
-------------------

Developer IRC can be found on irc.location.best at #herbsters.

Testing
-------

Windows: Working

Linux: Working

Macintosh: Unknown

Android: Working

For more information and source downloads and instructions visit http://herbsters.com

#                      #
# Ubuntu 18.04 - 22.04 #
#                      #

# first install the requirements
# then download and compile

###########################################

# Required
Start Here First on Fresh Install

###########################################

# Update Repository Source

sudo apt-get update

# Github & Packages

sudo apt-get install git

sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils libseccomp-dev libcap-dev

# Add Universe & Boost

sudo add-apt-repository universe

sudo add-apt-repository multiverse

sudo apt-get update

sudo apt-get install libboost-all-dev

# Berkeley Database

# Option #1

sudo apt-get install libdb-dev libdb++-dev

# Option #2

sudo add-apt-repository ppa:bitcoin/bitcoin

sudo apt-get update

sudo apt-get install libdb4.8-dev libdb4.8++-dev

# Option #3 - Build from Source

wget 'http://download.oracle.com/berkeley-db/db-4.8.30.NC.tar.gz'

sudo tar -xzvf db-4.8.30.NC.tar.gz

sed -i 's/__atomic_compare_exchange/__atomic_compare_exchange_db/g' db-4.8.30.NC/dbinc/atomic.h

sudo cd db-4.8.30.NC/build_unix/

sudo ../dist/configure --enable-cxx

sudo make

sudo make install

# Tell Your System Where to Find Berkeley
 
export BDB_INCLUDE_PATH="/usr/local/BerkeleyDB.4.8/include"

export BDB_LIB_PATH="/usr/local/BerkeleyDB.4.8/lib"

sudo ln -s /usr/local/BerkeleyDB.4.8/lib/libdb-4.8.so /usr/lib/libdb-4.8.so

########################################

NOW Compile herbsters from github source

########################################

git clone http://github.com/herbsters/herbsters.git

cd herbsters

./autogen.sh

./configure --with-incompatible-bdb
./configure --with-incompatible-bdb --with-boost-libdir=/usr/lib/x86_64-linux-gnu/

make

#############################################
DEBUG: On Ubuntu 20.04 + and make errors
Lib Boost Version 1.54
#############################################

sudo apt-get update

sudo apt-get -y --purge remove libboost-all-dev libboost-doc libboost-dev

sudo rm -f /usr/lib/libboost_*

sudo apt-get -y install build-essential g++ autotools-dev libicu-dev libbz2-dev

wget http://downloads.sourceforge.net/project/boost/boost/1.54.0/boost_1_54_0.tar.gz

tar -zxvf boost_1_54_0.tar.gz

cd boost_1_54_0

./bootstrap.sh

sudo ./b2 --with=all -j 2 install

#############################################
# path directory

vi ~/.profile

export PATH=$PATH:/home/USERNAME/herbsters/src

source ~/.profile

# Configuration File

vi /home/USERNAME/.herbsters/herbsters.conf

server=1

txindex=1

rpcuser=YOURUSER

rpcpassword=YOURSECRETPASSWORD

rpcport=7998

port=7999

rpcbind=0.0.0.0

rpcallowip=0.0.0.0/0

rpcallowip=127.0.0.1

rpcallowip=YOUR_IP_ADDRESS

daemon=1

gen=1

listen=1

addnode=149.28.46.64:7999

addnode=45.77.144.188:7999

# Application: Start & Controls

herbstersd -deprecatedrpc=accounts -daemon

herbsters-cli getinfo

herbsters-cli getbalance

herbsters-cli getblocktemplate

herbsters-cli getaccountaddress ""

herbsters-cli sendtoaddress "ADDRESS" AMOUNT

herbsters-cli move "#" "" AMOUNT

For more information Please visit:
http://herbsters.com
