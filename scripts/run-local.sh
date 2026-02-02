#!/bin/sh
# This script runs the Coliru website on your local machine. It's not used in production.
# Usage: ./scripts/run-local.sh
set -eu

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"
export COLIRU_ARCHIVE_ROOT="${ROOT_DIR}"

mkdir -p "${ROOT_DIR}/Archive" "${ROOT_DIR}/Archive2" "${ROOT_DIR}/Archive3"

ensure_writable_dir() {
    dir="$1"
    owner_uid="$(stat -c %u "$dir" 2>/dev/null || echo "")"
    if [ "$owner_uid" != "2001" ]; then
        if command -v sudo >/dev/null 2>&1; then
            sudo chown -R 2001:2001 "$dir"
        else
            echo "Directory owner must be uid 2001: $dir" >&2
            echo "Fix with: sudo chown -R 2001:2001 $dir" >&2
            exit 1
        fi
    fi
}

ensure_writable_dir "${ROOT_DIR}/Archive2"
ensure_writable_dir "${ROOT_DIR}/Archive3"

if [ -S /var/run/docker.sock ]; then
    DOCKER_GID="$(stat -c %g /var/run/docker.sock)"
else
    DOCKER_GID="0"
fi
export DOCKER_GID

docker volume create coliru_jobs >/dev/null 2>&1 || true
docker run --rm -v coliru_jobs:/job busybox sh -c 'chown -R 2001:2001 /job' >/dev/null 2>&1 || true

docker build -t coliru-runner:latest "${ROOT_DIR}/Docker/runner"

cd "${ROOT_DIR}"
if docker compose version >/dev/null 2>&1; then
    COMPOSE_CMD="docker compose"
elif command -v docker-compose >/dev/null 2>&1; then
    COMPOSE_CMD="docker-compose"
else
    echo "docker compose or docker-compose is required." >&2
    exit 1
fi

${COMPOSE_CMD} up --build
