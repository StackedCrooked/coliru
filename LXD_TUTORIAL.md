# Coliru LXD “Pretend Host” Setup (Ubuntu 24.04)

_Note: This document is AI-generated and should be reviewed for accuracy._

This creates a clean host-like environment (LXD container) where we install Docker + Nginx and run the Coliru stack with a reverse proxy.

---

## 1) Install LXD on the host laptop

```sh
sudo snap install lxd
sudo usermod -aG lxd $USER
newgrp lxd
```

## 2) Initialize LXD (creates lxdbr0 NAT bridge)

```sh
lxd init
```

Accept defaults (dir storage is fine).

## 3) Launch a fresh Ubuntu container

```sh
lxc launch ubuntu:24.04 coliru-host
```

## 4) Fix LXD networking if container can’t reach the internet

Inside container:

```sh
lxc exec coliru-host -- bash
ping -c 1 10.117.112.1
ping -c 1 1.1.1.1
```

If it can ping `10.117.112.1` but not `1.1.1.1`, host NAT/forwarding is blocked.

On the host:

```sh
sudo sysctl -w net.ipv4.ip_forward=1
echo "net.ipv4.ip_forward=1" | sudo tee /etc/sysctl.d/99-lxd.conf

sudo iptables -t nat -C POSTROUTING -s 10.117.112.0/24 ! -d 10.117.112.0/24 -j MASQUERADE 2>/dev/null || \
sudo iptables -t nat -A POSTROUTING -s 10.117.112.0/24 ! -d 10.117.112.0/24 -j MASQUERADE

sudo iptables -I FORWARD -i lxdbr0 -o wlp2s0 -j ACCEPT
sudo iptables -I FORWARD -i wlp2s0 -o lxdbr0 -m state --state RELATED,ESTABLISHED -j ACCEPT
```

Then retry inside the container:
```sh
ping -c 1 1.1.1.1
```

## 5) Allow Docker inside LXD (nesting)

On the host:

```sh
lxc config set coliru-host security.nesting true
lxc config set coliru-host security.privileged true
lxc restart coliru-host
```

## 6) Copy the repo into LXD

```sh
lxc file push -r /path/to/coliru coliru-host/root/coliru
```

## 7) Run the host setup script inside LXD

Inside the container:

```sh
lxc exec coliru-host -- bash
cd /root/coliru
chmod +x ./SetupHost.sh
sudo COLIRU_DOMAIN=localhost COLIRU_PORT=8080 COLIRU_TLS_MODE=selfsigned ./SetupHost.sh
```

Notes:
- `COLIRU_TLS_MODE` can be `none`, `selfsigned` (dev), or `letsencrypt` (prod).
- For `letsencrypt`, also set `COLIRU_EMAIL`.
- Archives are mounted from `${COLIRU_ARCHIVE_ROOT:-/}` (default `/Archive`, `/Archive2`, `/Archive3`).
- The script installs Docker + Nginx, builds the runner image, sets up systemd, and runs `docker compose up -d`.

## 8) Verify the service

Inside the container:

```sh
systemctl status coliru.service --no-pager
docker ps
curl http://127.0.0.1
```

## 9) Expose the website to your laptop (host)

On the host:

```sh
lxc config device add coliru-host http proxy listen=tcp:0.0.0.0:8080 connect=tcp:127.0.0.1:80
```

Then open:
```
http://localhost:8080
```

Remove proxy later:
```sh
lxc config device remove coliru-host http
```

---

## Troubleshooting tips

- If `docker-compose-plugin` isn’t available, `SetupHost.sh` falls back to `docker-compose`.
- If `coliru.service` fails:
  ```sh
  systemctl status coliru.service --no-pager
  journalctl -xeu coliru.service --no-pager
  ```

---
