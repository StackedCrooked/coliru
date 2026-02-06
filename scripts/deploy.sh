#!/bin/sh
set -eu

# Deploy updated webserver code to the live stack.
# Steps:
#   1) git pull
#   2) build webserver image
#   3) recreate webserver container

REPO_ROOT="$(cd "$(dirname "$0")/.." && pwd)"
cd "${REPO_ROOT}"

# Load persisted environment (DOCKER_GID, COLIRU_*), if present.
if [ -f /etc/coliru/coliru.env ]; then
    # shellcheck disable=SC1091
    set -a
    . /etc/coliru/coliru.env
    set +a
fi

# Ensure DOCKER_GID is set so compose can join the docker group.
if [ -z "${DOCKER_GID:-}" ]; then
    DOCKER_GID="$(stat -c %g /var/run/docker.sock)"
    export DOCKER_GID
fi

if ! command -v coliru-compose >/dev/null 2>&1; then
    echo "coliru-compose is required (installed by SetupHost.sh)." >&2
    exit 1
fi

echo "==> Updating repo"
git pull --ff-only

echo "==> Building webserver image"
coliru-compose build webserver

echo "==> Restarting webserver container"
coliru-compose up -d webserver

echo "Deploy complete."
