#!/bin/bash
set -e

# Prepare the job directory (shared with runner container)
export jobdir="${INPUT_FILES_DIR}"
mkdir -p "${jobdir}"
chmod -R a+w "${jobdir}"


cleanup_file="/tmp/cleanup_${COLIRU_PORT}"


# Cleanup temp files from previous job
[ -f "${cleanup_file}" ] && {
    bash "${cleanup_file}"
    rm -f "${cleanup_file}"
}


# Schedule cleanup of temp files for this job.
echo "rm -rf ${INPUT_FILES_DIR}" >> "${cleanup_file}"

# Runner defaults (override via env).
RUNNER_IMAGE="${COLIRU_RUNNER_IMAGE:-coliru-runner:latest}"
RUNNER_WORKDIR="${COLIRU_RUNNER_WORKDIR:-/job}"
RUNNER_USER="${COLIRU_RUNNER_USER:-0}"
RUNNER_CPUS="${COLIRU_RUNNER_CPUS:-1}"
RUNNER_MEMORY="${COLIRU_RUNNER_MEMORY:-512m}"
RUNNER_MEMORY_SWAP="${COLIRU_RUNNER_MEMORY_SWAP:-512m}"
RUNNER_PIDS_LIMIT="${COLIRU_RUNNER_PIDS_LIMIT:-64}"
RUNNER_NPROC="${COLIRU_RUNNER_NPROC:-50}"
RUNNER_FSIZE="${COLIRU_RUNNER_FSIZE:-4000}"
RUNNER_CPU="${COLIRU_RUNNER_CPU:-}"
RUNNER_TMPFS_SIZE="${COLIRU_RUNNER_TMPFS_SIZE:-64m}"

RUN_CMD=$(cat <<'EOF'
set -e
ulimit -u "${COLIRU_RUNNER_NPROC}"
ulimit -f "${COLIRU_RUNNER_FSIZE}"
if [ -n "${COLIRU_RUNNER_CPU}" ]; then
    ulimit -t "${COLIRU_RUNNER_CPU}"
fi
export LD_LIBRARY_PATH=/usr/local/lib:/usr/lib:/usr/local/lib64:/usr/lib64
cd "${COLIRU_RUNNER_WORKDIR}"
title() { true ; }
set +e
source "${COLIRU_RUNNER_WORKDIR}/cmd.sh"
EOF
)

# Run the command in a dedicated runner container.
docker run --rm \
    --network=none \
    --read-only \
    --tmpfs "/tmp:rw,nosuid,nodev,exec,size=${RUNNER_TMPFS_SIZE}" \
    --pids-limit "${RUNNER_PIDS_LIMIT}" \
    --cpus "${RUNNER_CPUS}" \
    --memory "${RUNNER_MEMORY}" \
    --memory-swap "${RUNNER_MEMORY_SWAP}" \
    --ulimit "nproc=${RUNNER_NPROC}" \
    --ulimit "fsize=${RUNNER_FSIZE}" \
    --cap-drop ALL \
    --security-opt no-new-privileges \
    --user "${RUNNER_USER}" \
    -e COLIRU_RUNNER_WORKDIR="${RUNNER_WORKDIR}" \
    -e COLIRU_RUNNER_NPROC="${RUNNER_NPROC}" \
    -e COLIRU_RUNNER_FSIZE="${RUNNER_FSIZE}" \
    -e COLIRU_RUNNER_CPU="${RUNNER_CPU}" \
    -v "${jobdir}:${RUNNER_WORKDIR}:rw" \
    -w "${RUNNER_WORKDIR}" \
    "${RUNNER_IMAGE}" \
    /bin/bash -lc "${RUN_CMD}"
