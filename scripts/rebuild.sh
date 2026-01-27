#!/bin/sh
set -eu

ROOT_DIR="$(cd "$(dirname "$0")/.." && pwd)"

docker build -t coliru-runner:latest "${ROOT_DIR}/Docker/runner"

cd "${ROOT_DIR}"
docker compose build --no-cache
