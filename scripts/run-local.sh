#!/bin/sh
set -eu

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"

mkdir -p "${ROOT_DIR}/Archive" "${ROOT_DIR}/Archive2" "${ROOT_DIR}/CompileArchive"

if [ -S /var/run/docker.sock ]; then
    DOCKER_GID="$(stat -c %g /var/run/docker.sock)"
else
    DOCKER_GID="0"
fi
export DOCKER_GID

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
