# 🧅 Toralizer: SOCKS4 Proxy Client in C

**Toralizer** is a lightweight SOCKS4 proxy client written in C that allows you to connect to any target IP and port through a SOCKS4 proxy — such as the Tor network (`127.0.0.1:9050`). It is useful for penetration testing, anonymity routing, and network experiments.

---

## ✨ Features

- Connects to any IPv4 host through a SOCKS4 proxy
- Compatible with the Tor proxy
- Minimal C implementation with no external dependencies
- Useful for testing Tor connectivity and proxy setups

---

## 🔧 Requirements

- GCC or any C compiler
- Linux or Unix-like OS (macOS, WSL, etc.)
- Tor (if routing through the Tor network)

---

## 📁 Project Structure
  |
  ├── toralizer.c # Main C source file
  ├── toralizer.h # Header file defining request/response structs
  └── README.md # Project documentation

## ⚙️ Installation & Compilation

 >> gcc toralizer.c -o toralizer 


🚀 Usage

./toralizer <destination_ip> <destination_port>
Example
./toralizer 93.184.216.34 80


CONNECTION ESTABLISHED TO PROXY
Successfully connected through proxy to 93.184.216.34:80
🔍 SOCKS4 Request Format
The proxy request structure follows the SOCKS4 protocol:
+----+----+----+----+----+----+----+----+----+----+....+----+
| VN | CD |   DSTPORT   |     DSTIP      |  USERID     |NULL|
+----+----+----+----+----+----+----+----+----+----+....+----+
VN: SOCKS version number (0x04)

CD: Command code (0x01 for CONNECT)

DSTPORT: 2 bytes, big-endian

DSTIP: 4 bytes

USERID: Null-terminated string (up to 8 bytes)

🧪 Testing with Tor
Start the Tor service:

sudo service tor start
By default, Tor listens on 127.0.0.1:9050 as a SOCKS proxy.

Then run:

./toralizer <target_ip> <port>
To test against example.com, convert its domain to IP first:

host example.com
❗ Troubleshooting
connect: Connection refused → Tor isn't running on port 9050

Unable to traverse the proxy, error code: 91 → Request was rejected by the proxy

📜 License
MIT License — free for personal and commercial use.


🤝 Contributions
Contributions, suggestions, and forks are welcome. Future improvements could include:
SOCKS5 support
SOCKS4a (domain name) support
Integration with libcurl for anonymous HTTP requests
