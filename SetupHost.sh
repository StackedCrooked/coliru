#!/bin/sh
set -eu

REPO_ROOT="$(cd "$(dirname "$0")" && pwd)"
COLIRU_DOMAIN="${COLIRU_DOMAIN:-_}"
COLIRU_PORT="${COLIRU_PORT:-8080}"

if [ "$(id -u)" -ne 0 ]; then
    echo "SetupHost.sh must be run as root." >&2
    exit 1
fi

export DEBIAN_FRONTEND=noninteractive

apt-get update
apt-get install -y software-properties-common
add-apt-repository -y universe
apt-get update

# Prefer compose plugin, fallback to docker-compose if unavailable.
if ! apt-get install -y docker.io docker-compose-plugin nginx; then
    apt-get install -y docker.io docker-compose nginx
fi

systemctl enable --now docker
systemctl enable --now nginx

# Compose wrapper for systemd (detects compose v2 or v1).
cat >/usr/local/bin/coliru-compose <<'EOF'
#!/bin/sh
set -eu
if docker compose version >/dev/null 2>&1; then
    exec docker compose "$@"
elif command -v docker-compose >/dev/null 2>&1; then
    exec docker-compose "$@"
else
    echo "docker compose or docker-compose is required." >&2
    exit 1
fi
EOF
chmod +x /usr/local/bin/coliru-compose

# Environment file for systemd unit.
mkdir -p /etc/coliru
DOCKER_GID="$(stat -c %g /var/run/docker.sock)"
cat >/etc/coliru/coliru.env <<EOF
DOCKER_GID=${DOCKER_GID}
COLIRU_DOMAIN=${COLIRU_DOMAIN}
COLIRU_PORT=${COLIRU_PORT}
EOF

# Nginx reverse proxy config (HTTP only; TLS can be added later).
cat >/etc/nginx/sites-available/coliru <<EOF
server {
    listen 80;
    server_name ${COLIRU_DOMAIN};

    location / {
        proxy_pass http://127.0.0.1:${COLIRU_PORT};
        proxy_set_header Host \$host;
        proxy_set_header X-Real-IP \$remote_addr;
        proxy_set_header X-Forwarded-For \$proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto \$scheme;
    }
}
EOF

ln -sf /etc/nginx/sites-available/coliru /etc/nginx/sites-enabled/coliru
if [ -e /etc/nginx/sites-enabled/default ]; then
    rm -f /etc/nginx/sites-enabled/default
fi
nginx -t
systemctl reload nginx

# systemd unit to keep coliru running on boot.
cat >/etc/systemd/system/coliru.service <<EOF
[Unit]
Description=Coliru webserver (docker compose)
After=docker.service network-online.target
Wants=docker.service network-online.target

[Service]
Type=oneshot
WorkingDirectory=${REPO_ROOT}
EnvironmentFile=/etc/coliru/coliru.env
ExecStart=/usr/local/bin/coliru-compose up -d
ExecStop=/usr/local/bin/coliru-compose down
RemainAfterExit=yes
TimeoutStartSec=0

[Install]
WantedBy=multi-user.target
EOF

systemctl daemon-reload
systemctl enable --now coliru

echo "Setup complete."
echo "Nginx proxying http://${COLIRU_DOMAIN} -> http://127.0.0.1:${COLIRU_PORT}"
