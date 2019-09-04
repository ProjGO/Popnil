# FootBook

## Intro

This is not a normal open sourse project and may be unsafe.

## Installation

###Pre-build configure guide

MariaDB is needed. This is written in pure C and depends on GTK+-2.0
#### For Debian GNU/Linux and Ubuntu

```bash
sudo apt update
sudo apt install mariadb-client mariadb-client libmariadbd-dev build-essencial cmake libgtk2.0-dev
```

#### Fedora

```bash
sudo dnf update
sudo dnf install mariadb mariadb-server mariadb-devel gcc make pkgconfig cmake gtk2-devel

# If you want to setup a root password
sudo mysql_secure_installation 

firewall-cmd --permanent --add-port=3306/tcp
```

#### Arch Linux

```bash
sudo pacman -Sy
sudo pacman -S mariadb mariadb-clients gcc cmake make gtk2 pkgconf
sudo mysql_install_db --user=mysql --basedir=/usr --datadir=/var/lib/mysql
```

To start the database, please

```bash
# Start it immediately
sudo systemctl start mariadb.service

# Start it on boot
sudo systemctl enable mariadb.service

# Start it immediately and on boot
sudo systemctl enable --now mariadb.service
```

Then, to add a user named "ProjGO", run the SQL in server/ProjGO.sql as root.
To establish the database "FootBook", run the SQLs in server/database.sql as ProjGO.

### Start building

```bash
mkdir -f cmake-build-debug/
cmake -B cmake-build-debug/
cd cmake-build-debug/
make client server
```

### Run the server

```bash
./server
```

### Run the client

```bash
./client
```
