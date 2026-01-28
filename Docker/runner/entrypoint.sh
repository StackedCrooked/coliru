#!/bin/sh
set -e

WORKDIR="${COLIRU_RUNNER_WORKDIR:-/job}"
TIMEOUT="${COLIRU_RUNNER_TIMEOUT:-20}"

export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib:/usr/local/lib64:/usr/lib64
cd "${WORKDIR}"

is_number() {
    case "$1" in
        ''|*[!0-9]*) return 1 ;;
        *) return 0 ;;
    esac
}

if ! is_number "${TIMEOUT}"; then
    echo "COLIRU_RUNNER_TIMEOUT must be a number" 1>&2
    exit 2
fi

if [ "${TIMEOUT}" -gt 0 ]; then
    setsid /bin/bash -lc "cd \"${WORKDIR}\"; source ./cmd.sh" &
    cmd_pid=$!

    (
        sleep "${TIMEOUT}"
        kill -KILL -"${cmd_pid}" 2>/dev/null || true
    ) &
    watchdog_pid=$!

    wait "${cmd_pid}"
    status=$?

    kill "${watchdog_pid}" 2>/dev/null || true
    wait "${watchdog_pid}" 2>/dev/null || true
    exit "${status}"
fi

exec /bin/bash -lc "cd \"${WORKDIR}\"; source ./cmd.sh"
