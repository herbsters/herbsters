herbsters Core
=============

Setup
---------------------
herbsters Core is the original herbsters client and it builds the backbone of the network. It downloads and, by default, stores the entire history of herbsters transactions (which is currently more than 7 GBs); depending on the speed of your computer and network connection, the synchronization process can take anywhere from a few hours to a day or more.

To download herbsters Core, visit [herbsters.org](https://herbsters.org).

Running
---------------------
The following are some helpful notes on how to run herbsters on your native platform.

### Unix

Unpack the files into a directory and run:

- `bin/herbsters-qt` (GUI) or
- `bin/herbstersd` (headless)

### Windows

Unpack the files into a directory, and then run herbsters-qt.exe.

### OS X

Drag herbsters-Core to your applications folder, and then run herbsters-Core.

### Need Help?

* See the documentation at the [herbsters Wiki](https://herbsters.info/)
for help and more information.
* Ask for help on [#herbsters](http://webchat.freenode.net?channels=herbsters) on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net?channels=herbsters).
* Ask for help on the [herbstersTalk](https://herbsterstalk.io/) forums.

Building
---------------------
The following are developer notes on how to build herbsters on your native platform. They are not complete guides, but include notes on the necessary libraries, compile flags, etc.

- [OS X Build Notes](build-osx.md)
- [Unix Build Notes](build-unix.md)
- [Windows Build Notes](build-windows.md)
- [OpenBSD Build Notes](build-openbsd.md)
- [Gitian Building Guide](gitian-building.md)

Development
---------------------
The herbsters repo's [root README](/README.md) contains relevant information on the development process and automated testing.

- [Developer Notes](developer-notes.md)
- [Release Notes](release-notes.md)
- [Release Process](release-process.md)
- [Source Code Documentation (External Link)](https://dev.visucore.com/herbsters/doxygen/)
- [Translation Process](translation_process.md)
- [Translation Strings Policy](translation_strings_policy.md)
- [Travis CI](travis-ci.md)
- [Unauthenticated REST Interface](REST-interface.md)
- [Shared Libraries](shared-libraries.md)
- [BIPS](bips.md)
- [Dnsseed Policy](dnsseed-policy.md)
- [Benchmarking](benchmarking.md)

### Resources
* Discuss on the [herbstersTalk](https://herbsterstalk.io/) forums.
* Discuss general herbsters development on #herbsters-dev on Freenode. If you don't have an IRC client use [webchat here](http://webchat.freenode.net/?channels=herbsters-dev).

### Miscellaneous
- [Assets Attribution](assets-attribution.md)
- [Files](files.md)
- [Fuzz-testing](fuzzing.md)
- [Reduce Traffic](reduce-traffic.md)
- [Tor Support](tor.md)
- [Init Scripts (systemd/upstart/openrc)](init.md)
- [ZMQ](zmq.md)

License
---------------------
Distributed under the [MIT software license](/COPYING).
This product includes software developed by the OpenSSL Project for use in the [OpenSSL Toolkit](https://www.openssl.org/). This product includes
cryptographic software written by Eric Young ([eay@cryptsoft.com](mailto:eay@cryptsoft.com)), and UPnP software written by Thomas Bernard.
