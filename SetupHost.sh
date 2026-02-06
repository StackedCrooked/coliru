#!/bin/sh
set -eu

REPO_ROOT="$(cd "$(dirname "$0")" && pwd)"
COLIRU_DOMAIN="${COLIRU_DOMAIN:-localhost}"
COLIRU_PORT="${COLIRU_PORT:-8080}"
COLIRU_TLS_MODE="${COLIRU_TLS_MODE:-selfsigned}" # none | selfsigned | letsencrypt
COLIRU_EMAIL="${COLIRU_EMAIL:-}"
COLIRU_ARCHIVE_ROOT="${COLIRU_ARCHIVE_ROOT:-/}"
COLIRU_STATE_ROOT="${COLIRU_STATE_ROOT:-/var/coliru/state}"

if [ "$(id -u)" -ne 0 ]; then
    echo "SetupHost.sh must be run as root." >&2
    exit 1
fi

export DEBIAN_FRONTEND=noninteractive

apt-get update
apt-get install -y software-properties-common ca-certificates curl gnupg
add-apt-repository -y universe
apt-get update

# Try Ubuntu packages first.
if ! apt-get install -y docker.io docker-compose-plugin nginx; then
    # Add Docker's official repo to get docker-compose-plugin on newer Ubuntu.
    install -m 0755 -d /etc/apt/keyrings
    curl -fsSL https://download.docker.com/linux/ubuntu/gpg | gpg --dearmor -o /etc/apt/keyrings/docker.gpg
    chmod a+r /etc/apt/keyrings/docker.gpg
    echo "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu $(. /etc/os-release && echo $VERSION_CODENAME) stable" \
        >/etc/apt/sources.list.d/docker.list
    apt-get update
    apt-get install -y docker.io docker-compose-plugin nginx
fi

systemctl enable --now docker
systemctl enable --now nginx

# Archive directories for the webserver (writeable).
ARCHIVE_DIR="${COLIRU_ARCHIVE_ROOT%/}"
mkdir -p "${ARCHIVE_DIR}/Archive" "${ARCHIVE_DIR}/Archive2" "${ARCHIVE_DIR}/Archive3"
if getent passwd webserver >/dev/null 2>&1; then
    chown webserver:coliru "${ARCHIVE_DIR}/Archive" "${ARCHIVE_DIR}/Archive2" "${ARCHIVE_DIR}/Archive3"
else
    chown 2001:2000 "${ARCHIVE_DIR}/Archive" "${ARCHIVE_DIR}/Archive2" "${ARCHIVE_DIR}/Archive3"
fi

# Feedback storage (persisted outside the image).
mkdir -p "${COLIRU_STATE_ROOT}"
touch "${COLIRU_STATE_ROOT}/feedback.txt"
if getent passwd webserver >/dev/null 2>&1; then
    chown webserver:coliru "${COLIRU_STATE_ROOT}" "${COLIRU_STATE_ROOT}/feedback.txt"
else
    chown 2001:2000 "${COLIRU_STATE_ROOT}" "${COLIRU_STATE_ROOT}/feedback.txt"
fi
chmod 664 "${COLIRU_STATE_ROOT}/feedback.txt"

# Build runner image locally (required for /compile).
docker build -t coliru-runner:latest "${REPO_ROOT}/Docker/runner"

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
COLIRU_ARCHIVE_ROOT=${COLIRU_ARCHIVE_ROOT}
COLIRU_STATE_ROOT=${COLIRU_STATE_ROOT}
EOF

# Nginx reverse proxy config (HTTP only; TLS can be added later).
if [ "${COLIRU_TLS_MODE}" = "selfsigned" ]; then
    mkdir -p /etc/nginx/certs
    if [ ! -f /etc/nginx/certs/localhost.crt ]; then
        openssl req -x509 -nodes -newkey rsa:2048 -days 365 \
            -keyout /etc/nginx/certs/localhost.key \
            -out /etc/nginx/certs/localhost.crt \
            -subj "/CN=${COLIRU_DOMAIN}"
    fi
fi

if [ "${COLIRU_TLS_MODE}" = "none" ]; then
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
else
    cat >/etc/nginx/sites-available/coliru <<EOF
server {
    listen 80;
    server_name ${COLIRU_DOMAIN};
    return 301 https://\$host\$request_uri;
}

server {
    listen 443 ssl;
    server_name ${COLIRU_DOMAIN};

    ssl_certificate     /etc/nginx/certs/localhost.crt;
    ssl_certificate_key /etc/nginx/certs/localhost.key;

    location / {
        proxy_pass http://127.0.0.1:${COLIRU_PORT};
        proxy_set_header Host \$host;
        proxy_set_header X-Real-IP \$remote_addr;
        proxy_set_header X-Forwarded-For \$proxy_add_x_forwarded_for;
        proxy_set_header X-Forwarded-Proto \$scheme;
    }
}
EOF
fi

ln -sf /etc/nginx/sites-available/coliru /etc/nginx/sites-enabled/coliru
if [ -e /etc/nginx/sites-enabled/default ]; then
    rm -f /etc/nginx/sites-enabled/default
fi
nginx -t
systemctl reload nginx

if [ "${COLIRU_TLS_MODE}" = "letsencrypt" ]; then
    if [ -z "${COLIRU_EMAIL}" ]; then
        echo "COLIRU_EMAIL is required for letsencrypt." >&2
        exit 1
    fi
    apt-get install -y certbot python3-certbot-nginx
    certbot --nginx -d "${COLIRU_DOMAIN}" -m "${COLIRU_EMAIL}" --agree-tos --non-interactive
fi

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
if [ "${COLIRU_TLS_MODE}" != "none" ]; then
    echo "Nginx TLS mode: ${COLIRU_TLS_MODE}"
fi
