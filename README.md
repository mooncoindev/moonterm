### moonterm 

forked from the brilliant BITC codebase @ https://github.com/bit-c/bitc
out of respect to the original author i've left the compiled name as the original; the original client still works on the btc network to this day!

bitc is a *thin* SPV mooncoin client.
* 100% C code,
* support for linux, mac, OpenBSD platforms,
* console based: uses ncurses,
* home grown async network i/o stack,
* home grown poll loop,
* home grown bitcoin engine,
* supports encrypted wallet,
* supports connecting via Tor/Socks5,
* multi-threaded,
* valgrind clean.

**WARNING:** this app is under development and may contain critical bugs.

---

#### Dependencies

 - cJSON: a C library to parse JSON objects. It's released under MIT license.
        http://sourceforge.net/projects/cjson/
 - libcurl: an http library. It's released under a MIT/X derivate license.  
	http://curl.haxx.se/libcurl/
 - LevelDB: Google's key value store, released under the BSD 3-Clause License.  
	https://github.com/google/leveldb
 - OpenSSL: crypto library.  
        https://www.openssl.org/

---

#### Install
##### Debian 8.6 (x64) 

You first need to install the libraries this app uses:
# apt-get update
# apt-get install -y git make libssl-dev libcurl4-openssl-dev libncurses5-dev libleveldb-dev libsnappy-dev build-essential

then clone the git repository:
# git clone https://github.com/mooncoindev/moonterm.git

finally build and launch:
# cd bitc && make
# ./bitc

#### Usage

The first time you launch the app, a message will notify you
of the list of files & directory it uses.

bitc uses the folder `~/.moonterm` to store various items:

|    what              |    where                    | avg size |
|:---------------------|:----------------------------|:--------:|
| block headers        | ~/.moonterm/headers.dat     | ~ 20MB   |
| peer IP addresses    | ~/.moonterm/peers.dat       |  ~ 2MB   |
| transaction database | ~/.moonterm/txdb            |  < 1MB   |
| config file          | ~/.moonterm/main.cfg        |  < 1KB   |
| wallet keys          | ~/.moonterm/wallet.cfg      |  < 1KB   |
| tx-label file        | ~/.moonterm/tx-labels.cfg   |  < 1KB   |
| contacts file        | ~/.moonterm/contacts.cfg    |  < 1KB   |


A log file is generated in `/tmp/bitc-$USER.log`.

To navigate the UI:
 - `<left>` and `<right>` allow you to change panel,
 - `<CTRL>` + `t` to initiate a transaction,
 - type `q` or `back quote` to exit.

---

#### Encrypted wallet

bitc has support for encrypted wallets. The first time you launch the app, it will
automatically generate a new bitcoin address for you, and the wallet file will
have private key **unencrypted**.

To turn on encryption, or to change the encryption password:
```
  # ./bitc -e
```

The next time you launch the app, you may or may not specify `-p` on
the command line. If you do, you will be able to initiate transactions. If you
do not the dashboard will still be functional but you won't be able to
initiate transactions.

Note that bitc encrypts each private key separately.

**WARNING:** please remember to make back-ups.

---

#### Importing existing keys

You need to modify your `~/.moonterm/wallet.cfg` so that it contains the private
key as exported by mooncoin-qt/mooncoind with the command `dumpprivkey`. More on that
later.

---

#### TOR / SOCKS5 support

Bitc can route all outgoing TCP connections through a socks5 proxy. Since TOR
implements a SOCKS5 proxy, you just need to put the entry:
```
	network.useSocks5="true"
```
in your main config file to use bitc over Tor (for a local Tor client). If the
Tor proxy is not running locally, you need to modify the config options:
```
 	socks5.hostname="localhost"
	socks5.port=9050
```
.. in the file `~/.moonterm/main.cfg`. The default `hostname:port` is
`localhost:9050` on linux, and `localhost:9150` on mac.

---

#### Watch-only Addresses

If you tag a key as
```
   key0.spendable = "FALSE"
```
in your `~/.mooncoin/wallet.cfg`, bitc won't attempt to spend the mooncoins held by
this address. This is not quite like a watch-only address, but we'll get there
eventually.

---

#### Problem?

There are still a variety of things that need to be fixed or implemented (cf [TODO
file](TODO.md)), and some of these may explain the behavior you're seeing.  If moonterm 
crashes, please collect the log file along with the core dump and open a ticket
on github:  

	https://github.com/mooncoindev/moonterm/issues

---

#### Feedback, comments?

Feel free to reach out to me if you have any feedback or if you're planning to
use this code in interesting ways.

   mailto:austruym@gmail.com
   PGP: 1C774FA3925A3076752B2741054E32DFBEE883DB
   
   (or for moonterm port)
   barrysty1e on the bitcointalk forums
