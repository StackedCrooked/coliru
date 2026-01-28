#!/bin/bash
set -e

# Prepare the job directory (shared with runner container)
export jobdir="${INPUT_FILES_DIR}"
jobid=$(basename "${jobdir}")
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
RUNNER_JOBDIR="${RUNNER_WORKDIR}/${jobid}"
RUNNER_USER="${COLIRU_RUNNER_USER:-0}"
RUNNER_CPUS="${COLIRU_RUNNER_CPUS:-1}"
RUNNER_MEMORY="${COLIRU_RUNNER_MEMORY:-512m}"
RUNNER_MEMORY_SWAP="${COLIRU_RUNNER_MEMORY_SWAP:-512m}"
RUNNER_PIDS_LIMIT="${COLIRU_RUNNER_PIDS_LIMIT:-64}"
RUNNER_NPROC="${COLIRU_RUNNER_NPROC:-50}"
RUNNER_MAX_FILESIZE_KB="${COLIRU_RUNNER_MAX_FILESIZE:-524288}"
RUNNER_CPU="${COLIRU_RUNNER_CPU:-10}"
RUNNER_TMPFS_SIZE="${COLIRU_RUNNER_TMPFS_SIZE:-64m}"
RUNNER_VOLUME="${COLIRU_RUNNER_VOLUME:-}"
RUNNER_TIMEOUT="${COLIRU_RUNNER_TIMEOUT:-}"
RUNNER_MAX_OUTPUT="${COLIRU_RUNNER_MAX_OUTPUT:-524288}"

EXTRA_ARGS=""
if [ -n "${RUNNER_CPU}" ]; then
    EXTRA_ARGS="${EXTRA_ARGS} --ulimit cpu=${RUNNER_CPU}"
fi

MOUNT_ARGS=""
if [ -n "${RUNNER_VOLUME}" ]; then
    MOUNT_ARGS="--mount type=volume,src=${RUNNER_VOLUME},dst=${RUNNER_WORKDIR}"
else
    MOUNT_ARGS="-v ${jobdir}:${RUNNER_JOBDIR}:rw"
fi

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
    --ulimit "fsize=$((RUNNER_MAX_FILESIZE_KB * 2))" \
    ${EXTRA_ARGS} \
    --cap-drop ALL \
    --security-opt no-new-privileges \
    --user "${RUNNER_USER}" \
    -e COLIRU_RUNNER_WORKDIR="${RUNNER_JOBDIR}" \
    -e COLIRU_RUNNER_TIMEOUT="${RUNNER_TIMEOUT}" \
    -e COLIRU_RUNNER_MAX_OUTPUT="${RUNNER_MAX_OUTPUT}" \
    -e COLIRU_RUNNER_NPROC="${RUNNER_NPROC}" \
    -e COLIRU_RUNNER_MAX_FILESIZE="${RUNNER_MAX_FILESIZE_KB}" \
    -e COLIRU_RUNNER_CPU="${RUNNER_CPU}" \
    ${MOUNT_ARGS} \
    -w "${RUNNER_JOBDIR}" \
    "${RUNNER_IMAGE}" \
    /runner/entrypoint.sh
