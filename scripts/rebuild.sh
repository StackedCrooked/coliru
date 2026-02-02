#!/bin/sh
# Rebuild local Docker images (runner + webserver) without using cache.
# Use this after changing Dockerfiles or dependencies when a normal rebuild
# seems to keep using old layers.
# Usage: ./scripts/rebuild.sh
set -eu

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"

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

${COMPOSE_CMD} build --no-cache
