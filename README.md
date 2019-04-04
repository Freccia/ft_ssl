# ft_ssl

OpenSSL reinplementation for educational purpose.

### This is work in progress !

# Cloning

Clone the repository the following way:
```
git clone git://github.com/freccia/ft_ssl.git
cd ft_ssl
git submodule update --init --recursive
```

# Compile

To compile simply run `make`

Available compile commands: `make all` ; `make clean` ; `make fclean` ; `make re`

# Algorithms

Right now the project includes the following algorithms:
- MD5
- SHA 256
- BASE 64
- DES CBC (work in progress)

# Usage

```
$ ./ft_ssl
Usage: ./ft_ssl [ options ] (command) [ options ]
		-h : Show this help message
digests: md5, sha256
ciphers: base64
```

