Herbsters - HERBS
========================
Install Tutorials & Download Source on Windows and Linux and Android

Home Page: http://herbsters.com

Web Wallet - Receive and Withdraw: http://herbswallet.com

Mining Pool - Stratum : USB, ASIC: http://pool.herbsters.com

Block Explorer - Height, TX, Address: http://explorer.herbsters.com

Android App in the Play Store: HerbsWallet

Faucet - Earn 0.125 HERBS; refill hourly: http://herbsfaucet.com

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

#              #
# Ubuntu 18.04 #
#              #

# download and install

git clone http://github.com/herbsters/herbsters.git

cd herbsters

./autogen.sh

./configure --with-incompatible-bdb

make

# path directory

vi ~/.profile

export PATH=$PATH:/home/USERNAME/herbsters/src

source ~/.profile

# onfiguration File

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

# Application: Start & Controls

herbstersd -deprecatedrpc=accounts -daemon
herbsters-cli getinfo
herbsters-cli getbalance
herbsters-cli getblocktemplate
herbsters-cli getaccountaddress ""
herbsters-cli sendtoaddress "ADDRESS" AMOUNT
herbsters-cli move "#" "" AMOUNT

###########################################
Required: Start Here First on Fresh Install
###########################################

# Update Repository Source

sudo apt-get update

# Github & Packages

sudo apt-get install git

sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils libseccomp-dev libcap-dev

# Add Universe & Boost

sudo add-apt-repository universe

sudo apt-get update

sudo apt-get install libboost-all-dev

# Berkeley Database

# Option #1

sudo add-apt-repository ppa:bitcoin/bitcoin

sudo apt-get update

sudo apt-get install libdb4.8-dev libdb4.8++-dev

# Option #2

sudo apt-get install libdb-dev libdb++-dev

# Update Repository Source

sudo apt-get update

# Github & Packages

sudo apt-get install git

sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils libseccomp-dev libcap-dev

# Add Universe & Boost
sudo add-apt-repository universe
sudo apt-get update
sudo apt-get install libboost-all-dev

# Berkeley Database

# Option #1

sudo add-apt-repository ppa:bitcoin/bitcoin

sudo apt-get update

sudo apt-get install libdb4.8-dev libdb4.8++-dev

# Option #2

sudo apt-get install libdb-dev libdb++-dev

########################################
NOW Compile herbsters from github source
########################################

For more information Please visit:
http://crypto.location.best/index.php?e=software
